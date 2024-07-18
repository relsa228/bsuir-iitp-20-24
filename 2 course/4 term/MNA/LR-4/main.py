import numpy as np
import sympy as sp
import time

from Iteration_module import simple_iterations
from Newton_module import newton_method

n = 2
eps = 0.0001


def output(x, iteration, time_result):
    if iteration == -1:
        print("Превышено допустимое количество итераций")
    else:
        print(f"x = " "%.4f" % x[0])
        print("y = " "%.4f" % x[1])
        print("----------------------")
        print(f"Кол-во итераций: {iteration}")
        print(f"Время работы: {round(time_result, 7)} секунд")


def f(x):
    f = np.zeros([n])
    f[0] = np.tan(x[0] * x[1] + 0.2) - x[0]
    f[1] = 0.8 * x[0] ** 2 + 2 * x[1] ** 2 - 1
    return f


def build_plots():
    (x, y) = sp.symbols('x y')
    f1 = sp.tan(x * y + 0.2) - x
    f2 = 0.8 * x ** 2 + 2 * y ** 2 - 1

    plots = sp.plot_implicit(sp.Eq(f1, 0), (x, 0, 1.5), (y, 0, 1.5), line_color="blue", show=False)
    plots.extend(sp.plot_implicit(sp.Eq(f2, 0), (x, 0, 1.5), (y, 0, 1.5), line_color="red", show=False))
    plots.show()


if __name__ == '__main__':
    build_plots()

    approximation = [0.64, 0.59]

    print("1. Метод простых итераций: ")
    work_time_start_simple = time.perf_counter()
    x_simple, iteration_simple = simple_iterations(approximation, eps)
    work_time_final_simple = time.perf_counter() - work_time_start_simple
    output(x_simple, iteration_simple, work_time_final_simple)

    print("\n2. Метод Ньютона: ")
    x0 = np.zeros([n])
    work_time_start_newton = time.perf_counter()
    x_newton, iteration_newton = newton_method(f, x0, eps, 0.59)
    work_time_final_newton = time.perf_counter() - work_time_start_newton
    output(x_newton, iteration_newton, work_time_final_newton)
