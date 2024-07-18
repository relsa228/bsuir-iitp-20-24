import numpy as np


class LagrangePoly:

    def __init__(self, x_arg, y_arg):
        self.n = len(x_arg)
        self.X = np.array(x_arg)
        self.Y = np.array(y_arg)

    def basis(self, x_point, j):  # базис lj(x) в методе
        l = [(x_point - self.X[m]) / (self.X[j] - self.X[m]) for m in range(self.n) if m != j]
        return np.prod(l, axis=0) * self.Y[j]

    def interpolate(self, x_point):  # сама интерполяция, сложение
        l = [self.basis(x_point, j) for j in range(self.n)]
        return np.sum(l, axis=0)

    def print_poly(self):
        result_str = ""
        for i in range(1, len(self.X)):
            result_str += f"[(x - {'%.1f' % self.X[i]})/({self.X[0]} - {'%.1f' % self.X[i]})] * "
            if i%2 == 0:
                result_str += "\n"
        result_str = result_str[:-3]
        print(result_str)
