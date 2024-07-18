from __future__ import annotations

import sympy as sym
from working_functions import make_system_of_equations
from working_functions import answer_subs


def collocation_method(residual: sym.Add,
                       y_n: sym.Add,
                       collocation_points: list[float]) -> sym.Add | None:
    system = make_system_of_equations(collocation_points, residual)
    return answer_subs(y_n, sym.solve(system))
