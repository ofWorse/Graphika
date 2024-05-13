r"""
author: Konak Vladimir Evgen'evich

last edited: 05.13.2024

organisation: Dnevnie mechaniki
"""


def integral_linear(x_values, y_values, a=None, b=None, precision=4):
    r"""
    Calculate an area under the curve using rectangle right rule.

    Calculate integration value of the given function using geometric meaning of define integral.
    Small segment of area is presented as rectangle with `base = dx` and `height = y(x)`.

    Function is present as two lists of values: `x` and `y`. Each `x` value has according `y(x)` value.

    :param x_values: list of equally spaced `x` float values of the given function.
    :param y_values: list of float values of the given function.
    :param a: optional, if present, used as starting point for calculation.
    :param b: optional, if present, used as end point for calculation.
    :param precision: integer, represents number of signs after decimal point.
    :return: float value of area under the curve of the given function.
    """

    if a and b and (a < b):
        for i in x_values:
            if i > b:
                index = x_values.index(i)
                x_values = x_values[:index]
                y_values = y_values[:index]
                break
        for i in x_values:
            if i > a:
                index = x_values.index(i)
                x_values = x_values[index:]
                y_values = y_values[index:]
                break
    x_values = x_values
    y_values = [abs(element) for element in y_values]
    delta = abs(x_values[1] - x_values[0])
    integral = 0
    for i in range(1, len(x_values)):
        integral += y_values[i]
    return round(integral*delta, precision)


def integral_trapezoid(x_values, y_values, a=None, b=None, precision=4):
    r"""
    Calculate an area under the curve using trapezoidal rule.

    Calculate integration value of the given function using geometric meaning of define integral.
    Small segment of area is presented as trapezoid with `base = (y(x) + y(x+dx))/2` and `height = dx`.

    Function is present as two lists of values: `x` and `y`. Each `x` value has according `y(x)` value.

    :param x_values: list of equally spaced `x` float values of the given function.
    :param y_values: list of float values of the given function.
    :param a: optional, if present, used as starting point for calculation.
    :param b: optional, if present, used as end point for calculation.
    :param precision: integer, represents number of signs after decimal point.
    :return: float value of area under the curve of the given function.
    """

    if a and b and (a < b):
        for i in x_values:
            if i > b:
                index = x_values.index(i)
                x_values = x_values[:index]
                y_values = y_values[:index]
                break
        for i in x_values:
            if i > a:
                index = x_values.index(i)
                x_values = x_values[index:]
                y_values = y_values[index:]
                break
    x_values = x_values
    y_values = [abs(element) for element in y_values]
    delta = abs(x_values[1] - x_values[0])
    integral = 0
    for i in range(len(x_values)-1):
        integral += (y_values[i] + y_values[i+1])/2
    return round(integral*delta, precision)


def integral_parabolic(x_values, y_values, a=None, b=None, precision=4):
    r"""
    Calculate an area under the curve using Simpson's rule for irregularly spaced data.

    Calculate integration value of the given function using geometric meaning of define integral.

    Function is present as two lists of values: `x` and `y`. Each `x` value has according `y(x)` value.

    :param x_values: list of equally spaced `x` float values of the given function.
    :param y_values: list of float values of the given function.
    :param a: optional, if present, used as starting point for calculation.
    :param b: optional, if present, used as end point for calculation.
    :param precision: integer, represents number of signs after decimal point.
    :return: float value of area under the curve of the given function.
    """

    if a and b and (a < b):
        for i in x_values:
            if i > b:
                index = x_values.index(i)
                x_values = x_values[:index]
                y_values = y_values[:index]
                break
        for i in x_values:
            if i > a:
                index = x_values.index(i)
                x_values = x_values[index:]
                y_values = y_values[index:]
                break
    n = len(x_values)-1
    h = [x_values[i + 1] - x_values[i] for i in range(0, n)]
    y_values = [abs(element) for element in y_values]

    integral = 0
    for i in range(1, n, 2):
        h0, h1 = h[i - 1], h[i]
        h1plush0, h1divh0, h1mulh0 = h1 + h0, h1 / h0, h1 * h0
        integral += ((h1plush0 / 6) *
                     ((2 - h1divh0) * y_values[i - 1]
                      + (h1plush0 ** 2 / h1mulh0) * y_values[i]
                      + (2 - 1 / h1divh0) * y_values[i + 1])
                     )

    if n % 2 != 0:
        h0, h1 = h[n - 2], h[n - 1]
        integral += y_values[n] * (2 * h1 ** 2 + 3 * h0 * h1) / (6 * (h0 + h1))
        integral += y_values[n - 1] * (h1 ** 2 + 3 * h1 * h0) / (6 * h0)
        integral -= y_values[n - 2] * h1 ** 3 / (6 * h0 * (h0 + h1))
    return round(integral, precision)