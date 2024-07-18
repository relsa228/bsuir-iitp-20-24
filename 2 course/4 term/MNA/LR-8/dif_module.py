def numeral_dif_first_pow(f, point, h):
    result = f(point + h) - f(point - h)
    result /= 2 * h
    return result


def numeral_dif_second_pow(f, point, h):
    result = numeral_dif_first_pow(f, point + h, h) - numeral_dif_first_pow(f, point - h, h)
    result /= 2 * h
    return result
