from sympy import *
import matplotlib.pyplot as plt


def galerkin(ode, x, x0, x1, y0, q):
    basis = [x ** i * (1 - x ** 2) for i in range(q + 1)]

    # Coefficients for the basis monomials
    xi = [Symbol("xi_%i" % i) for i in range(q + 1)]

    # Solution function ansatz
    y = y0 + sum(xi[i] * basis[i] for i in range(1, q + 1))

    # Form system of linear equations
    equations = [integrate(ode(y) * basis[k], (x, x0, x1)) for k in range(1, q + 1)]
    coeffs = solve(equations, xi[1:])
    return y.subs(coeffs)


def get_galerkin_solve(ode, x, x0, x1, y0, q):
    pprint(galerkin(ode, x, x0, x1, y0, q))


def get_galerkin_plots(ode, x, x0, x1, y0, q, step):
    x_coord = []
    y_coord = []
    galerkin_solve_0 = galerkin(ode, x, x0, x1, y0, q)
    galerkin_solve_1 = galerkin(ode, x, x0, x1, y0, q + 1)
    galerkin_solve_2 = galerkin(ode, x, x0, x1, y0, q + 2)
    galerkin_solve_3 = galerkin(ode, x, x0, x1, y0, q + 3)

    x_insert = -1
    while x_insert <= 1:
        x_coord.append(x_insert)
        x_insert += step

    for x_val in x_coord:
        y_coord.append(galerkin_solve_0.subs(x, x_val))
    plt.plot(x_coord, y_coord, color="red")

    y_coord = []
    for x_val in x_coord:
        y_coord.append(galerkin_solve_1.subs(x, x_val))
    plt.plot(x_coord, y_coord, color="black")

    y_coord = []
    for x_val in x_coord:
        y_coord.append(galerkin_solve_2.subs(x, x_val))
    plt.plot(x_coord, y_coord, color="yellow")

    y_coord = []
    for x_val in x_coord:
        y_coord.append(galerkin_solve_3.subs(x, x_val))
    plt.plot(x_coord, y_coord, color="green")

    plt.show()