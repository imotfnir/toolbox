#!/usr/bin/env python
import library.connection as cc


PROMPT = "root@ubuntu:~#"
console = cc.Console(
    ip='192.168.162.2',
    username='administrator',
    password='ufispace',
    port='5101')


console.send_command("\r\n")
console.wait_for_pattern("ubuntu login:")
console.send_command("root")
console.wait_for_pattern("Password:")
console.send_command("ufispace")

# console.wait_for_pattern(PROMPT)
# console.send_command("dmidecode -s bios-version")
# console.wait_for_pattern(PROMPT)
# console.send_command("lscpu")
# console.wait_for_pattern(PROMPT)
