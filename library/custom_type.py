class Ipv4:
    def __init__(self, ip: str, port: int) -> None:
        self._ip = ip
        self._port = port
        return

    def get_ip(self) -> str:
        return self._ip

    def set_ip(self) -> None:
        # ToDo
        return

    def get_port(self) -> int:
        return self._port

    def set_port(self, port: int) -> None:
        if (port < 5101):
            self._port = 5101
        if (port > 5116):
            self._port = 5116
        self._port = port
        return
