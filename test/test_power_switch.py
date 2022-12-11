import pytest
from library.power_switch import *


console = ConsoleIp(ip="192.168.162.2", port=5116)
ps = PowerSwitch(console=console, port=4)


def ps_item(obj: PowerSwitch) -> None:
    obj.port = 1
    assert obj.port == 1
    obj.port = 4
    assert obj.port == 4
    return


def ps_exception_item(obj: PowerSwitch) -> None:
    with pytest.raises(ValueError):
        obj.port = 5
    with pytest.raises(ValueError):
        obj.port = 0
    return


def test_ps():
    ps_item(ps)
    return


def test_ps_exception():
    ps_exception_item(ps)
    return


if __name__ == "__main__":
    pass
