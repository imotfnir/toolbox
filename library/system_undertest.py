from library.custom_type import *


class system_undertest():
    def __init__(self, console_ip: ConsoleIp = None,
                 ssh_ip: SshIp = None, bmc_ip: SshIp = None) -> None:
        self._console_ip = console_ip
        self._ssh_ip = ssh_ip
        self._bmc_ip = bmc_ip
        self._platform = None
        self._pcie_list = None
        self._sku = None
        self._ssd_list = None
        self._bios = None
        self._nvm = None
        self._cpu_cpld = None
        self._mb_cpld = None
        pass


if __name__ == '__main__':
    pass
