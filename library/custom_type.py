import logging
import ipaddress


class Ipv4:
    def __init__(self, ip: str, port: int) -> None:
        self.ip = ip
        self.port = port
        return

    @property
    def ip(self) -> str:
        return self._ip

    @ip.setter
    def ip(self, ip: str) -> None:
        self._ip = ipaddress.ip_address(ip).__str__()
        return

    @property
    def port(self) -> int:
        return self._port

    @port.setter
    def port(self, port: int) -> None:
        if (port < 0):
            logging.warning("port number only can be 0~65535")
            raise ValueError("port number only can be 0~65535")
        if (port > 65535):
            logging.warning("port number only can be 0~65535")
            raise ValueError("port number only can be 0~65535")
        self._port = port
        return


class ConsoleIp(Ipv4):
    @Ipv4.port.setter
    def port(self, port: int) -> None:
        if (port < 1):
            logging.warning("port number only can be 5101~5116")
            raise ValueError("port number only can be 5101~5116")
        if (port > 5116):
            logging.warning("port number only can be 5101~5116")
            raise ValueError("port number only can be 5101~5116")
        if (port < 5101) and (port > 16):
            logging.warning("port number only can be 5101~5116")
            raise ValueError("port number only can be 5101~5116")
        if (port <= 16):
            self._port = port + 5100
            return
        self._port = port
        return


class SshIp(Ipv4):
    @Ipv4.port.setter
    def port(self, port: int) -> None:
        if (port != 22):
            raise ValueError("port number only can be 22")
        logging.warning("port number only can be 22")
        self._port = 22
        return


class Connection:
    def __init__(self, ipv4: Ipv4, username: str, password: str) -> None:
        self._ipv4 = ipv4
        self._username = username
        self._password = password
        pass


if __name__ == "__main__":
    pass
