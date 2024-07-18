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
    A = 0.4
    B = 1.4
    first = 1.2
    last = 3.2
    iteration_count = 0
    points = []
    current = []
    prev = []
    h = 0
    while True:
        h = get_h(A, B, n)
        points = list(np.linspace(A, B, n + 1))

        del points[0]

        a = [(1 / h ** 2) + 0.5 * x / (2 * h) for x in points]
        b = [-(2 / h ** 2) + 1 for x in points]
        c = [(1 / h ** 2) + (-0.5 * x / (2 * h)) for x in points]
        d = [2 for x in points]

        d[0] = d[0] - a[0] * 1.2

        a[-1] = a[-1] - c[-1] / (h + 3)
        b[-1] = b[-1] + 4 * c[-1] / (h + 3)
        d[-1] = d[-1] - c[-1] * 3.2 * h / (h + 3)
        c[-1] = 0

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

    mpl.figure()
    points.insert(0, A)
    current.insert(0, 1.2)

    return points, current, h


def task_3():
    points_1, currect_1, h_1 = task_proc(1000, 0.05)
    points_2, currect_2, h_2 = task_proc(1000, 0.005)
    points_3, currect_3, h_3 = task_proc(1000, 0.0005)
    mpl.plot(points_1, currect_1, label="Task 2\nh = {}".format(h_1), linewidth=0.5)
    mpl.plot(points_2, currect_2, label="Task 2\nh = {}".format(h_2), linewidth=0.5)
    mpl.plot(points_3, currect_3, label="Task 2\nh = {}".format(h_3), linewidth=0.5)
    mpl.legend()
    mpl.grid(True)
    mpl.show()
