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
    return


if __name__ == "__main__":
    pass
