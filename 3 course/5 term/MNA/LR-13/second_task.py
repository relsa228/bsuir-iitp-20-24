import matplotlib.pyplot as plt
import numpy
from scipy import integrate

Ua, Ub = 3, 3
a, b = 1, 2
h = (b - a) / 150

f = lambda x: 1 / x

# Входные данные для случаев а) k1 << k2, б) k1 >> k2
test_values = [
    [5, 500],
    [500, 5],
]


def k_two_materials(x, k1, k2):
    if a <= x <= (b + a) * 0.5:
        return k1
    return k2


def k_three_materials(x, k1, k2, k3):
    if a <= x <= (a + (b - a) / 3):
        return k1
    elif (a + 2 * (b - a) / 3) < x <= b:
        return k3
    return k2


def c(x1, x2, *k_values):
    if len(k_values) == 2:
        return (integrate.quad(lambda x: 1 / k_two_materials(x, *k_values), x1, x2)[0]) ** (-1)
    else:
        return (integrate.quad(lambda x: 1 / k_three_materials(x, *k_values), x1, x2)[0]) ** (-1)


def phi(x1, x2):
    return integrate.quad(f, x1, x2)[0]


def get_delta_integral(x, x0, c):
    if abs(x - x0) - h / 2 < 1e-5:
        return c / 2
    elif abs(x - x0) < h / 2:
        return c
    return 0


def find_answer_2_task(a, b, Ua, Ub, sources=None, *k_values):
    n = int((b - a) / h) + 1

    A = numpy.zeros((n, n))
    g = numpy.zeros((n, 1))

    A[0, 0] = A[-1, -1] = 1
    g[0] = Ua
    g[-1] = Ub
    x_points = numpy.linspace(a, b, n)

    for i in range(1, n - 1):
        A[i, i - 1] = c(x_points[i - 1], x_points[i], *k_values)
        A[i, i] = (- c(x_points[i - 1], x_points[i], *k_values)
                   - c(x_points[i], x_points[i + 1], *k_values))
        A[i, i + 1] = c(x_points[i], x_points[i + 1], *k_values)
        if sources:
            g[i] = - sum(get_delta_integral(x_points[i], x0, c_i) for c_i, x0 in sources)
        else:
            g[i] = - phi(x_points[i] - h / 2, x_points[i] + h / 2)
    return x_points, numpy.linalg.solve(A, g)


def plot_result(x, y, label):
    plt.rcParams["figure.figsize"] = (8, 8)
    plt.plot(x, y, label=label)
    plt.grid()
    plt.legend()
    plt.show()


for k1, k2 in test_values:
    x, y = find_answer_2_task(a, b, Ua, Ub, None, k1, k2)
    #plot_result(x, y, f'k: {k1}, {k2}')

#а) k1 < k2 < k3;
#k1, k2, k3 = 5, 500, 1000
#x, y = find_answer_2_task(a, b, Ua, Ub, None, k1, k2, k3)
#plot_result(x, y, f'k: {k1}, {k2}, {k3}')

#б) k1 > k2 > k3;
#k1, k2, k3 = 1000, 500, 5
#x, y = find_answer_2_task(a, b, Ua, Ub, None, k1, k2, k3)
#plot_result(x, y, f'k: {k1}, {k2}, {k3}')

# в) k1 = k, k2 = 2k, k3 = k;
#k1, k2, k3 = 250, 500, 250
#x, y = find_answer_2_task(a, b, Ua, Ub, None, k1, k2, k3)
#plot_result(x, y, f'k: {k1}, {k2}, {k3}')

# г) k1 = 20k, k2 = k, k3 = 20k;
#k1, k2, k3 = 300, 5, 300
#x, y = find_answer_2_task(a, b, Ua, Ub, None, k1, k2, k3)
#plot_result(x, y, f'k: {k1}, {k2}, {k3}')

sources = [
    [(10, a + (b - a) / 2)],
    [(50, a + (b - a) / 4), (50, a + 3 * (b - a) / 4)],
    [(70, a + (b - a) / 4), (30, a + 3 * (b - a) / 4)],
]

k1, k2, k3 = 1000, 50, 1000
for src in sources:
    x, y = find_answer_2_task(a, b, Ua, Ub, src, k1, k2, k3)
    plot_result(x, y, f'k: {k1}, {k2}, {k3} \nsources:{src}')

my_example = [(100, a + 7 * (b - a) / 10), (100, a + 9 * (b - a) / 10)]
k1, k2, k3 = 1000, 50, 1000
x, y = find_answer_2_task(a, b, Ua, Ub, my_example, k1, k2, k3)
plot_result(x, y, f'k: {k1}, {k2}, {k3} \nsources:{my_example}')
