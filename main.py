#!/usr/bin/env python
import autotestlib.base as Base
import autotestlib.session as s
import autotestlib.type as Type
import autotestlib.system_undertest as Sut

import pexpect
import paramiko


if __name__ == "__main__":
    cip: Type.ConsoleIp = Type.ConsoleIp(ip="192.168.162.2", port=5101)
    dut = Sut.SystemUnderTest(cip)
    dut.connect_console()
    dut.update()
    dut.connect_x86()
    print(dut.x86.lspci())
    print(dir(dut))
