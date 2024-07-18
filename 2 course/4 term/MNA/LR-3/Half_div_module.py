def exec_half_div(f, eps):
    a, b = -10, 10
    f1 = f(a)
    f2 = f(b)
    if f1 * f2 >= 0:
        return None
    else:
        x = (a+b)/2
        f3 = f(x)
        iterations = 0
        while abs(f3) > eps:
            x = (a+b)/2
            f3 = f(x)
            if f1 * f3 < 0:
                b = x
            else:
                a = x
            iterations += 1

        return iterations, x
