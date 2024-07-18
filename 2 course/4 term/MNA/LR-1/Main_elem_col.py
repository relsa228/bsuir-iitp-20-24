from Gauss import triangle_form


def gauss_main_col_func(matrix_a, b):
    for i in range(0, matrix_a.shape[0]):

        # поиск главного по столбцу элемента
        max_elem = matrix_a[i][i]
        max_index = i
        for j in range(i + 1, matrix_a.shape[0]):
            if abs(max_elem) < abs(matrix_a[j][i]):
                max_elem = matrix_a[j][i]
                max_index = j

        if i != max_index:
            b[i], b[max_index] = b[max_index], b[i]
            for j in range(i, matrix_a.shape[0]):
                matrix_a[i][j], matrix_a[max_index][j] = matrix_a[max_index][j], matrix_a[i][j]

        # треугольный вид
        trng_res = triangle_form(matrix_a, b, i)
        matrix_a = trng_res[0]
        b = trng_res[1]

    for i in range(matrix_a.shape[0]):
        if matrix_a[i][i] == 0:
            print("На главной диагонали были обнаружены нули. Решение остановлено.")
            return None

    # ищем решения
    x = [0 for _ in range(matrix_a.shape[0])]
    for i in range(matrix_a.shape[0] - 1, -1, -1):
        for j in range(i, matrix_a.shape[0]):
            if j == matrix_a.shape[0] - 1:
                break
            else:
                b[i] -= matrix_a[i][j + 1] * x[j + 1]
        if matrix_a[i][i] != 0:
            x[i] = b[i] / matrix_a[i][i]

    return x, matrix_a, b
