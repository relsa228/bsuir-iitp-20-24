import time
from matplotlib.pyplot import plot, grid, show, axis

from euler_method_module import euler_method
from runge_kutta_method_module import runge_kutta_method


def function(x, y):
    return 1.1*(1 - y**2)/(2*x**2 + y**2 + 1)

print("Метод Эйлера:")
t = time.perf_counter()
euler = euler_method(function, 10, 0.1, 0, 0)
t_w = time.perf_counter() - t
print(f"В точке x = {'%.6f' % euler[0]} имеет значение: {'%.6f' % euler[1][10]}")
print(f"Время выполнения: {'%.6f' % t_w}")

print("\nМетод Рунге-Кутта:")
t = time.perf_counter()
runge_kutta = runge_kutta_method(function, 10, 0.1, 0, 0)
t_w = time.perf_counter() - t
print(f"В точке x = {'%.6f' % runge_kutta[0]} имеет значение: {'%.6f' % runge_kutta[1][10]}")
print(f"Время выполнения: {'%.6f' % t_w}")

x_str = [0]
for i in range(10, 0, -1):
    x_str.append(x_str[10 - i] + 1/10)
plot(x_str, euler[1], "xb")
grid(True)
axis("equal")
show()