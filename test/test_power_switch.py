import pytest
from autotestlib.power_switch import *


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


def test_ps_command():
    ps.port = 4
    assert ps.poweroff_cmd == ":040402f5"
    assert ps.poweron_cmd == ":040401f6"
    ps.port = 1
    assert ps.poweroff_cmd == ":040102f8"
    assert ps.poweron_cmd == ":040101f9"


if __name__ == "__main__":
    pass
