import numpy as np


def eigenvalue(matrix_a, v):
    Av = matrix_a.dot(v)
    return v.dot(Av)


def power_iteration_method(matrix_a, eps):
    n, d = matrix_a.shape
    v = np.ones(d) / np.sqrt(d)
    ev = eigenvalue(matrix_a, v)

    while True:
        Av = matrix_a.dot(v)
        v_new = Av / np.linalg.norm(Av)

        ev_new = eigenvalue(matrix_a, v_new)
        if np.abs(ev - ev_new) < eps:
            break

        v = v_new
        ev = ev_new

    return ev_new, v_new
