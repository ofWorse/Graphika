import sympy
from sympy import symbols


def integral_linear(equation: str, a, b, delta=0.05, precision=4):
    equation = sympy.sympify(equation)
    a = a
    b = b
    delta = sympy.Rational(delta).limit_denominator(1000)
    x = symbols("x")
    integral = 0
    x_point = a + delta / 2
    while x_point <= b:
        integral += equation.subs(x, x_point) * delta
        x_point += delta
    return round(integral, precision)


def integral_trapezoid(equation: str, a, b, delta=0.05, precision=4):
    equation = sympy.sympify(equation)
    a = a
    b = b
    delta = sympy.Rational(delta).limit_denominator(1000)
    x = symbols("x")
    integral = 0
    x_point = a
    while x_point + delta <= b:
        integral += (equation.subs(x, x_point) + equation.subs(x, x_point + delta)) / 2 * delta
        x_point += delta
    return round(integral, precision)


def integral_parabolic(equation: str, a, b, delta=0.05, precision=4):
    equation = sympy.sympify(equation)
    a = a
    b = b
    delta = sympy.Rational(delta).limit_denominator(1000)
    x = symbols("x")
    integral = 0
    x_point = a
    while x_point + delta <= b:
        integral += ((equation.subs(x, x_point)) +
                     4 * (equation.subs(x, x_point + delta / 2)) +
                     equation.subs(x, x_point + delta)) * (delta / 6)
        x_point += delta
    return round(integral, precision)
