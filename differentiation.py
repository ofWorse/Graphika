import sympy
from sympy import symbols

"""Core functions"""


def differential_2p(equation: str, x_point, order=1, delta=0.02):
    delta = sympy.core.Rational(delta).limit_denominator(1000)
    x = symbols("x")
    equation = sympy.sympify(equation)
    if order == 1:
        return ((equation.subs(x, x_point + delta) - equation.subs(x, x_point)) / delta).evalf()
    else:
        order -= 1
        return ((differential_2p(equation, x_point + delta, order) -
                 differential_2p(equation, x_point, order)) / delta).evalf()


def differential_3p(equation: str, x_point, order=1, delta=0.02):
    delta = sympy.core.Rational(delta).limit_denominator(1000)
    x = symbols("x")
    equation = sympy.sympify(equation)
    if order == 1:
        return ((equation.subs(x, x_point + delta) - equation.subs(x, x_point - delta)) / (2 * delta)).evalf()
    else:
        order -= 1
        return ((differential_3p(equation, x_point + delta, order) -
                 (differential_3p(equation, x_point - delta, order))) / (2 * delta)).evalf()


def differential_5p(equation: str, x_point, order=1, delta=0.02):
    delta = sympy.core.Rational(delta).limit_denominator(1000)
    x = symbols("x")
    equation = sympy.sympify(equation)
    if order == 1:
        return ((equation.subs(x, x_point - 2 * delta) -
                 8 * equation.subs(x, x_point - delta) +
                 8 * equation.subs(x, x_point + delta) -
                 equation.subs(x, x_point + 2 * delta)) /
                (12 * delta)).evalf()
    else:
        order -= 1
        return ((differential_5p(equation, x_point - 2 * delta, order) -
                 8 * differential_5p(equation, x_point - delta, order) +
                 8 * differential_5p(equation, x_point + delta, order) -
                 differential_5p(equation, x_point + 2 * delta, order)) /
                (12 * delta)).evalf()


"""Wrap functions with formatted output"""


def differential_2_points(equation: str, x_point, order=1, delta=0.02, precision=4):
    return differential_2p(equation, x_point, order, delta).evalf(n=precision, chop=1e-5)


def differential_3_points(equation: str, x_point, order=1, delta=0.02, precision=4):
    return differential_3p(equation, x_point, order, delta).evalf(n=precision, chop=1e-5)


def differential_5_points(equation: str, x_point, order=1, delta=0.02, precision=4):
    return differential_5p(equation, x_point, order, delta).evalf(n=precision, chop=1e-5)


"""Polt-ready functions"""


def differential_2p_for_plot(equation: str, a, b, order=1, delta=0.05, precision=4):
    equation = sympy.sympify(equation)
    delta = sympy.core.Rational(delta).limit_denominator(1000)
    y_for_plot = list()
    x_for_sub = a + delta
    while x_for_sub + delta < b:
        y_for_plot.append(float(differential_2_points(equation, x_for_sub, order, delta, precision).evalf(n=precision)))
        x_for_sub += delta
    return y_for_plot


def differential_3p_for_plot(equation: str, a, b, order=1, delta=0.05, precision=4):
    equation = sympy.sympify(equation)
    delta = sympy.core.Rational(delta).limit_denominator(1000)
    y_for_plot = list()
    x_for_sub = a + delta
    while x_for_sub + delta < b:
        y_for_plot.append(float(differential_3_points(equation, x_for_sub, order, delta, precision).evalf(n=precision)))
        x_for_sub += delta
    return y_for_plot


def differential_5p_for_plot(equation: str, a, b, order=1, delta=0.05, precision=4):
    equation = sympy.sympify(equation)
    delta = sympy.core.Rational(delta).limit_denominator(1000)
    y_for_plot = list()
    x_for_sub = a + delta
    while x_for_sub + delta < b:
        y_for_plot.append(float(differential_5_points(equation, x_for_sub, order, delta, precision).evalf(n=precision)))
        x_for_sub += delta
    return y_for_plot
