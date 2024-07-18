import sympy as sym
import numpy as np

from collocation_module import collocation_method
from discret_least_squares_method import discrete_least_squares_method
from integral_least_squares_module import integral_least_squares_method
from galerkin_method_module import get_galerkin_solve, get_galerkin_plots
from working_functions import make_points


def make_boundary_value_problem(k_val: float) -> sym.Add:
    k, x, y = sym.symbols('k x y')
    a = sym.sin(k_val)
    b = sym.cos(k_val)
    return a * sym.Derivative(y, x, x) + (1 + b * x ** 2) * y + 1


def make_basis_system(num_of_functions: int) -> list[sym.Add]:
    x = sym.Symbol('x')
    fi_0 = 0
    basis = [fi_0]
    for i in range(1, num_of_functions):
        fi_i = x ** i * (1 - x ** 2)
        basis.append(fi_i)
    return basis


def make_residual(boundary_value_problem: sym.Add,
                  y_n: sym.Add,
                  symbol_to_subs=sym.Symbol('y')) -> sym.Add:
    return boundary_value_problem.subs(symbol_to_subs, y_n).doit().evalf().simplify()


def make_y_n(basis_system: list) -> sym.Add:
    y_n = 0
    for i, fi_i in enumerate(basis_system):
        a_i = sym.Symbol(f"a{i}")
        y_n += a_i * fi_i
    return y_n


var = 6
x = sym.Symbol('x')
y0 = 0
x0 = -1
x1 = 1
q = 5
ode = lambda y: np.sin(6) * y.diff(x).diff(x) + (1 + np.cos(6) * x ** 2) * y + 1
bvp = make_boundary_value_problem(var)
basis = make_basis_system(q)
y_n = make_y_n(basis)
psi = make_residual(bvp, y_n)
print("Метод коллокаций:")
sym.pprint(collocation_method(psi, y_n, make_points(x0, x1, q)))
print("===========================================================")
print("Интегральный метод наименьших квадратов:")
sym.pprint(integral_least_squares_method(psi, y_n, x0, x1))
print("===========================================================")
print("Дискретный метод наименьших квадратов:")
sym.pprint(discrete_least_squares_method(psi, y_n, 20, x0, x1))
print("===========================================================")
print("Метод Галеркина:")
get_galerkin_solve(ode, x, x0, x1, y0, q)

get_galerkin_plots(ode, x, x0, x1, y0, q, 0.001)


