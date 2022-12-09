import pytest
from library.custom_type import Ipv4


ipv4 = Ipv4(ip='192.168.162.2', port=5102)


def test_ipv4_port() -> None:
    assert ipv4.port == 5102
    ipv4.port = 2000
    assert ipv4.port == 5102
    ipv4.port = 1
    assert ipv4.port == 5101
    ipv4.port = 5100
    assert ipv4.port == 5101
    ipv4.port = 5116
    assert ipv4.port == 5116
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


if __name__ == "__main__":
    pass
