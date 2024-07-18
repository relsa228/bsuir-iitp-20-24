from __future__ import annotations

import sympy as sym
from working_functions import make_points
from working_functions import answer_subs


def discrete_least_squares_method(residual: sym.Add,
                                  y_n: sym.Add,
                                  number_of_points: int,
                                  left: float, right: float) -> sym.Add | None:
    S = 0
    x = sym.Symbol('x')
    for point in make_points(left, right, number_of_points):
        S += residual.subs(x, point) ** 2
    system = []
    for i in range(1, len(residual.free_symbols)):
        system.append(sym.diff(S, sym.Symbol(f"a{i}")))
    return answer_subs(y_n, sym.solve(system))
