import numpy as np


def not_full_zeidel_criteria(a_matrix):
    first = []
    for i in range(a_matrix.shape[0]):
        sum = 0
        for j in range(a_matrix.shape[1]):
            sum += np.abs(a_matrix[i][j])
        first.append(sum)
    if max(first) < 1:
        return True

    second = []
    for j in range(a_matrix.shape[1]):
        sum = 0
        for i in range(a_matrix.shape[0]):
            sum += np.abs(a_matrix[i][j])
        second.append(sum)
    return max(second) < 1


def seidel_criteria(matrix) -> bool:
    on_proc_matrix = matrix.copy()

    f = np.zeros(on_proc_matrix.shape)
    for i in range(0, on_proc_matrix.shape[0]):
        for j in range(i, on_proc_matrix.shape[0]):
            f[i][j] = on_proc_matrix[i][j]

    h = on_proc_matrix - f
    e = np.eye(on_proc_matrix.shape[0])
    lambd = np.linalg.eigh(on_proc_matrix)[0]

    for i in lambd:
        res = f + i * h - i * e
        if int(np.linalg.det(res)) == 0 and abs(i) >= 1:
            return False

    return True


def seidel_method(matrix_a, matrix_b, eps):
    n = len(matrix_a)
    x = np.zeros(n)
    iterations = 0
    for i in range(matrix_a.shape[0]):
        matrix_b[i] /= matrix_a[i][i]
        matrix_a[i] /= matrix_a[i][i]

    if not not_full_zeidel_criteria(np.eye(matrix_a.shape[0]) - matrix_a):
        print("Нарушен достаточный критерий")

    if not seidel_criteria(np.eye(matrix_a.shape[0]) - matrix_a):
        print("Нарушен необходимый критерий")
        return None

    converge = False
    while not converge:
        x_new = np.copy(x)
        for i in range(n):
            s1 = sum(matrix_a[i][j] * x_new[j] for j in range(i))
            s2 = sum(matrix_a[i][j] * x[j] for j in range(i + 1, n))
            x_new[i] = (matrix_b[i] - s1 - s2) / matrix_a[i][i]

        converge = np.sqrt(sum((x_new[i] - x[i]) ** 2 for i in range(n))) <= eps
        x = x_new
        iterations += 1

    return x, iterations
