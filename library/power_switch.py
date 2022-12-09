from library.custom_type import Ipv4


class PowerSwitch():
    def __init__(self, ipv4: Ipv4, port: int) -> None:
        self._ipv4_ip = ipv4
        self._port = port

    def get_port(self) -> str:
        return self._port

    def set_port(self, port: int) -> None:
        if (port < 0):
            self._port = 0
        if (port > 4):
            self._port = 4
        self._port = port
        return

    def get_ipv4(self) -> str:
        return self._ipv4


if __name__ == "__main__":
    pass
