import pytest
from library.custom_type import *


ipv4_obj = Ipv4(ip='192.168.162.2', port=5102)
console_obj = ConsoleIp(ip="192.168.0.1", port=5101)
ssh_obj = SshIp(ip="192.168.0.1", port=22)


def ipv4(obj: Ipv4) -> None:
    obj.port = 5102
    assert obj.port == 5102
    obj.port = 2000
    assert obj.port == 2000
    obj.port = 1
    assert obj.port == 1
    obj.port = 65535
    assert obj.port == 65535
    obj.ip = "0.0.0.0"
    assert obj.ip == "0.0.0.0"
    obj.ip = "10.60.120.10"
    assert obj.ip == "10.60.120.10"
    obj.ip = "255.255.255.255"
    assert obj.ip == "255.255.255.255"
    return


def ipv4_exception(obj: Ipv4) -> None:
    with pytest.raises(ValueError):
        obj.port = 65536
    with pytest.raises(ValueError):
        obj.port = -1
    with pytest.raises(ValueError):
        obj.ip = "255.255.1.320"
    with pytest.raises(ValueError):
        obj.ip = "3221225985"
    with pytest.raises(ValueError):
        obj.ip = "255.255"
    return


def test_ipv4() -> None:
    ipv4(ipv4_obj)
    return


def test_ipv4_exception() -> None:
    ipv4_exception(ipv4_obj)
    return


def test_console() -> None:
    console_obj.ip = "10.10.10.10"
    assert console_obj.ip == "10.10.10.10"
    console_obj.port = 5101
    assert console_obj.port == 5101
    console_obj.port = 2
    assert console_obj.port == 5102
    return


def test_console_exception() -> None:
    ipv4_exception(console_obj)
    with pytest.raises(ValueError):
        console_obj.ip = "259.10.23.5"
    with pytest.raises(ValueError):
        console_obj.port = 8080
    with pytest.raises(ValueError):
        console_obj.port = 2000
    return


def test_ssh() -> None:
    ssh_obj.ip = "10.58.151.139"
    assert ssh_obj.ip == "10.58.151.139"
    with pytest.raises(ValueError):
        ssh_obj.ip = "112.114.555.5"
    return


def test_ssh_exception() -> None:
    ipv4_exception(ssh_obj)
    ssh_obj.port = 22
    assert ssh_obj.port == 22
    with pytest.raises(ValueError):
        ssh_obj.port = 8080
    return


if __name__ == "__main__":
    pass
