import abc

import autotestlib.type as Type


class X86Action:
    @abc.abstractmethod
    def lspci(self) -> str:
        pass

    @abc.abstractmethod
    def get_bios_version(self) -> Type.BiosVersion:
        pass

    @abc.abstractmethod
    def get_cpu_cpld_version(self) -> Type.CpuCpldVersion:
        pass

    @abc.abstractmethod
    def get_bmc_version(self) -> Type.BmcVersion:
        pass

    @abc.abstractmethod
    def get_os_version(self) -> str:
        pass

    @abc.abstractmethod
    def get_sys_sku(self) -> Type.Sku:
        pass

    @abc.abstractmethod
    def get_platform(self) -> Type.Platform:
        pass

    @abc.abstractmethod
    def get_cpu_code_name(self) -> str:
        pass


class IcelakeAction(X86Action):
    pass


class OnieAction:
    pass


class BmcAction:
    pass
