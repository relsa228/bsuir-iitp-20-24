def triangle_form(matrix_a, b, i):
    for j in range(i + 1, matrix_a.shape[0]):
        if matrix_a[i][i] != 0:
            temp = matrix_a[j][i] / matrix_a[i][i]
            b[j] -= temp * b[i]
            matrix_a[j][i] = 0
            for k in range(i + 1, matrix_a.shape[0]):
                matrix_a[j][k] -= int(temp * matrix_a[i][k] * 10000) / 10000
    return matrix_a, b


def gauss_func(matrix_a, b):
    for i in range(1, matrix_a.shape[0]):
        for j in range(i, matrix_a.shape[0]):
            if matrix_a[i - 1][i - 1] != 0:
                q = matrix_a[j][i - 1] / matrix_a[i - 1][i - 1]
                b[j] -= round(q * b[i - 1], 4)
                for k in range(matrix_a.shape[0]):
                    matrix_a[j][k] = round((matrix_a[j][k] - q * matrix_a[i - 1][k]), 4)
            else:
                print("Схема не может быть реализована, так как один из главных элементов равен нулю")
                return None

    x = [0 for i in range(matrix_a.shape[0])]
    for i in range(matrix_a.shape[0] - 1, -1, -1):
        x[i] = (b[i] - sum([matrix_a[i][j] * x[j] for j in range(i + 1, matrix_a.shape[0])])) / matrix_a[i][i]
    return x, matrix_a, b
