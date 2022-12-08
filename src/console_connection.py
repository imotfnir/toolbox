import pexpect
import time


class console_connection:
    delay = 0.2

    def __init__(self, ip, username, password, port):
        self._ip = ip
        self._username = username
        self._password = password
        self._port = port
        self._child = pexpect.spawn('ssh',
                                    ['-o',
                                     'StrictHostKeyChecking=no',
                                     '-o',
                                     'UserKnownHostsFile=/dev/null',
                                     '-l',
                                     self._username,
                                     self._ip,
                                     '-p',
                                     self._port])
        if(self.wait_for_pattern('[P|p]assword:')):
            print('Terminal server Enter password')
            self.send_command(self._password)
            print('Terminal server Login success') if self.wait_for_pattern(
                'Suspend') else print('Login failed')
        else:
            print("Connection Timeout")

    def send_command(self, command):
        self._child.sendline(command)
        time.sleep(self.delay)
        return self

    def wait_for_pattern(self, pattern):
        return self._child.expect([pexpect.TIMEOUT, pattern])

    def where_am_i(self, args):
        pass


if __name__ == "__main__":
    pass
