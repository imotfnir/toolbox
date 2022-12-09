import pytest
from library.custom_type import Ipv4


ipv4 = Ipv4(ip='192.168.162.2', port=5102)


def test_ipv4_port() -> None:
    assert ipv4.get_port() == 5102
    ipv4.set_port(2000)
    assert ipv4.get_port() == 5102
    ipv4.set_port(1)
    assert ipv4.get_port() == 5101
    ipv4.set_port(5100)
    assert ipv4.get_port() == 5101
    ipv4.set_port(5116)
    assert ipv4.get_port() == 5116
    return


def test_ipv4_ip() -> None:
    ipv4.set_ip("10.60.120.10")
    assert ipv4.get_ip() == "10.60.120.10"
    ipv4.set_ip("255.255.255.255")
    assert ipv4.get_ip() == "255.255.255.255"
    return


def test_ipv4_ip_exception() -> None:
    with pytest.raises(ValueError):
        ipv4.set_ip("255.255.1.320")
    with pytest.raises(ValueError):
        ipv4.set_ip("3221225985")
    with pytest.raises(ValueError):
        ipv4.set_ip("255.255")
    return


if __name__ == "__main__":
    ipv4.set_ip("10.60.120.10")
    print(type("110.60.150.10"))
    ipv4.set_ip("255.255.255.255")
    print(ipv4.get_ip())
