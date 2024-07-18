import numpy as np


def QR_Decomposition(undec_matrix_a):
    n, m = undec_matrix_a.shape  # get the shape of A

    Q = np.empty((n, n))  # initialize matrix Q
    u = np.empty((n, n))  # initialize matrix u

    u[:, 0] = undec_matrix_a[:, 0]
    Q[:, 0] = u[:, 0] / np.linalg.norm(u[:, 0])

    for i in range(1, n):

        u[:, i] = undec_matrix_a[:, i]
        for j in range(i):
            u[:, i] -= (undec_matrix_a[:, i] @ Q[:, j]) * Q[:, j]  # get each u vector

        Q[:, i] = u[:, i] / np.linalg.norm(u[:, i])  # compute each e vetor

    R = np.zeros((n, m))
    for i in range(n):
        for j in range(i, m):
            R[i, j] = undec_matrix_a[:, j] @ Q[:, i]

    return Q, R


def checkDiagonal(arr):
    for i in range(len(arr)):
        for j in range(len(arr[i])):
            if i == j:
                continue
            else:
                if abs(arr[i][j]) > 0.001:
                    return False
    return True


def QR_Factorization(arr):
    temp = arr
    i = 0
    while True:
        Q, R = QR_Decomposition(temp)
        temp = np.dot(R, Q)
        if checkDiagonal(temp):
            return temp
        else:
            i += 1


def qr_method(matrix_a, eps):
    work_arr = QR_Factorization(matrix_a)
    result = []
    for i in range(len(work_arr)):
        for j in range(len(work_arr[i])):
            if i == j:
                temp = work_arr[i][j]
                if abs(temp) < eps:
                    temp = 0
                result.append(temp)

    return result
