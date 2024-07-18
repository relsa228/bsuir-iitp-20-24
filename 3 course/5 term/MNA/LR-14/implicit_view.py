import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

a = 0
b = 2
k = 1
T = 0.2
phi = lambda x: 0
g1 = lambda t: 0
g2 = lambda t: 0
f = lambda x, t: x
h = 0.01
t = 0.5 * h * h / k

NK = int((b - a) / h) + 1
NT = int(T / t) + 1


def solve2l():
    M = np.zeros(shape=(NT, NK))
    M[:, 0] = np.array([g1(i) for i in np.linspace(0, T, NT)])
    M[0, :] = np.array([phi(i) for i in np.linspace(a, b, NK)])

    for i in range(1, NT):
        M2 = np.zeros(shape=(NK - 1, NK - 1))
        Y = np.zeros(NK - 1)
        M2[0][0] = -(1 + 2 * k * t / (h * h))
        M2[0][1] = t * k / (h * h)
        Y[0] = -(M[i - 1][1] + t * f(a + i * h, i * t) + k * t * M[i][0] / (h * h))

        for j in range(1, NK - 2):
            M2[j][j - 1] = k * t / (h * h)
            M2[j][j] = -(1 + 2 * k * t / (h * h))
            M2[j][j + 1] = k * t / (h * h)
            Y[j] = -(M[i - 1][j + 1] + t * f(a + j * h, i * t))
        # last equation is approximation from even scheme
        M2[-1][-1] = -1
        M2[-1][-2] = 1
        Y[-1] = h * g2(t * i)

        M[i, 1:] = np.linalg.solve(M2, Y)
    return M


# central difference

def solve2c():
    M = np.zeros(shape=(NT, NK))
    M[:, 0] = np.array([g1(i) for i in np.linspace(0, T, NT)])
    M[0, :] = np.array([phi(i) for i in np.linspace(a, b, NK)])

    for i in range(1, NT):
        M2 = np.zeros(shape=(NK - 1, NK - 1))
        Y = np.zeros(NK - 1)
        M2[0][0] = -(1 + 2 * k * t / (h * h))
        M2[0][1] = t * k / (h * h)
        Y[0] = -(M[i - 1][1] + t * f(a + i * h, i * t) + k * t * M[i][0] / (h * h))

        for j in range(1, NK - 2):
            M2[j][j - 1] = k * t / (h * h)
            M2[j][j] = -(1 + 2 * k * t / (h * h))
            M2[j][j + 1] = k * t / (h * h)
            Y[j] = -(M[i - 1][j + 1] + t * f(a + j * h, i * t))
        # last equation is approximation from even scheme
        M2[-1][-1] = -1
        M2[-1][-3] = 1
        Y[-1] = 2 * h * g2(t * i)

        M[i, 1:] = np.linalg.solve(M2, Y)
    return M


matrix = solve2l()
X = np.linspace(a, b, NK)

for i in range(0, NT, NT // 6):
    plt.plot(X, matrix[i], label=i)
    plt.title("Left difference")
plt.legend()
plt.show()

matrix = solve2c()
X = np.linspace(a, b, NK)

for i in range(0, NT, NT // 6):
    plt.plot(X, matrix[i], label=i)
    plt.title("Central difference")
plt.legend()
plt.show()

# неявная схема, левая разность

tn1 = 25
tn2 = 75

ns = [10, 20, 40, 80, 160]
table = np.zeros(shape=(len(ns), 6))
t = 0.0001
for i in range(len(ns) - 1):
    h = (b - a) / ns[i]
    NK = ns[i]
    NT = int(T / t) + 1

    M1 = solve2l()

    h = (b - a) / ns[i + 1]
    NK = ns[i + 1]
    NT = int(T / t) + 1

    M2 = solve2l()

    sol1l = M1[tn1]
    sol1c = M2[tn1]
    sol2l = M1[tn2]
    sol2c = M2[tn2]

    table[i][0] = ns[i]
    table[i][1] = t
    table[i][2] = sum((sol1c[::2] - sol1l) ** 2)
    table[i][3] = sum((sol2c[::2] - sol2l) ** 2)
    table[i][4] = max(abs(sol1c[::2] - sol1l))
    table[i][5] = max(abs(sol2c[::2] - sol2l))

df = pd.DataFrame(table,
                  columns=['$N$', '$t$', '$s{(t=t_{n1})}$', '$s{(t=t_{n2})}$', '$max{|t_{n1}|}$', '$max{|t_{n2}|}$'])


# неявная схема, центральная разность

tn1 = 25
tn2 = 75

ns = [10, 20, 40, 80, 160]
table = np.zeros(shape=(len(ns), 6))
t = 0.0001
for i in range(len(ns) - 1):
    h = (b - a) / ns[i]
    NK = ns[i]
    NT = int(T / t) + 1

    M1 = solve2c()

    h = (b - a) / ns[i + 1]
    NK = ns[i + 1]
    NT = int(T / t) + 1

    M2 = solve2c()

    sol1l = M1[tn1]
    sol1c = M2[tn1]
    sol2l = M1[tn2]
    sol2c = M2[tn2]

    table[i][0] = ns[i]
    table[i][1] = t
    table[i][2] = sum((sol1c[::2] - sol1l) ** 2)
    table[i][3] = sum((sol2c[::2] - sol2l) ** 2)
    table[i][4] = max(abs(sol1c[::2] - sol1l))
    table[i][5] = max(abs(sol2c[::2] - sol2l))

df = pd.DataFrame(table,
                  columns=['$N$', '$t$', '$s{(t=t_{n1})}$', '$s{(t=t_{n2})}$', '$max{|t_{n1}|}$', '$max{|t_{n2}|}$'])

