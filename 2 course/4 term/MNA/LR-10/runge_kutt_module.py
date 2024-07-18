import numpy as np


def runge_kutta_method(function, t0, tn, n, y0):
    h = abs(tn - t0) / n
    t = np.linspace(t0, tn, n + 1)
    y = np.zeros(n + 1)
    y[0] = y0
    for i in range(0, n):
        K1 = function(t[i], y[i])
        K2 = function(t[i] + h / 2, y[i] + K1 * h / 2)
        K3 = function(t[i] + h / 2, y[i] + K2 * h / 2)
        K4 = function(t[i] + h, y[i] + K3 * h)
        y[i + 1] = y[i] + h * (K1 + 2 * K2 + 2 * K3 + K4) / 6

    return tn, y
