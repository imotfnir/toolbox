#!/usr/bin/env python
import autotestlib.connection as cc
import autotestlib.custom_type as Type
import pexpect


PROMPT = "root@ubuntu:~#"
console = cc.Console(
    ipv4=Type.Ipv4('192.168.162.2', 5101),
    username='administrator',
    password='ufispace',
)
console.connect()
x86 = console.get_ssh_ip()
print(x86.ip)
bmc = console.get_bmc_ip()
print(bmc.ip)
