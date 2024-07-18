import numpy as np
import time
from jacobi_algorithm_module import jacobi_method
from power_iteration import power_iteration_method
from qr_method import qr_method


def matrix():
    C = np.array([[0.2, 0, 0.2, 0, 0],
                  [0, 0.2, 0, 0.2, 0],
                  [0.2, 0, 0.2, 0, 0.2],
                  [0, 0.2, 0, 0.2, 0],
                  [0, 0, 0.2, 0, 0.2]])

    D = np.array([[2.33, 0.81, 0.67, 0.92, -0.53],
                  [0.81, 2.33, 0.81, 0.67, 0.92],
                  [0.67, 0.81, 2.33, 0.81, 0.92],
                  [0.92, 0.67, 0.81, 2.33, -0.53],
                  [-0.53, 0.92, 0.92, -0.53, 2.33]])

    matrix_A = 4 * C + D
    return matrix_A


if __name__ == '__main__':
    eps = 0.0001

    print("Результаты, полученные с помощью np.linalg.eig(): ")
    print("Собственные значения:")
    for i in range(1, matrix().shape[0] + 1):
        print(f"{i}. " "%.4f" % np.linalg.eig(matrix())[0][i - 1])
    print(f"\nСобственные векторы: \n{np.linalg.eig(matrix())[1]}")

    print("====================================================================")

    print("\n1. Метод Якоби:")
    t = time.perf_counter()
    result_jacobi = jacobi_method(matrix(), eps)
    t_w = time.perf_counter() - t
    print("Собственные значения:")
    for i in range(1, matrix().shape[0] + 1):
        print(f"{i}. " "%.4f" % result_jacobi[0][i - 1])
    print(f"\nСобственные векторы: \n{result_jacobi[1]}")
    print(f"\nВремя выполнения: {t_w}")

    print("\n\n2. Степенной метод:")
    t = time.perf_counter()
    result_pow = power_iteration_method(matrix(), eps)
    t_w = time.perf_counter() - t
    print(f"Наибольшее собственное значение: \n" "%.4f" % result_pow[0])
    print(f"\nНаибольший собственный вектор: \n {result_pow[1]}")
    print(f"\nВремя выполнения: {t_w}")

    print("\n\n3. QR метод:")
    t = time.perf_counter()
    result_qr = qr_method(matrix(), eps)
    t_w = time.perf_counter() - t
    print("Собственные значения:")
    for i in range(1, matrix().shape[0] + 1):
        print(f"{i}. " "%.4f" % result_qr[i - 1])
    print(f"\nВремя выполнения: {t_w}")
