import autotestlib.type as Type
import autotestlib.session as Session
import autotestlib.base as Base


class SystemUnderTest():
    def __init__(self, console_ip: Type.ConsoleIp) -> None:
        self.console_ip: Type.ConsoleIp = console_ip
        self.x86_ip: Type.SshIp = None
        self.bmc_ip: Type.SshIp = None
        self._onie_ip: Type.SshIp = None
        self.console: Session.Console = None
        self.x86: Session.X86Terminal = None
        self.bmc: Session.BmcTerminal = None
        self.config: dict = None
        self.platform = None
        self.sku = None
        self.update_config()

    @property
    def console_ip(self) -> Type.ConsoleIp:
        return self._console_ip

    @console_ip.setter
    def console_ip(self, ip: Type.ConsoleIp) -> None:
        self._console_ip = ip

    @property
    def x86_ip(self) -> Type.SshIp:
        return self._x86_ip

    @x86_ip.setter
    def x86_ip(self, ip: Type.SshIp) -> None:
        self._x86_ip = ip

    @property
    def bmc_ip(self) -> Type.SshIp:
        return self._bmc_ip

    @bmc_ip.setter
    def bmc_ip(self, ip: Type.SshIp) -> None:
        self._bmc_ip = ip

    def __str__(self) -> str:
        var = f"Console: {self.console_ip}\n"
        var += f"x86: {self.x86_ip}\n"
        var += f"bmc: {self.bmc_ip}"
        return var

    def connect_console(self) -> None:
        account = Type.Account(
            Type.ConsoleIp(
                self._console_ip.ip,
                self._console_ip.port),
            "administrator",
            "ufispace")
        self.console = Session.Console(account)
        self.console.connect()

    def connect_x86(self) -> None:
        account = Type.Account(
            Type.SshIp(self.x86_ip.ip),
            "root",
            "ufispace")
        self.x86 = Session.X86Terminal(account)
        self.x86.connect()

    def connext_bmc(self) -> Session.BmcTerminal:
        account = Type.Account(
            Type.SshIp(self.bmc_ip.ip),
            "sysadmin",
            "superuser")
        self.bmc = Session.BmcTerminal(account)
        self.bmc.connect()

    def update_x86_ip(self) -> None:
        self.x86_ip = self.console.get_ssh_ip()

    def update_bmc_ip(self) -> None:
        self.bmc_ip = self.console.get_bmc_ip()

    def update(self) -> None:
        self.update_x86_ip()
        self.update_bmc_ip()

    def connect_all(self) -> None:
        self.connect_console()
        self.connect_x86()
        self.connext_bmc()

    def update_config(self) -> None:
        self.config = Base.Decoding.decode_config("autotestlib/config.json")
        self.platform = self.config["platform"]
        self.sku = self.config["sku"]
        self.console_ip = Type.ConsoleIp(
            self.config["console_ip"]["ip"],
            self.config["console_ip"]["port"])


if __name__ == '__main__':
    pass
