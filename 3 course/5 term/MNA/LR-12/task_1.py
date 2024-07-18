import numpy as np
import math
import matplotlib.pyplot as mpl


def approx_method(n, a, b, y_a, y_b, f, p):
    x = np.linspace(a, b, num=n + 1)
    h = (b - a) / (n + 1)
    a_s = [-1] * (n - 1)
    c_s = [-(2 + h ** 2 * p(i)) for i in x[1:-1]]
    b_s = [-1] * (n - 1)
    f_s = [h ** 2 * f(i) for i in x[1:-1]]
    A_s = [0, b_s[0] / c_s[0]]
    B_s = [0, f_s[0] / c_s[0]]

    for i in range(1, n - 2):
        A_s.append(b_s[i] / (c_s[i] - a_s[i] * A_s[i]))
        B_s.append((f_s[i] + a_s[i] * B_s[i]) / (c_s[i] - a_s[i] * A_s[i]))

    y = [y_b, (f_s[n - 4] + a_s[n - 4] * B_s[n - 4]) / (c_s[n - 4] - a_s[n - 4] * A_s[n - 4])]

    for (A, B) in list(zip(reversed(A_s), reversed(B_s)))[:-1]:
        y.append(A * y[-1] + B)

    y.append(y_a)
    y = list(reversed(y))

    return x, np.array(y), h


def task_1():
    k = 4
    p = lambda x: -(1 + math.cos(k) * x ** 2) / math.sin(k)
    f = lambda x: -1 / math.sin(k)
    for n in range(3, 10):
        x1, y1, res_h = approx_method(n, -1, 1, 0, 0, f, p)
        print(f"Шаг: {res_h}")
        mpl.plot(x1, y1)
    mpl.show()
