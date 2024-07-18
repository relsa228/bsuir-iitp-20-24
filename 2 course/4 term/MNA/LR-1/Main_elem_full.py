def gauss_main_full_func(matrix_a, b):
    for i in range(matrix_a.shape[0] - 1):

        # ищем по всей матрице
        max_elem = 0
        max_index = 0
        for j in range(i, matrix_a.shape[0]):
            if abs(matrix_a[j][i]) > abs(max_elem):
                max_elem = matrix_a[j][i]
                max_index = j

        # перестановка строк
        matrix_a[i], matrix_a[max_index] = matrix_a[max_index], matrix_a[i]
        b[i], b[max_index] = b[max_index], b[i]

        # треугольный вид
        matrix_a[i] /= max_elem
        b[i] /= max_elem
        for k in range(i + 1, matrix_a.shape[0]):
            temp = round(matrix_a[k][i], 4)
            matrix_a[k] -= matrix_a[i] * temp
            b[k] -= b[i] * temp

    for i in range(matrix_a.shape[0]):
        b[i] = int(b[i] * 10000) / 10000
        for j in range(matrix_a.shape[0]):
            matrix_a[i][j] = int(matrix_a[i][j] * 10000) / 10000

    for i in range(matrix_a.shape[0]):
        if matrix_a[i][i] == 0:
            print("На главной диагонали были обнаружены нули. Решение остановлено.")
            return None

    # ищем решения
    x = [b[b.shape[0] - 1] / (matrix_a[matrix_a.shape[0] - 1][matrix_a.shape[0] - 1])]
    for i in range(matrix_a.shape[0] - 2, -1, -1):
        temp = b[i]
        for j in range(len(x)):
            temp -= x[j] * matrix_a[i][matrix_a.shape[0] - 1 - j]
        x.append(temp)

    # возвращаем в нормальный вид
    x_norm = []
    for i in reversed(x):
        x_norm.append(i)
    return x_norm, matrix_a, b
