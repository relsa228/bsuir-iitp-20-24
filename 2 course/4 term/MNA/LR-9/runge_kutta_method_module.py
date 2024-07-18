def runge_kutta_method(function, n, h, x, y):
    yn = 0
    res_yn = [0]
    for i in range(n):
        k1 = h * (function(x, y))
        k2 = h * (function((x + h / 2), (y + k1 / 2)))
        k3 = h * (function((x + h / 2), (y + k2 / 2)))
        k4 = h * (function((x + h), (y + k3)))
        k = (k1 + 2 * k2 + 2 * k3 + k4) / 6
        yn = y + k
        y = yn
        x = x + h
        res_yn.append(yn)

    return x, res_yn
