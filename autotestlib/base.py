from types import SimpleNamespace
from sys import stderr
import json

import autotestlib.type as Type


def print_err(*args, **kwargs):
    print(*args, file=stderr, **kwargs)


class Decoding:
    @classmethod
    def decode_config(cls, file):
        with open(file=file, mode="r", encoding="utf-8") as f:
            return json.load(f)
