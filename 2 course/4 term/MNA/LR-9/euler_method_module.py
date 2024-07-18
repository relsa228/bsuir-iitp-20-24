def euler_method(function, n, h, x, y):
    res_y = [0]
    for i in range(n):
        y += h * function(x, y)
        x += h
        res_y.append(y)
    return x, res_y
