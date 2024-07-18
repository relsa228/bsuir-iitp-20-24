def least_squares(x, y):
    xy = []
    for i, val in enumerate(x):
        xy.append(x[i] * y[i])

    x_sqrt = [i ** 2 for i in x]
    n = len(x)

    w = (n * sum(xy) - sum(x) * sum(y)) / (n * sum(x_sqrt) - sum(x) ** 2)
    b = (sum(y) - w * sum(x)) / n

    return w, b
