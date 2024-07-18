import numpy as np


def jacobian(f, x, approximation):
    range_of_function = len(x)
    jac = np.zeros([range_of_function, range_of_function])
    f0 = f(x)
    for i in np.arange(0, range_of_function, 1):
        tt = x[i]
        x[i] = tt + approximation
        f1 = f(x)
        x[i] = tt
        jac[:, i] = (f1 - f0) / approximation
    return jac, f0


def newton_method(f, x, eps, approximation):
    iterMax = 1000
    for iterations in range(iterMax):
        jac, fO = jacobian(f, x, approximation)

        if np.sqrt(np.dot(fO, fO) / len(x)) < eps:
            return x, iterations

        dx = np.linalg.solve(jac, fO)
        x = x - dx
    return -1, -1
