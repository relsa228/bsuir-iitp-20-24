import numpy as np
import math
import matplotlib.pyplot as mpl

mpl.rc('figure', figsize=(12, 8))


def deep_copy(system: list) -> list:
    return [item for item in system]


def get_h(a: float, b: float, n: int) -> float:
    return (b - a) / n


def check_accuracy(current: list[float], prev: list[float], eps: float) -> bool:
    eps_t = max([math.fabs(current[i * 2] - prev[i]) for i in range(len(prev))])
    if eps_t > eps:
        return False
    return True


def tridiagonal_matrix_algorithm(a: list[float], b: list[float], c: list[float], d: list[float]) -> list[int]:
    AlphaS = [-c[0] / b[0]]
    BetaS = [d[0] / b[0]]
    GammaS = [b[0]]
    n = len(d)
    result = [0 for i in range(n)]

    for i in range(1, n - 1):
        GammaS.append(b[i] + a[i] * AlphaS[i - 1])
        AlphaS.append(-c[i] / GammaS[i])
        BetaS.append((d[i] - a[i] * BetaS[i - 1]) / GammaS[i])

    GammaS.append(b[n - 1] + a[n - 1] * AlphaS[n - 2])
    BetaS.append((d[n - 1] - a[n - 1] * BetaS[n - 2]) / GammaS[n - 1])

    result[n - 1] = BetaS[n - 1]
    for i in reversed(range(n - 1)):
        result[i] = AlphaS[i] * result[i + 1] + BetaS[i]

    return result


def task_proc(n, eps):
    A = 0
    B = 2.3
    C = 1.875
    k1 = 0.4
    k2 = 1.8
    q1 = 3.5
    q2 = 12.8
    iteration_count = 0
    prev = []
    points = []
    current = []
    while True:
        h = get_h(A, B, n)
        points = list(np.linspace(A, B, n))

        a = [-k1 / h ** 2 if x < C else -k2 / h ** 2 for x in points[1:-1]]
        b = [2 * k1 / h ** 2 + q1 if x < C else 2 * k2 / h ** 2 + q2 for x in points[1:-1]]
        c = [-k1 / h ** 2 if x < C else -k2 / h ** 2 for x in points[1:-1]]
        d = [10 * x * (1.2 - x ** 2) for x in points[1:-1]]

        a.insert(0, 0)
        b.insert(0, k1 / h + 0.5)
        c.insert(0, -k1 / h)
        d.insert(0, 0)

        a.append(-k2 / h)
        b.append(k2 / h + 0.5)
        c.append(0)
        d.append(0)

        current = tridiagonal_matrix_algorithm(a, b, c, d)

        if iteration_count != 0 and check_accuracy(current, prev, eps):
            break

        print("\nstep = ", h)
        print("y = ", current)
        print("prev = ", prev)

        prev = deep_copy(current)
        iteration_count += 1
        n *= 2

    print("\nШаг = ", h)
    return points, current, h


def task_4():
    points_1, currect_1, h_1 = task_proc(10000, 0.001)
    points_2, currect_2, h_2 = task_proc(500, 0.0001)
    points_3, currect_3, h_3 = task_proc(10, 0.005)
    mpl.plot(points_1, currect_1, label="Task 4\nh = {}".format(h_1), linewidth=0.5)
    mpl.plot(points_2, currect_2, label="Task 4\nh = {}".format(h_2), linewidth=0.5)
    mpl.plot(points_3, currect_3, label="Task 4\nh = {}".format(h_3), linewidth=0.5)
    mpl.legend()
    mpl.grid(True)
    mpl.show()
