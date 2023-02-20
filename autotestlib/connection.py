import pexpect
import re
import autotestlib.custom_type as Type


class Console:

    def __init__(self, ipv4: Type.Ipv4, username: str, password: str):
        self.delay: float = 0.2
        self._ipv4 = ipv4
        self._username = username
        self._password = password
        self._prompt = "root@ubuntu:~#"
        self.process = None

    def connect(self) -> None:
        self.process = pexpect.spawn('ssh',
                                     ['-o',
                                      'StrictHostKeyChecking=no',
                                      '-o',
                                      'UserKnownHostsFile=/dev/null',
                                      '-l',
                                      self._username,
                                      self._ipv4.ip,
                                      '-p',
                                      str(self._ipv4.port)])
        match self.process.expect(["(?i)password:", pexpect.EOF, pexpect.TIMEOUT]):
            case 0:
                self.process.sendline("ufispace")
                print('Terminal server Enter password')
                self._is_connect_success()
            case 1:
                print('Login failed')
            case 2:
                print('Login failed')
            case _:
                print('Login failed')
        return

    def _is_connect_success(self) -> bool:
        match self.process.expect(["Suspend Menu", pexpect.EOF, pexpect.TIMEOUT]):
            case 0:
                print("Terminal server Login success")
                return True
            case _:
                print('Login failed')
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
