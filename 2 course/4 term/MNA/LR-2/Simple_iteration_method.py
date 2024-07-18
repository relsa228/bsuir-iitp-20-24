import numpy as np


def prime_criteria(on_proc_matrix) -> bool:
    eigenvalues = np.linalg.eigh(on_proc_matrix)[0]
    for i in eigenvalues:
        if i >= 1:
            return False
    return True


def not_full_criteria(matrix_a):
    first = []
    for i in range(matrix_a.shape[0]):
        s = 0
        for j in range(matrix_a.shape[1]):
            s += np.abs(matrix_a[i][j])
        first.append(s)
    if max(first) < 1:
        return True

    second = 0
    for i in range(matrix_a.shape[0]):
        for j in range(matrix_a.shape[1]):
            second += matrix_a[i][j] ** 2
    if second < 1:
        return True

    third = []
    for j in range(matrix_a.shape[1]):
        s = 0
        for i in range(matrix_a.shape[0]):
            s += np.abs(matrix_a[i][j])
        third.append(s)
    return max(third) < 1


def prime_iteration(a_matrix, b_data, eps):
    for i in range(a_matrix.shape[0]):
        b_data[i] /= a_matrix[i][i]
        a_matrix[i] /= a_matrix[i][i]

    if not prime_criteria(np.eye(5) - a_matrix):
        print("Нарушен достаточный критерий")

    b_inproc = np.eye(a_matrix.shape[0]) - a_matrix
    if not prime_criteria(b_inproc):
        print("Нарушен необходимый критерий")
        return None

    x = np.zeros(a_matrix.shape[0])
    converge = False
    interation = 0

    while not converge:
        x_new = b_inproc.dot(x.T) + b_data
        converge = np.sqrt((x_new - x).dot((x_new - x).T)) <= eps
        x = x_new
        interation += 1

    return x, interation
