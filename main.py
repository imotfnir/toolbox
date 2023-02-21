#!/usr/bin/env python
from fabric.api import local, run, env
import autotestlib.connection as cc
import autotestlib.custom_type as Type
import pexpect


if __name__ == "__main__":
    ac = Type.Account(ipv4=Type.Ipv4('192.168.162.2', 5101),
                      username='administrator',
                      password='ufispace')
    console = cc.Console(ac)
    console.connect()
    x86 = console.get_ssh_ip()
    print(x86.ip)
    bmc = console.get_bmc_ip()
    print(bmc.ip)
