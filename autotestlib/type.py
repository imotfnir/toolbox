import logging
import ipaddress
from enum import Enum


class Ipv4:
    def __init__(self, ip: str, port: int) -> None:
        self.ip = ip
        self.port = port

    @property
    def ip(self) -> str:
        return self._ip

    @ip.setter
    def ip(self, ip: str) -> None:
        self._ip = str(ipaddress.ip_address(ip))

    @property
    def port(self) -> int:
        return self._port

    @port.setter
    def port(self, port: int) -> None:
        if port < 0:
            logging.warning("port number only can be 0~65535")
            raise ValueError("port number only can be 0~65535")
        if port > 65535:
            logging.warning("port number only can be 0~65535")
            raise ValueError("port number only can be 0~65535")
        self._port = port

    def __str__(self) -> str:
        return f"{self.ip}: {self.port}"


class ConsoleIp(Ipv4):
    @Ipv4.port.setter
    def port(self, port: int) -> None:
        if port < 5101:
            logging.warning("port number only can be 5101~5116")
            raise ValueError("port number only can be 5101~5116")
        if port > 5116:
            logging.warning("port number only can be 5101~5116")
            raise ValueError("port number only can be 5101~5116")
        self._port = port


class SshIp(Ipv4):
    def __init__(self, ip: str) -> None:
        super().__init__(ip=ip, port=22)

    @Ipv4.port.setter
    def port(self, port: int) -> None:
        if port != 22:
            logging.warning("port number only can be 22")
            raise ValueError("port number only can be 22")
        self._port = 22


class Account:
    def __init__(self, ipv4: Ipv4, username: str, password: str) -> None:
        self.ipv4 = ipv4
        self.username = username
        self.password = password


class Semver:
    def __init__(self) -> None:
        self.major: int = None
        self.minor: int = None
        self.patch: int = None

    @property
    def major(self) -> int:
        return self._major

    @major.setter
    def major(self, num: int) -> None:
        if num < 0:
            raise ValueError("Semver is non-negative integers")
        self._major = num

    @property
    def minor(self) -> int:
        return self._minor

    @minor.setter
    def minor(self, num: int) -> None:
        if num < 0:
            raise ValueError("Semver is non-negative integers")
        self._minor = num

    @property
    def patch(self) -> int:
        return self._patch

    @patch.setter
    def patch(self, num: int) -> None:
        if num < 0:
            raise ValueError("Semver is non-negative integers")
        self._patch = num


class BiosVersion:
    def __init__(self, raw: str) -> None:
        self.raw = raw
        self.semver: Semver = None

    @property
    def semver(self) -> Semver:
        return self._semver

    @semver.setter
    def semver(self, semver: Semver) -> None:
        self._semver = semver


class BmcVersion:
    def __init__(self, raw: str) -> None:
        self.raw = raw


class CpldVersion(Semver):
    pass


class CpuCpldVersion(CpldVersion):
    pass


class MbCpldVersion(CpldVersion):
    pass


class SystemInfo():
    def __init__(self) -> None:
        self.sys_sku: Sku = None
        self.platform: Platform = None
        self.cpu_code_name: str = None
        self.bios_toolbox: str = None
        self.bios_fw_upgrade_tools: str = None


class Platform(Enum):
    ICELAKE = 0
    SKYLAKE = 1
    DENVERTON = 2
    BROADWELL = 3


class Sku:
    sku_list = [
        "S9710-76D (NCP3-1)",
        "S9310-32D (TD4)",
        "S9701-78DC (NCP-Lite)",
        "S9600-72XC (w/o OP2)",
        "S9600-48X (NCP1-2 for SKLD)",
        "S9600-48X (NCP1-2 for SKLD)",
        "S9600-72XC (w/ OP2)",
        "S9300-32D (TD4 1RU X11)",
        "S9701-78DC (w/o OP2)",
        "S9701-82DC (NCP-Lite)",
        "S9701-82DC (w/o OP2)",
        "S9610-36D (NCP3-SA)",
        "S9600-64X (Nighthawk)",
        "S9600-32X (Nighthawk)",
        "S9600-30DX (NCP1-3 for SKLD)",
        "S9600-30DX (NCP1-3 for SKLD)",
        "S9710-76D (w/o OP2)",
        "S9301-32DB(TD4 1RU X9)",
        "S9301-32D (TH3)",
        "S9300-32DB(TD4 1RU X9)",
        "S9600-56DX (Large EMUX)",
        "S9600-28DX (w/ ICLD CPU, half L-EMUX)",
        "S9601-56DX (w/ SKLD CPU)",
        "S9601-28DX (w/ SKLD CPU)",
        "S9321-64E(TH5)",
        "S9725-64E(R3)",
        "S9720-44ED(J3)",
        "S9711-76D(NCP3-AI)",
        "S9600-102XC (Access BNG)",
        "S9711-76D(NCP3-AI W/ NTM)",
        "RESERVED",
        "RESERVED",
        "RESERVED",
    ]


class HwRev(Enum):
    PROTO = 0
    ALPHA = 1
    BETA = 2
    PVT = 3


if __name__ == "__main__":
    pass
