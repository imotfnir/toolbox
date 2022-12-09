import logging
import ipaddress


class Ipv4:
    def __init__(self, ip: str, port: int) -> None:
        self._ip = ip
        self._port = port
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
        if (port < 1):
            logging.warning("port number only can be 5101~5116")
            return
        if (port > 5116):
            logging.warning("port number only can be 5101~5116")
            return
        if (port < 5101) and (port > 16):
            logging.warning("port number only can be 5101~5116")
            return
        if (port <= 16):
            self._port = port + 5100
            return
        self._port = port
        return


if __name__ == "__main__":
    pass
