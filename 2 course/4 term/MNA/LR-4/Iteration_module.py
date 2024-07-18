import numpy as np


def get_x(x, y):
    return np.tan(x * y + 0.2)


def get_y(x):
    return np.sqrt((1 - 0.8 * (x ** 2)) / 2)


def simple_iterations(first_approximation, eps):
    maxIter = 1000
    result_array = np.asarray(first_approximation)
    temp = 1
    iterations = 0
    while temp > eps:
        new_x = result_array.copy()
        new_x[0], new_x[1] = get_x(result_array[0], result_array[1]), get_y(result_array[0])
        temp = np.max(np.abs(result_array - new_x))
        result_array = new_x.copy()
        iterations += 1
        if iterations == maxIter:
            return -1, -1
    return result_array, iterations
