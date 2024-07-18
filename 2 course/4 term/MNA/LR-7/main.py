import numpy as np
import math
import matplotlib.pyplot as plt

from spline_module import Spline
from lagrange_module import LagrangePoly


if __name__ == '__main__':
    # input
    #  x = [-1.0, 0.0, 1.0, 2.0, 3.0]
    #  x = [-0.5, 0.0, 0.5, 1.0, 1.5]
    x = [1, 1.2, 1.5, 1.6, 1.8, 2]
    y = [1, 0.81, 0.63, 0.61, 0.52, 0.5]

    lg = LagrangePoly(x, y)
    spline = Spline(x, y)
    rx = np.arange(0, 2, 0.01)
    ry = [spline.calc(i) for i in rx]

    plt.plot(x, y, "xb", color='b')
    #plt.plot(rx, ry, "-r", color='r')
    plt.plot(x, np.divide(1, x), color='g')
    plt.plot(x, lg.interpolate(x), color='m')
    plt.grid(True)
    plt.axis("equal")
    plt.show()
