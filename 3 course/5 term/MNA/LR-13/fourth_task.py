import matplotlib.pyplot as plt
import numpy


a, b = 0, 2
Ua, Ub = 4, 1
k = 1
f = lambda x, t: x
h = (b - a) / 10
dt = 0.45 * h ** 2 / k
phi = lambda x: 0
t = 0.2
g1 = lambda t: 0
g2 = lambda t: 0


def find_answer_4_task(a, b, Ua, Ub, k, f, dt, phi, t, g1, g2):
    n_t = int(t / dt) + 1
    m_x = int((b - a) / h) + 1
    x_points = numpy.linspace(a, b, m_x)
    t_points = numpy.linspace(0, t, n_t)
    A = numpy.zeros((n_t, m_x))
    A[0] = [phi(x) for x in x_points]
    A[:, 0] = numpy.array([g1(t_i) for t_i in numpy.linspace(0, t, n_t)])
    A[:, -1] = numpy.array([g2(t_i) for t_i in numpy.linspace(0, t, n_t)])

    for i in range(n_t - 1):
        for j in range(1, m_x - 1):
            A[i + 1, j] = (k * dt / h ** 2 * A[i, j - 1] + (1 - 2 * k * dt / h ** 2) * A[i, j]
                           + k * dt / h ** 2 * A[i, j + 1] + dt * f(x_points[j], t_points[i]))
    return x_points, t_points, A


def show_plots(x, A):
    plt.rcParams["figure.figsize"] = (8, 8)
    for i in range(0, int(t / dt) + 1, 2):
        plt.plot(x, A[i], label=fr't={i}$\tau$')
    plt.grid()
    plt.legend()
    plt.show()


def show_3d_plot(x, t, A):
    fig = plt.figure()
    ax = fig.gca(projection='3d')
    for i in range(len(t) - 1, - 1, -1):
        x = x
        y = [i * dt] * len(x)
        z = A[i]
        ax.plot(x, y, z)
    plt.show()


x_row, t_row, A = find_answer_4_task(a, b, Ua, Ub, k, f, dt, phi, t, g1, g2)
show_plots(x_row, A)
show_3d_plot(x_row, t_row, A)