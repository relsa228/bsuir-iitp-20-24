import numpy as np
from Chord_module import get_f_from_polinom
from Chord_module import borders_of


def newton_method(polinom, l, r, eps):
    phi = get_f_from_polinom(polinom)
    P0 = np.polyder(polinom).tolist()
    der_phi = get_f_from_polinom(P0)
    iters = 0
    P00 = np.polyder(P0).tolist()
    der_der_phi = get_f_from_polinom(P00)
    if phi(r) * der_der_phi(r) > 0:
        x0 = r
    else:
        x0 = l

    def recurent(xn_1):
        return xn_1 - phi(xn_1) / der_phi(xn_1)

    while abs(x0 - recurent(x0)) > eps:
        x0 = recurent(x0)
        iters += 1

    return iters, x0


def exec_newton(f, poly, eps):
    bounds = borders_of(-10, 10, f)
    r0 = bounds[0][1]
    return newton_method(poly, -10, r0, eps)
