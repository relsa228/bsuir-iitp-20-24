from __future__ import annotations

import sympy as sym
from working_functions import answer_subs


def integral_least_squares_method(residual: sym.Add,
                                  y_n: sym.Add,
                                  left: float, right: float) -> sym.Add | None:
    system = []
    x = sym.Symbol('x')
    for i in range(1, len(residual.free_symbols)):
        part_diff = sym.diff(residual, sym.Symbol(f"a{i}"))
        system.append(2 * sym.integrate(residual * part_diff, (x, left, right)))
    return answer_subs(y_n, sym.solve(system))
