"""System module."""
import logging
import ipaddress


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


if __name__ == "__main__":
    pass
