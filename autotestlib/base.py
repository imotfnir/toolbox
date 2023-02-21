from sys import stderr


def print_err(*args, **kwargs):
    print(*args, file=stderr, **kwargs)
