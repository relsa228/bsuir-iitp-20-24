import sympy
from sympy.solvers import solve
import matplotlib.pyplot as plt

from numpy import linspace

LINSPACE_SIZE = 100
x = sympy.Symbol('x')

a = 0.2
b = 1.2
u_a = 4
u_b = 1
my_k = 1


def k_1(x, c):
    return x ** 3


def function_1(x):
    return 1.0 + x ** (1 / 3)


def build_final_equation(f, k, c, c1, c2):
    first_iter = (-(sympy.integrate(f(x), x) + c1) / k(x, c)).expand()
    second_iter = sympy.integrate(first_iter, x) + c2
    return second_iter


# this function returns final thermal conductivity function
def solve_thermal_conductivity_equation(f, k, c, a, b, u_a, u_b):
    c1, c2 = sympy.Symbol('c1'), sympy.Symbol('c2')
    true_eq = build_final_equation(f, k, c, c1, c2)
    c2_val = solve(true_eq.subs(x, b) - u_b, c2)[0]
    true_eq = true_eq.subs(c2, c2_val)

    c1_val = solve(true_eq.subs(x, a) - u_a, c1)[0]
    true_eq = true_eq.subs(c1, c1_val)
    print(true_eq)
    return true_eq


# TASK 1
def task_1():
    var_1 = solve_thermal_conductivity_equation(function_1, k_1, 1, a, b, u_a, u_b)
    var_2 = solve_thermal_conductivity_equation(function_1, lambda x, c: c * k_1(x, c), 2, a, b, u_a, u_b)
    var_3 = solve_thermal_conductivity_equation(function_1, lambda x, c: c * k_1(x, c), 0.1, a, b, u_a, u_b)

    D = linspace(a, b, LINSPACE_SIZE)
    func_y1, func_y2, func_y3, func_y4 = [], [], [], []

    for i in range(len(D)):
        func_y1.append(var_1.subs(x, D[i]))
        func_y2.append(var_2.subs(x, D[i]))
        func_y3.append(var_3.subs(x, D[i]))

    fig, _ = plt.subplots()
    plt.plot(D, func_y1, c='red', label='c = 1')
    plt.plot(D, func_y2, c='green', label='c = 2')
    plt.plot(D, func_y3, c='blue', label='c = 0.1')

    plt.legend()
    plt.show()

    var_4 = solve_thermal_conductivity_equation(function_1, lambda x, c: 1 / k_1(x, c), 1, a, b, u_a, u_b)

    for i in range(len(D)):
        func_y4.append(var_4.subs(x, D[i]))

    fig, _ = plt.subplots()
    plt.plot(D, func_y1, c='red', label='Набор 1')
    plt.plot(D, func_y4, c='green', label='Набор 4')

    plt.legend()
    plt.show()

    var_5 = solve_thermal_conductivity_equation(function_1, k_1, 1, a, b, -u_a, u_b)
    var_6 = solve_thermal_conductivity_equation(function_1, k_1, 1, a, b, u_a, -u_b)
    var_7 = solve_thermal_conductivity_equation(function_1, k_1, 1, a, b, -u_a, -u_b)

    func_y5, func_y6, func_y7 = [], [], []
    for i in range(len(D)):
        func_y5.append(var_5.subs(x, D[i]))
        func_y6.append(var_6.subs(x, D[i]))
        func_y7.append(var_7.subs(x, D[i]))

    fig, _ = plt.subplots()
    plt.plot(D, func_y5, c='red', label='Набор 5')
    plt.plot(D, func_y6, c='green', label='Набор 6')
    plt.plot(D, func_y7, c='blue', label='Набор 7')

    plt.legend()
    plt.show()

task_1()
