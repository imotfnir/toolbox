import autotestlib.type as Type
import autotestlib.action as Action
from autotestlib.base import print_err

import paramiko
import pexpect
import re
import abc


class Session():
    def __init__(self, account: Type.Account) -> None:
        self.account = account
        self.timeout = 30
        self.process = None

    @property
    def account(self) -> Type.Account:
        return self._account

    @account.setter
    def account(self, account: Type.Account) -> None:
        self._account = account

    @property
    def timeout(self) -> float:
        return self._timeout

    @timeout.setter
    def timeout(self, timeout: float) -> None:
        if timeout < 0:
            print_err("Timeout must >= 0")
            raise ValueError("Timeout must >= 0")
        self._timeout = timeout

    @abc.abstractmethod
    def connect(self) -> None:
        pass


class Terminal(Session):
    @abc.abstractmethod
    def connect(self) -> None:
        pass


class X86Terminal(Terminal, Action.X86Action):
    def connect(self) -> None:
        try:
            self.process = paramiko.SSHClient()
            self.process.set_missing_host_key_policy(paramiko.AutoAddPolicy())
            self.process.connect(
                self.account.ipv4.ip,
                self.account.ipv4.port,
                self.account.username,
                self.account.password,
                timeout=self.timeout)
        except Exception:
            print_err("X86 ssh connect fail")
            raise

    # ToDo: rewrite action fucntion by DIP
    def lspci(self) -> str:
        try:
            _, stdout, _ = self.process.exec_command("lspci")
            return str(stdout.read(), encoding='UTF-8')
        except Exception:
            print_err("lspci fail")
            raise

    def get_bios_version(self) -> Type.BiosVersion:
        try:
            _, stdout, _ = self.process.exec_command(
                "dmidecode -s bios-version")
            ver = Type.BiosVersion(str(stdout.read(), encoding='UTF-8'))

        except Exception:
            print_err("get BIOS version fail")
        return ver


class BmcTerminal(Terminal, Action.BmcAction):
    pass


class Console(Session):
    def __init__(self, account: Type.Account) -> None:
        super().__init__(account=account)
        self.delay: float = 0.2
        self._prompt = "root@ubuntu:~#"

    def connect(self) -> None:
        try:
            self.process = pexpect.spawn('ssh',
                                         ['-o',
                                          'StrictHostKeyChecking=no',
                                          '-o',
                                          'UserKnownHostsFile=/dev/null',
                                          '-l',
                                          self.account.username,
                                          self.account.ipv4.ip,
                                          '-p',
                                          str(self.account.ipv4.port)])
        except Exception:
            print_err("Terminal server login fail")
            raise

        match self.process.expect(["(?i)password:", pexpect.EOF, pexpect.TIMEOUT]):
            case 0:
                self.process.sendline(self.account.password)
                print('Terminal server Enter password')
                self._is_connect_success()
            case _:
                print_err("Terminal server login timeout")
        return

    def _is_connect_success(self) -> bool:
        match self.process.expect(["Suspend Menu", pexpect.EOF, pexpect.TIMEOUT]):
            case 0:
                print("Terminal server login success")
                return True
            case _:
                print_err("Terminal server login timeout")
                return False

    def _flush_buffer(self) -> None:
        if self.process.before:
            self.process.expect(r'.+')
        return

    def login(self) -> None:
        self._flush_buffer()
        self.process.send("\r")

        while True:
            self._flush_buffer()
            self.process.send("\r")
            match self.process.expect(["ubuntu login", pexpect.EOF, pexpect.TIMEOUT], timeout=5):
                case 0:
                    break
                case _:
                    pass

        self.process.send("root\r")

        match self.process.expect(["(?i)password", pexpect.EOF, pexpect.TIMEOUT]):
            case 0:
                self.process.send("ufispace\r")
            case _:
                print('Login failed')
                return

        match self.process.expect([self._prompt, pexpect.EOF, pexpect.TIMEOUT]):
            case 0:
                return
            case _:
                print('Login failed')
                return

    def is_hardware_error(self) -> bool:
        self._flush_buffer()
        self.process.send("dmesg | grep -i \"hardware error\"\r")
        match self.process.expect(["(?i)hardware error", pexpect.EOF, pexpect.TIMEOUT], timeout=5):
            case 0:
                return True
            case _:
                return False

    def get_ssh_ip(self) -> Type.SshIp:
        self._flush_buffer()
        self.process.send("ip r\r")
        self.process.expect(
            ["(?<=link src )(\\d{1,3}\\.){3}\\d{1,3}", pexpect.EOF, pexpect.TIMEOUT], timeout=5)
        return Type.SshIp(str(self.process.after, encoding='UTF-8'))

    def get_bmc_ip(self) -> Type.SshIp:
        self._flush_buffer()
        self.process.send("ipmitool lan print\r")
        self.process.expect(
            ["(IP Address\\s*\\:\\s)(\\d{1,3}\\.){3}\\d{1,3}", pexpect.EOF, pexpect.TIMEOUT], timeout=5)
        ip = re.search(
            "(\\d{1,3}\\.){3}\\d{1,3}", str(
                self.process.after, encoding='UTF-8')).group(0)
        return Type.SshIp(ip)


if __name__ == "__main__":
    pass
