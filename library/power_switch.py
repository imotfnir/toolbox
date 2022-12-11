from library.custom_type import *


class PowerSwitch():
    def __init__(self, console: ConsoleIp, port: int) -> None:
        self.console = console
        self.port = port

    @property
    def console(self) -> ConsoleIp:
        return self._console

    @console.setter
    def console(self, console: ConsoleIp) -> None:
        self._console = console
        return

    @property
    def port(self) -> int:
        return self._port

    @port.setter
    def port(self, port: int) -> None:
        if (port < 1):
            raise ValueError("Power switch port number only can be 1,2,3,4")
        if (port > 4):
            raise ValueError("Power switch port number only can be 1,2,3,4")
        self._port = port
        return


if __name__ == "__main__":
    pass
