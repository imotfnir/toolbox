import pytest
from library.custom_type import *


ipv4_obj = Ipv4(ip='192.168.162.2', port=5102)
console_obj = ConsoleIp(ip="192.168.0.1", port=5101)
ssh_obj = SshIp(ip="192.168.0.1")


def ipv4_item(obj: Ipv4) -> None:
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


def ipv4_exception_item(obj: Ipv4) -> None:
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


def console_item(obj: Ipv4) -> None:
    obj.ip = "10.10.10.10"
    assert obj.ip == "10.10.10.10"
    obj.port = 5101
    assert obj.port == 5101
    obj.port = 5116
    assert obj.port == 5116
    return


def ssh_item(obj: Ipv4) -> None:
    obj.ip = "10.58.151.139"
    assert obj.ip == "10.58.151.139"
    obj.port = 22
    assert obj.port == 22
    return
# Test


def test_ipv4() -> None:
    ipv4_item(ipv4_obj)
    console_item(ipv4_obj)
    return


def test_ipv4_exception() -> None:
    ipv4_exception_item(ipv4_obj)
    return


def test_console() -> None:
    console_item(console_obj)
    return


def test_console_exception() -> None:
    ipv4_exception_item(console_obj)
    with pytest.raises(ValueError):
        console_obj.port = 5117
    with pytest.raises(ValueError):
        console_obj.port = 5100
    with pytest.raises(ValueError):
        console_obj.port = 2000
    return


def test_ssh() -> None:
    ssh_item(ssh_obj)
    return


def test_ssh_exception() -> None:
    ipv4_exception_item(ssh_obj)
    with pytest.raises(ValueError):
        ssh_obj.port = 8080
    with pytest.raises(ValueError):
        ssh_obj.port = 23
    with pytest.raises(ValueError):
        ssh_obj.port = 21
    return


if __name__ == "__main__":
    pass
