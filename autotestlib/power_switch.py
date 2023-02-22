from autotestlib.type import *


class PowerSwitch():
    __poweroff = [":040102f8", ":040202f7", ":040302f6", ":040402f5"]
    __poweron = [":040101f9", ":040201f8", ":040301f7", ":040401f6"]

    def __init__(self, console: ConsoleIp, port: int) -> None:
        self.console = console
        self.port = port

    @property
    def console(self) -> ConsoleIp:
        return self._console

    @console.setter
    def console(self, console: ConsoleIp) -> None:
        self._console = console

    @property
    def port(self) -> int:
        return self._port

    @port.setter
    def port(self, port: int) -> None:
        if port < 1:
            raise ValueError("Power switch port number only can be 1,2,3,4")
        if port > 4:
            raise ValueError("Power switch port number only can be 1,2,3,4")
        self._port = port

    @property
    def poweroff_cmd(self) -> str:
        return self.__poweroff[self.port - 1]

    @property
    def poweron_cmd(self) -> str:
        return self.__poweron[self.port - 1]


if __name__ == "__main__":
    pass
