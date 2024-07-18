from sympy import *
import numpy as np
import Shturm_module as sm


def get_f_from_polinom(polinom):
    def f(x):
        val = polinom[0]
        for i in range(len(polinom) - 1):
            val = val * x + polinom[i + 1]
        return val
    return f


def borders_of(a, b, f):
    x = Symbol('x')
    shturm_row = sm.build_shturm_row(f)

    if sm.find_n(shturm_row, a, x) - sm.find_n(shturm_row, b, x) == 0:
        return []
    if sm.find_n(shturm_row, a, x) - sm.find_n(shturm_row, b, x) == 1:
        return [(a, b)]
    m = a + (b - a) / (1.5 + np.random.random())
    return borders_of(a, m, f) + borders_of(m, b, f)


def chord_method(polinom, l, r, eps, first):
    phi = get_f_from_polinom(polinom)
    P0 = np.polyder(polinom).tolist()
    P00 = np.polyder(P0).tolist()
    der_der_phi = get_f_from_polinom(P00)
    iters = 0
    if phi(r) * der_der_phi(r) > 0:
        def recurent(xn_1):
            return xn_1 - phi(xn_1) * (r - xn_1) / (phi(r) - phi(xn_1))

        x0 = l
        while abs(recurent(x0) - x0) > eps:
            x0 = recurent(x0)
            iters += 1
    else:
        def recurent(xn_1):
            return xn_1 - phi(xn_1) * (l - xn_1) / (phi(l) - phi(xn_1))

        x0 = first
        while abs(recurent(x0) - x0) > eps:
            x0 = recurent(x0)
            iters += 1

    return iters, x0


def exec_chord_method(f, polyn, eps, first):
    bounds = borders_of(-10, 10, f)
    l = bounds[0][0]
    r = bounds[0][1]
    return chord_method(polyn, l, r, eps, first)
