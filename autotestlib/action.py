import autotestlib.type as Type

import abc


class X86Action:
    @abc.abstractmethod
    def lspci(self) -> str:
        pass

    @property
    @abc.abstractmethod
    def bios_version(self) -> str:
        pass

    @property
    @abc.abstractmethod
    def cpu_cpld_version(self) -> str:
        pass

    @property
    @abc.abstractmethod
    def bmc_version(self) -> str:
        pass

    @property
    @abc.abstractmethod
    def os_version(self) -> str:
        pass


class OnieAction:
    pass


class BmcAction:
    pass
