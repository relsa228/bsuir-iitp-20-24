def simpson(function, bound_a, bound_b, number_of_splits):
    h = (bound_b - bound_a) / number_of_splits
    k = 0.0
    x = bound_a + h

    higher_bound = int(number_of_splits / 2 + 1)
    for i in range(1, higher_bound):
        k += 4 * function(x)
        x += 2 * h

    x = bound_a + 2 * h

    higher_bound = int(number_of_splits / 2)
    for i in range(1, higher_bound):
        k += 2 * function(x)
        x += 2 * h
    return (h / 3) * (function(bound_a) + function(bound_b) + k)
