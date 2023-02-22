#!/usr/bin/env python
import autotestlib.session as cc
import autotestlib.type as Type

import pexpect
import paramiko


if __name__ == "__main__":
    # ac = Type.Account(ipv4=Type.Ipv4('192.168.162.2', 5101),
    #                   username='administrator',
    #                   password='ufispace')
    # console = cc.Console(ac)
    # console.connect()
    # x86 = console.get_ssh_ip()
    # print(x86.ip)
    # bmc = console.get_bmc_ip()
    # print(bmc.ip)

    ac2 = Type.Account(ipv4=Type.SshIp('192.168.165.164'),
                       username='root',
                       password='ufispace')
    x86 = cc.X86Terminal(ac2)
    x86.connect()
    print(x86.lspci())
    print(x86.get_bios_version().raw)
