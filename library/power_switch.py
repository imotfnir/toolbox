class PowerSwitch():
    def __init__(self, ipv4_ip: str, ipv4_port: int, port: int) -> None:
        self._ipv4_ip = ipv4_ip
        self._ipv4_port = ipv4_port
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

    def get_ipv4_ip(self) -> str:
        return self._ipv4_ip

    def get_ipv4_ip(self, ip: str) -> None:
        # ToDO
        return

    def get_ipv4_port(self) -> int:
        return self._ipv4_port

    def get_ipv4_port(self, port: int) -> None:
        if (port < 5101):
            self._ipv4_port = 5101
        if (port > 5116):
            self._ipv4_port = 5116
        self._ipv4_port = port
        return
