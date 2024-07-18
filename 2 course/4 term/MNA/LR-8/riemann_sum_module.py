def rimemann(f, a, b, n):
    w = (b - a) / n
    result = 0.5 * f(a) + sum([f(a + i * w) for i in range(1, n)]) + 0.5 * f(b)
    result *= w
    return result
