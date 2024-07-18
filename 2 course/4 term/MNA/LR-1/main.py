import numpy as np

from Gauss import gauss_func
from Main_elem_col import gauss_main_col_func
from Main_elem_full import gauss_main_full_func


def val():
    d = np.array([[2.33, 0.81, 0.67, 19, -0.53],
                  [-0.53, 2.33, 0.81, 0.67, 0.92],
                  [0.92, -0.53, 2.33, 0.81, 0.67],
                  [0.67, 10, -0.53, 2.33, 0.81],
                  [0.81, 0.67, 0.92, 28, 2.33]])

    c = np.array([[0.2, 0, 0.2, 0, 0],
                  [0, 0.2, 0, 0.2, 0],
                  [0.2, 0, 0.2, 0, 0.2],
                  [0, 0.2, 0, 0.2, 0],
                  [0, 0, 0.2, 0, 0.2]])

    b = np.array([4.2 for _ in range(5)])
    a = 4 * c + d

    a = np.array([[7, -2, -1],
                  [6, -4, -5],
                  [1, 2, 4]])

    b = np.array([2, 3, 5])

    return a, b


def output(result_full):
    if result_full is not None:
        np.set_printoptions(formatter={'float': '{: 0.4f}'.format})
        result_x = result_full[0]
        result_matrix_a = np.c_[result_full[1], result_full[2].T]
        print(f"Полученная матрица:\n {result_matrix_a}")
        print("\nРезультат:")
        for i in range(val()[0].shape[0]):
            print(f"x_{i + 1} = " "%.4f" % result_x[i])
        print("==================================================================")


def compatibility_check(a, b, n):
    full_matrix = np.insert(a, a.shape[0], b, 1)
    rank_a = np.linalg.matrix_rank(a)
    rank_full = np.linalg.matrix_rank(full_matrix)
    if rank_a == 0:
        print("Матрица вырождена")
        return 1
    if rank_a != rank_full:
        print("Матрица несовместна")
    if rank_full == rank_a and rank_full == n:
        print("Система совместна и имеет единственное решение")
        return 0
    if rank_full == rank_a and rank_full < n:
        print(f"Система совместна и имеет бесконечно много решений в векторном пространстве R_{full_matrix.shape[0]}")
        return 1


if __name__ == '__main__':
    if compatibility_check(val()[0], val()[1], 3) == 0:
        print("\n==================================================================")
        numpy_res = np.linalg.solve(val()[0], val()[1])
        print("Результат, полученный с помщью numpy:\n---------------------------------")
        for i in range(numpy_res.shape[0]):
            print(f"x_{i + 1} = " "%.4f" % numpy_res[i])
        print("==================================================================")

        print("\n\n==================================================================")
        print("Метод Гаусса:\n-------------")
        result = gauss_func(val()[0], val()[1])
        if result is not None:
            output(result)

        print("\n\n==================================================================")
        print("Метод Гаусса с выбором главного элемента по столбцу:\n-----------------------------"
              "-----------------------")
        result = gauss_main_col_func(val()[0], val()[1])
        output(result)

        print("\n\n==================================================================")
        print("Метод Гаусса с выбором главного элемента по всей матрице:\n------------------------"
              "---------------------------------")
        result = gauss_main_full_func(val()[0], val()[1])
        output(result)
