import numpy as np
import matplotlib.pyplot as plt

L = 15
u = 0.1
E = 86e9
rho = 8.5e3
p = lambda x: -4 * u / (L ** 2) * x ** 2 + 4 * u / L * x
q = lambda x: 0
NK = 100
h = L / NK
c = 0.0001
t = c * h
NT = 400


def solve1():
    M = np.zeros(shape=(NT, NK))
    X = np.linspace(0, L, NK)
    M[0, :] = np.array([p(i) for i in np.linspace(0, L, NK)])
    M[:, 0] = np.array([0 for i in np.linspace(0, u, NT)])
    M[:, -1] = np.array([0 for i in np.linspace(0, u, NT)])
    M[1, 1:-1] = t * q(X[1:-1]) + p(X[1:-1]) + t ** 2 * E / (2 * rho * h ** 2) * (p(X[2:]) - 2 * p(X[1:-1]) + p(X[:-2]))

    for i in range(2, NT):
        M[i, 1:-1] = (t ** 2 * E) / (rho * h ** 2) * (M[i - 1, 2:] - 2 * M[i - 1, 1:-1] + M[i - 1, :-2]) + 2 * M[i - 1,
                                                                                                               1:-1] - M[
                                                                                                                       i - 2,
                                                                                                                       1:-1]
    return M


matrix = solve1()
X = np.linspace(0, L, NK)

for i in range(0, NT, NT // 19):
    plt.plot(X, matrix[i], label=i)
# plt.legend()
plt.show()
