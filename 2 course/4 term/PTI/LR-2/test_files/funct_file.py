import math

c = 42


def f(x):
    a = 123
    return math.sin(x * a * c)


def take_globals():
    return globals()
