import math
import numpy
import matplotlib.pyplot as plt

a, b = 0.2, 1.2
Ua, Ub = 4, 1
k = lambda x: x ** 3
f = lambda x: 1 + x ** (1 / 3)
h = 0.1
dt = 0.001


def find_answer_3_task(phi, a, b, Ua, Ub, k, f, h, dt):
    n_t = int(t / dt) + 1
    m_x = int((b - a) / h) + 1
    x_points = numpy.linspace(a, b, m_x)
    t_points = numpy.linspace(0, t, n_t)
    A = numpy.zeros((n_t, m_x))
    A[:, 0] = Ua
    A[:, -1] = Ub
    A[0] = [phi(x) for x in x_points]
    for i in range(n_t - 1):
        for j in range(1, m_x - 1):
            A[i + 1, j] = (dt * k(x_points[j] - h / 2) / (h ** 2) * A[i, j - 1]
                           + (1 - dt * (k(x_points[j] - h / 2) + k(x_points[j] + h / 2)) / (h ** 2)) * A[i, j]
                           + dt * k(x_points[j] + h / 2) / (h ** 2) * A[i, j + 1]
                           + dt * f(x_points[j]) * (1 - math.exp(-t_points[i])))

    return x_points, t_points, A


def show_plots(x, A, t_values):
    for i in t_values:
        plt.plot(x, A[i], label=fr't={i}$\tau$')
    plt.grid()
    plt.legend()
    plt.rcParams["figure.figsize"] = (8, 8)
    plt.show()


def show_3d_plot(x, t, A):
    fig = plt.figure()
    ax = fig.gca(projection='3d')
    for i in range(len(t) - 1, -1, -50):
        y = [i * dt] * len(x)
        z = A[i]
        ax.plot(x, y, z)
    plt.show()


t_values = [0, 5, 20, 100, 200, 400, 700, 1000]
t = 1000 * dt

#phi = lambda x: 4
#x_row, t_row, A = find_answer_3_task(phi, a, b, Ua, Ub, k, f, h, dt)
#show_plots(x_row, A, t_values)
#show_3d_plot(x_row, t_row, A)

#phi = lambda x: math.log(x) + math.sin(567) * x ** (1/2)
#x_row, t_row, A = find_answer_3_task(phi, a, b, Ua, Ub, k, f, h, dt)
#show_plots(x_row, A, t_values)
#show_3d_plot(x_row, t_row, A)

#phi = lambda x: math.sinh(x) ** math.log(2 * x) + math.exp(x/2)
#x_row, t_row, A = find_answer_3_task(phi, a, b, Ua, Ub, k, f, h, dt)
#show_plots(x_row, A, t_values)
#show_3d_plot(x_row, t_row, A)

phi = lambda x: math.cosh(x) + x ** 12 - math.gamma(x)
x_row, t_row, A = find_answer_3_task(phi, a, b, Ua, Ub, k, f, h, dt)
show_plots(x_row, A, t_values)
show_3d_plot(x_row, t_row, A)
