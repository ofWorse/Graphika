import sympy
from sympy import symbols


def cast_to_number(x, y):
    x_act = list()
    y_act = list()
    contains_float = False
    for i in range(len(x)):
        if "." in x[i] or "." in y[i]:
            contains_float = True
        x_act.append(sympy.core.Rational(x[i]))
        y_act.append(sympy.core.Rational(y[i]))
    return x_act, y_act, contains_float


def newton_polynomial(x_values, y_values, precision=3):
    x_values, y_values, contains_float = cast_to_number(x_values, y_values)
    n = len(x_values)
    polynomial = y_values[0]
    x = symbols("x")
    for polynomial_term in range(1, n):
        multiplier = 1
        for j in range(polynomial_term):
            multiplier *= (x - x_values[j])
        polynomial += divided_difference(polynomial_term, x_values[:polynomial_term + 1], y_values[:polynomial_term + 1]) * multiplier
    if contains_float:
        return str(sympy.nsimplify(polynomial.evalf(n=precision).cancel())).replace("**", "^")
    return str(sympy.cancel(polynomial, x)).replace("**", "^")


def divided_difference(n, x_values, y_values):
    if n == 1:
        return sympy.Rational((y_values[n] - y_values[n - 1]), (x_values[n] - x_values[0]))
    else:
        return sympy.Rational((divided_difference(n - 1, x_values[1:], y_values[1:]) -
                               divided_difference(n - 1, x_values[:n], y_values[:n])), (x_values[n] - x_values[0]))


def lagrange_polynomial(x_values, y_values, precision=3):
    x_values, y_values, contains_float = cast_to_number(x_values, y_values)
    polynomial = sympy.sympify(0)
    n = len(x_values)
    x = symbols("x")
    for i in range(n):
        lagrange = 1
        for j in range(n):
            if j == i:
                continue
            lagrange *= (x - x_values[j]) / (x_values[i] - x_values[j])
        polynomial += y_values[i] * lagrange
    if contains_float:
        return str(sympy.nsimplify(polynomial.evalf(n=precision).cancel())).replace("**", "^")
    return str(sympy.cancel(polynomial, x)).replace("**", "^")


def berruta_functions(x_values, y_values, precision=3):
    x_values, y_values, contains_float = cast_to_number(x_values, y_values)
    numerator = 0
    denominator = 0
    n = len(x_values)
    x = symbols("x")
    for k in range(n):
        product = 1
        for i in range(n):
            if i == k:
                continue
            product *= (x - x_values[i])
        numerator += (-1) ** k * y_values[k] * product
        denominator += ((-1) ** k * product)
    polynomial = sympy.sympify(numerator/denominator)
    if contains_float:
        return str(sympy.nsimplify(polynomial.evalf(n=precision).cancel())).replace("**", "^")
    return str(polynomial.cancel()).replace("**", "^")
