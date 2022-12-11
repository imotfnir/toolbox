import pytest
from library.custom_type import *


ipv4 = Ipv4(ip='192.168.162.2', port=5102)


def test_ipv4_port() -> None:
    assert ipv4.port == 5102
    ipv4.port = 2000
    assert ipv4.port == 2000
    ipv4.port = 1
    assert ipv4.port == 1
    ipv4.port = 65535
    assert ipv4.port == 65535
    return


def test_ipv4_port_exception() -> None:
    with pytest.raises(ValueError):
        ipv4.port = 65536
    with pytest.raises(ValueError):
        ipv4.port = -1
    return


def test_ipv4_ip() -> None:
    ipv4.ip = "10.60.120.10"
    assert ipv4.ip == "10.60.120.10"
    ipv4.ip = "255.255.255.255"
    assert ipv4.ip == "255.255.255.255"
    return


def test_ipv4_ip_exception() -> None:
    with pytest.raises(ValueError):
        ipv4.ip = "255.255.1.320"
    with pytest.raises(ValueError):
        ipv4.ip = "3221225985"
    with pytest.raises(ValueError):
        ipv4.ip = "255.255"
    return


console = ConsoleIp(ip="192.168.0.1", port=5101)


def test_console_ip() -> None:
    console.ip = "10.10.10.10"
    assert console.ip == "10.10.10.10"
    with pytest.raises(ValueError):
        console.ip = "259.10.23.5"
    return


def test_console_port() -> None:
    console.port = 5101
    assert console.port == 5101
    console.port = 2
    assert console.port == 5102
    with pytest.raises(ValueError):
        console.port = 8080
    with pytest.raises(ValueError):
        console.port = 2000
    return


ssh = SshIp(ip="192.168.0.1", port=22)


def test_ssh_ip() -> None:
    ssh.ip = "10.58.151.139"
    assert ssh.ip == "10.58.151.139"
    with pytest.raises(ValueError):
        ssh.ip = "112.114.555.5"
    return


def test_ssh_port() -> None:
    ssh.port = 22
    assert ssh.port == 22
    with pytest.raises(ValueError):
        ssh.port = 8080
    return


if __name__ == "__main__":
    pass
