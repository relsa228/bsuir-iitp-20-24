from sympy import *
import numpy as np


def build_shturm_row(y):
    shturm_row = [y, y.diff()]
    count = len(shturm_row)
    for i in range(0, count, 1):
        shturm_row.append(-div(shturm_row[i], shturm_row[i + 1])[1])
        count += 1

    return shturm_row


def find_n(shturm_row, interval, x):
    temp = []
    sign_mut = 0
    for row_element in shturm_row:
        temp.append(row_element.subs(x, interval))
    for i in range(1, len(temp)):
        if np.sign(temp[i - 1]) != np.sign(temp[i]):
            sign_mut += 1

    return sign_mut


def shturm_function_answer(funct, x):
    shturm_row = build_shturm_row(funct)
    answer = find_n(shturm_row, -10, x) - find_n(shturm_row, 10, x)
    return answer
