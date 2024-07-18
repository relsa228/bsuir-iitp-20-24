import numpy as np
import matplotlib.pyplot as plt

a = 2
b = 3
p = lambda x, y: np.tan(np.cos(np.pi * y / b))
q = lambda x, y: np.exp(np.sin(np.pi * x / a)) * np.sin(2 * np.pi * y / b)
NX = 100
NY = 100
hx = a / NX
hy = b / NY
t = 0.001
NT = 10000


def solve2():
    MOM = np.zeros(shape=(NT, NX, NY))
    X = np.array([np.linspace(-a / 2, a / 2, NX)]).T
    Y = np.array([np.linspace(-b / 2, b / 2, NY)])
    MOM[0, 1:-1, :] = p(X[1:-1], Y)
    MOM[1, 1:-1, 1:-1] = p(X[1:-1], Y[:, 1:-1]) + t * q(X[1:-1], Y[:, 1:-1]) + (t / hx) ** 2 / 2 * (
            p(X[2:], Y[:, 1:-1]) - 2 * p(X[1:-1], Y[:, 1:-1]) + p(X[:-2], Y[:, 1:-1])) + (t / hy) ** 2 / 2 * (
                                 p(X[1:-1], Y[:, 2:]) - 2 * p(X[1:-1], Y[:, 1:-1]) + p(X[1:-1], Y[:, :-2]))
    MOM[1, 1:-1, 0] = MOM[1, 1:-1, 1]
    MOM[1, 1:-1, -1] = MOM[1, 1:-1, -2]

    for i in range(2, NT):
        MOM[i, 1:-1, 1:-1] = (t / hx) ** 2 * (MOM[i - 1, 2:, 1:-1] - 2 * MOM[i - 1, 1:-1, 1:-1] +
                                              MOM[i - 1, :-2, 1:-1]) + (t / hy) ** 2 * (MOM[i - 1, 1:-1, 2:] - 2 *
                                                                                        MOM[i - 1, 1:-1, 1:-1] +
                                                                                        MOM[i - 1, 1:-1, :-2]) + 2 * \
                             MOM[i - 1, 1:-1, 1:-1] - MOM[i - 2, 1:-1, 1:-1]
        MOM[i, 1:-1, 0] = MOM[i, 1:-1, 1]
        MOM[i, 1:-1, -1] = MOM[i, 1:-1, -2]

    return MOM


sol = solve2()

for i in range(0, NT, NT // 40):
    plt.imshow(sol[i], vmin=-0.8, extent=(-a / 2, a / 2, -b / 2, b / 2))
    plt.show()
