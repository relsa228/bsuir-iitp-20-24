from __future__ import annotations

import sympy as sym


def make_system_of_equations(x_values: list[float],
                             residual: sym.Add,
                             symbol_to_subs=sym.Symbol('x')) -> list[sym.Add]:
    system = []
    for x in x_values:
        system.append(residual.subs(symbol_to_subs, x).simplify())
    return system


def answer_subs(y_n: sym.Add,
                coefficients: dict[sym.Symbol: float]) -> sym.Add | None:
    if type(coefficients) is not dict:
        print("Не может быть решено данным способом")
        return
    for coeff, val in coefficients.items():
        y_n = y_n.subs(coeff, val)
    return y_n


def make_points(left: float, right: float, number_of_points: int) -> list[float]:
    delta = (right - left) / (number_of_points + 1)
    return [left + delta * i for i in range(1, number_of_points + 1)]
