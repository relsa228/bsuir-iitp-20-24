import numpy as np

from runge_kutt_module import runge_kutta_method


def adams_bash(funct, n, t0, tn, y0):
    h = abs(tn - t0) / n
    t = np.linspace(t0, tn, n + 1)
    y = np.zeros(n + 1)
    y[0:3] = runge_kutta_method(funct, t0, t0 + 2 * h, 2, y0)[1]
    K1 = funct(t[1], y[1])
    K2 = funct(t[0], y[0])
    for i in range(2, n):
        K3 = K2
        K2 = K1
        K1 = funct(t[i], y[i])
        y[i + 1] = y[i] + h * (23 * K1 - 16 * K2 + 5 * K3) / 12

    return tn, y
