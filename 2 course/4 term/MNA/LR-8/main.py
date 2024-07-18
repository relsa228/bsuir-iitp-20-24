import time

import numpy as np
from simpsons_rule_module import simpson
from riemann_sum_module import rimemann
from dif_module import numeral_dif_first_pow
from dif_module import numeral_dif_second_pow
from trapezoidal_rule_module import trapezoidal


def f(x):
    return np.sqrt(x)


a = 0
b = 4
n = 100000

if __name__ == '__main__':
    print(f"Первая производная в точке х = 2: {'%.2f' % numeral_dif_first_pow(f, 2, 0.01)}")
    print(f"Вторая производная в точке х = 2: {'%.2f' % numeral_dif_second_pow(f, 2, 0.01)}")
    #t = time.perf_counter()
    #print(f"Метод трапеций: {'%.8f' % trapezoidal(f, a, b, n)}")
    #t_w = time.perf_counter() - t
    #print(f"Время выполнения: {'%.10f' % t_w}")
    #print(f"Метод Симпсона: {'%.8f' % simpson(f, a, b, n)}")
    #print(f"Метод средних прямоугольников: {'%.8f' % rimemann(f, a, b, n)}")
