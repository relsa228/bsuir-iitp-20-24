import random

import numpy as np
import sympy as sp
from prettytable import PrettyTable

x, t = sp.symbols('x t')


# initial condition
a, b = 0, 2
k = 1
# expression of initial function
phi_expr = 0
g1_expr = 0
g2_expr = 0
f_expr = x
# initial functions
phi = sp.lambdify(x, phi_expr)
g1 = sp.lambdify(t, g1_expr)
g2 = sp.lambdify(t, g2_expr)
f = sp.lambdify((x, t), f_expr)
T = 0.2


def explicit_method(a, b, k, T, phi, g1, g2, f, h_x, h_t):
    hx_step_amount = int((b - a) / h_x)
    ht_step_amount = int(T / h_t)

    h_x = (b - a) / hx_step_amount
    h_t = T / ht_step_amount

    h_xs = np.linspace(a, b, hx_step_amount)
    h_ts = np.linspace(0, T, ht_step_amount)

    matrix = np.zeros(shape=(ht_step_amount, hx_step_amount))

    matrix[0, 1:-1] = np.array([phi(hs) for hs in h_xs[1:-1]])
    matrix[:, 0] = np.array([g1(ht) for ht in h_ts])
    #     matrix[:, -1] = np.array([g2(h_ts[i]) * h_t + matrix[i-1, -1] for i in range(len(h_ts))])

    coefs = [
        k * h_t / h_x ** 2,
        1 - 2 * k * h_t / h_x ** 2,
        k * h_t / h_x ** 2,
    ]

    for i in range(1, ht_step_amount):
        prev_layer = matrix[i - 1]
        matrix[i, 1: -1] = (
                sum(coefs[i] * prev_layer[i:len(prev_layer) - 2 + i] for i in range(3))  # sum yn-1 yn yn+1
                + np.array([h_t * f(hx, h_ts[i - 1]) for hx in h_xs[1:-1]])  # vector of tau * f(x, t)
        )
        matrix[i, -1] = matrix[i, -2] + h_x * g2(h_ts[i])

    #     plot_2d(h_xs, matrix, 5)
    #     plot_3d(h_xs, h_ts, matrix)

    return matrix


mantissa_len = 10


# standard deviation
def SD_t(m1, m2, layer1, layer2):
    if len(m1[0]) > len(m2[0]):
        m1, m2 = m2, m1
        layer1, layer2 = layer2, layer1
    return np.sqrt(sum((m1[layer1][i] - m2[layer2][2*i])**2 for i in range(len(m1[0]))) / len(m1[0]))

def max_deviation_t(m1, m2, layer1, layer2):
    if len(m1[0]) > len(m2[0]):
        m1, m2 = m2, m1
        layer1, layer2 = layer2, layer1
    return max(np.abs([m1[layer1][i] - m2[layer2][2*i] for i in range(len(m1[0]))]))

Ns = np.array([5 * 2**i for i in range(4, -1, -1)])

table_t = PrettyTable()

table_t.field_names = ['N : h', 'tau', 's(t=t_n1)', 's(t=t_n2)', 'max_abs(t=t_n1)', 'max_abs(t=t_n2)']

# select randomly t1 and t2
layer1 = random.randint(1, Ns[-1] - 1)
layer2 = random.randint(1, Ns[-1] - 1)

prev_res = None

print("t1 = {}, t2 = {}".format(T / Ns[-1] * layer1, T / Ns[-1] * layer2))

Xs = np.linspace(a, b, Ns[0] + 1)
tau = 0.5 * (Xs[1] - Xs[0])**2 / k

for i, N in enumerate(Ns):
    h_x = (b - a) / N
    res = explicit_method(a, b, T, k, phi, g1, g2, f, h_x, tau)
    if prev_res is None:
            table_t.add_row([Xs[1] - Xs[0], round(tau, mantissa_len), *list('-'*4)])
    else:
        # compute indexes of t1 and t2
        t11 = layer1 * Ns[i-1] // Ns[-1]
        t12 = layer1 * Ns[i] // Ns[-1]
        t21 = layer2 * Ns[i-1] // Ns[-1]
        t22 = layer2 * Ns[i] // Ns[-1]
        table_t.add_row(list(map(lambda x: round(x, mantissa_len),[
            h_x,
            tau,
            SD_t(prev_res, res, t11, t12),
            SD_t(prev_res, res, t21, t22),
            max_deviation_t(prev_res, res, t11, t12),
            max_deviation_t(prev_res, res, t21, t22),
        ])))
    prev_res = res


print(table_t)

# standard deviation
def SD_h(m1, m2, layer1, layer2):
    return np.sqrt(sum((m1[layer1][i] - m2[layer2][i])**2 for i in range(len(m1[0]))) / len(m1[0]))

def max_deviation_h(m1, m2, layer1, layer2):
    return max(np.abs([m1[layer1][i] - m2[layer2][i] for i in range(len(m1[0]))]))

Ts = np.array([100*2**i for i in range(5)])

table_h = PrettyTable()

table_h.field_names = ['N : h', 'tau', 's(t=t_n1)', 's(t=t_n2)', 'max_abs(t=t_n1)', 'max_abs(t=t_n2)']

max_tau = T / Ts[0]
h_x = np.sqrt(2 * k * max_tau)

# select randomly t1 and t2
layer1 = random.randint(1, Ts[0] - 1)
layer2 = random.randint(1, Ts[0] - 1)

prev_res = None

print("t1 = {}, t2 = {}".format(T / Ts[0] * layer1, T / Ts[0] * layer2))

for i, h_t in enumerate(Ts):
    tau = T / h_t
    res = explicit_method(a, b, T, k, phi, g1, g2, f, h_x, tau)
    if prev_res is None:
        table_h.add_row([h_x, round(tau, mantissa_len), *list('-' * 4)])
    else:
        # compute indexes of t1 and t2
        t11 = layer1 * Ts[i - 1] // Ts[0]
        t12 = layer1 * Ts[i] // Ts[0]
        t21 = layer2 * Ts[i - 1] // Ts[0]
        t22 = layer2 * Ts[i] // Ts[0]
        table_h.add_row(list(map(lambda x: round(x, mantissa_len), [
            h_x,
            tau,
            SD_h(prev_res, res, t11, t12),
            SD_h(prev_res, res, t21, t22),
            max_deviation_h(prev_res, res, t11, t12),
            max_deviation_h(prev_res, res, t21, t22),
        ])))
    prev_res = res

print(table_h)
