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


def solve1l():
    M = np.zeros(shape=(NT, NK))
    M[:, 0] = np.array([g1(i) for i in np.linspace(0, T, NT)])
    M[0, :] = np.array([phi(i) for i in np.linspace(a, b, NK)])

    for i in range(1, NT):
        for j in range(1, NK - 1):
            xj = a + j * h
            M[i][j] = k * M[i - 1][j + 1] * t / (h * h) + \
                      (1 - 2 * k * t / (h * h)) * M[i - 1][j] + \
                      k * M[i - 1][j - 1] * t / (h * h) + \
                      t * f(xj, i * t)
        M[i][-1] = M[i][-2] + h * g2(t * i)
    return M


def solve1c():
    M = np.zeros(shape=(NT, NK))
    M[:, 0] = np.array([g1(i) for i in np.linspace(0, T, NT)])
    M[0, :] = np.array([phi(i) for i in np.linspace(a, b, NK)])

    for i in range(1, NT):
        for j in range(1, NK - 1):
            xj = a + j * h
            M[i][j] = k * M[i - 1][j + 1] * t / (h * h) + \
                      (1 - 2 * k * t / (h * h)) * M[i - 1][j] + \
                      k * M[i - 1][j - 1] * t / (h * h) + \
                      t * f(xj, i * t)
        M[i][-1] = M[i][-3] + 2 * h * g2(t * i)
    return M


matrix = solve1l()
X = np.linspace(a, b, NK)

for i in range(0, NT, NT // 6):
    plt.plot(X, matrix[i], label=i)
    plt.title("Левая разность")
plt.legend()
plt.show()

matrix = solve1c()
X = np.linspace(a, b, NK)

for i in range(0, NT, NT // 6):
    plt.plot(X, matrix[i], label=i)
    plt.title("Центральная разность")
plt.legend()
plt.show()

tn1 = 25
tn2 = 75

ns = [10, 20, 40, 80, 160]
table = np.zeros(shape=(len(ns), 6))
t = 0.0001
for i in range(len(ns) - 1):
    h = (b - a) / ns[i]
    NK = ns[i]
    NT = int(T / t) + 1

    M1 = solve1l()

    h = (b - a) / ns[i + 1]
    NK = ns[i + 1]
    NT = int(T / t) + 1

    M2 = solve1l()

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
                  columns=['N', 't', 's(t=t_{n1})', 's(t=t_{n2})', 'max|t_{n1}|', 'max|t_{n2}|'])
df[:-1]

# явная схема, центральная разность

tn1 = 25
tn2 = 75

ns = [10, 20, 40, 80, 160]
table = np.zeros(shape=(len(ns), 6))
t = 0.0001
for i in range(len(ns) - 1):
    h = (b - a) / ns[i]
    NK = ns[i]
    NT = int(T / t) + 1

    M1 = solve1c()

    h = (b - a) / ns[i + 1]
    NK = ns[i + 1]
    NT = int(T / t) + 1

    M2 = solve1c()

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
                  columns=['N', 't', 's(t=t_{n1})', 's(t=t_{n2})', 'max|t_{n1}|', 'max|t_{n2}|'])
df[:-1]
