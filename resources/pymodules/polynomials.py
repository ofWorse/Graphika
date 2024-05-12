r"""
author: Konak Vladimir Evgen'evich
last edited: 05.12.2024
organisation: Dnevnie mechaniki
"""

import sympy
from sympy import symbols


def set_data_type(x, y):
    r"""
    Cast interpolation points coordinates from string to working type.

    Original values are casts to sympy.core.Rational, providing arbitrary large precision during calculations.
    Boolean flag is returned, signalling that the initial data were float.

    :param x: list of string numbers e.g: ['0', '1', '2.12', ...]
    :param y: list of string numbers e.g: ['10', '14.2321', '28.0', ...]
    :return: tuple(x_new_data_list:sympy.core.Rational[], y_new_data_list:sympy.core.Rational[], contains_float:boolean)
    """

    x_new_data_list = list()
    y_new_data_list = list()
    contains_float = False
    for i in range(len(x)):
        if "." in x[i] or "." in y[i]:
            contains_float = True
        x_new_data_list.append(sympy.core.Rational(x[i]))
        y_new_data_list.append(sympy.core.Rational(y[i]))
    return x_new_data_list, y_new_data_list, contains_float


def newton_polynomial(x_values, y_values, precision=3):
    r"""
    Create Newton's divided differences interpolation polynomial.

    Most usable for small data set of interpolation points (number of points < 7).
    With increasing number of interpolations points oscillations may acquire.

    Coefficients are calculated with arbitrary large rationals, then evaluated as floats and
    then presented as simplified rationals, e.g:

    Rational(1.2341234412) = 2778998934958757/2251799813685248 -> 1.23 (precision = 3) -> 311/252

    311/252 is final coefficient value.

    :param x_values: list of string numbers e.g: ['0', '1', '2.12', ...]
    :param y_values: list of string numbers e.g: ['10', '14.2321', '28.0', ...]
    :param precision: integer number that represents number of meaningful signs in the number.
    :return: string containing model of interpolation polynomial e.g: "16*x^3/285 - 43*x^2/131 + 235*x/487"
    """

    x_values, y_values, contains_float = set_data_type(x_values, y_values)
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
    r"""
    Create Lagrange interpolating polynomial.

    Most usable for small data set of interpolation points (number of points < 7).
    With increasing number of interpolations points oscillations may acquire.

    Coefficients are calculated with arbitrary large rationals, then evaluated as floats and
    then presented as simplified rationals, e.g:

    Rational(1.2341234412) = 2778998934958757/2251799813685248 -> 1.23 (precision = 3) -> 311/252

    311/252 is final coefficient value.

    :param x_values: list of string numbers e.g: ['0', '1', '2.12', ...]
    :param y_values: list of string numbers e.g: ['10', '14.2321', '28.0', ...]
    :param precision: integer number that represents number of meaningful signs in the number.
    :return: string containing model of interpolation polynomial e.g: "16*x^3/285 - 43*x^2/131 + 235*x/487"
    """

    x_values, y_values, contains_float = set_data_type(x_values, y_values)
    polynomial = sympy.sympify(0)
    n = len(x_values)
    x = symbols("x")
    for i in range(n):
        lagrange = 1
        for j in range(n):
            if j == i:
                continue
            lagrange *= (x - x_values[j]) / (x_values[i] - x_values[j])
        polynomial += y_values[i] * sympy.cancel(lagrange)
    if contains_float:
        return str(sympy.nsimplify(polynomial.evalf(n=precision).cancel())).replace("**", "^")
    return str(sympy.cancel(polynomial, x)).replace("**", "^")


def beirut_functions(x_values, y_values, precision=3):
    r"""
    Create interpolation function using Beirut's algorithm for building rational functions.

    Works better on data sets where other polynomial models creates major oscillations or
    with number of interpolation points > 7.

    Increasing number of interpolation points drastically increases time it takes to compute interpolation function.

    Coefficients are calculated with arbitrary large rationals, then evaluated as floats and
    then presented as simplified rationals, e.g:

    Rational(1.2341234412) = 2778998934958757/2251799813685248 -> 1.23 (precision = 3) -> 311/252

    311/252 is final coefficient value.

    :param x_values: list of string numbers e.g: ['0', '1', '2.12', ...]
    :param y_values: list of string numbers e.g: ['10', '14.2321', '28.0', ...]
    :param precision: integer number that represents number of meaningful signs in the number.
    :return: string containing model of interpolation rational function e.g: "(-4*x^2/37 + 8*x/25)/(x^2 - 2*x + 2)"
    """

    x_values, y_values, contains_float = set_data_type(x_values, y_values)
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
