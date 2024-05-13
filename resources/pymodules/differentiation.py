r"""
author: Konak Vladimir Evgen'evich

last edited: 05.13.2024

organisation: Dnevnie mechaniki
"""


def differential_2p(x_values, y_values, x_point, order=1):
    r"""
    Inner method of :func:`differential_2_points` and :func:`differential_2p_for_plot`.

    :param x_values: list of equally spaced `x` float values of the given function.
    :param y_values: list of float values of the given function.
    :param x_point: `x` point at which the derivative is calculated.
    :param order: integer, order of the differentiation.
    :return: float value of derivative at the desired point.
    """

    x_values = x_values
    y_values = y_values
    x_point = float(x_point)
    order = int(order)
    delta = (x_values[1] - x_values[0])
    index = 0
    for i in x_values:
        if i > x_point:
            index = x_values.index(i) - 1
            break
    if order == 1:
        return (y_values[index+1] - y_values[index]) / delta
    else:
        order -= 1
        return ((differential_2p(x_values, y_values, x_values[index+1], order) -
                 differential_2p(x_values, y_values, x_values[index], order))
                / delta)


def differential_3p(x_values, y_values, x_point, order=1):
    r"""
    Inner method of :func:`differential_3_points` and :func:`differential_3p_for_plot`.

    :param x_values: list of equally spaced `x` float values of the given function.
    :param y_values: list of float values of the given function.
    :param x_point: `x` point at which the derivative is calculated.
    :param order: integer, order of the differentiation.
    :return: float value of derivative at the desired point.
    """

    x_values = x_values
    y_values = y_values
    x_point = float(x_point)
    order = int(order)
    delta = (x_values[1] - x_values[0])
    index = 0
    for i in x_values:
        if i > x_point:
            index = x_values.index(i) - 1
            break
    if order == 1:
        return (y_values[index+1] - y_values[index-1]) / (2 * delta)
    else:
        order -= 1
        return ((differential_3p(x_values, y_values, x_values[index+1], order) -
                 (differential_3p(x_values, y_values, x_values[index-1], order))) / (2 * delta))


def differential_5p(x_values, y_values, x_point, order=1):
    r"""
    Inner method of :func:`differential_5_points` and :func:`differential_5p_for_plot`.

    :param x_values: list of equally spaced `x` float values of the given function.
    :param y_values: list of float values of the given function.
    :param x_point: `x` point at which the derivative is calculated.
    :param order: integer, order of the differentiation.
    :return: float value of derivative at the desired point.
    """

    x_values = x_values
    y_values = y_values
    x_point = float(x_point)
    order = int(order)
    delta = (x_values[1] - x_values[0])
    index = 0
    for i in x_values:
        if i > x_point:
            index = x_values.index(i) - 1
            break
    if order == 1:
        return ((y_values[index-2] -
                8 * y_values[index-1] +
                8 * y_values[index+1] -
                y_values[index+2]) /
                (12 * delta))
    else:
        order -= 1
        return ((differential_5p(x_values, y_values, x_values[index-2], order) -
                 8 * differential_5p(x_values, y_values, x_values[index-1], order) +
                 8 * differential_5p(x_values, y_values, x_values[index+1], order) -
                 differential_5p(x_values, y_values, x_values[index+2], order)) /
                (12 * delta))


def differential_2_points(x_values, y_values, x_point, order=1, precision=4):
    r"""
    Find value of function derivative at certain 'x' point using five point schema.

    Function is present as two lists of values: `x` and `y`. Each `x` value has according `y(x)` value.

    :param x_values: list of equally spaced `x` float values of the given function.
    :param y_values: list of float values of the given function.
    :param x_point: `x` point at which the derivative is calculated.
    :param order: integer, order of the differentiation.
    :param precision: integer, represents number of signs after decimal point.
    :return: float value of derivative at the desired point.
    """

    return round(differential_2p(x_values, y_values, x_point, order), precision)


def differential_3_points(x_values, y_values, x_point, order=1, precision=4):
    r"""
    Find value of function derivative at certain 'x' point using five point schema.

    Function is present as two lists of values: `x` and `y`. Each `x` value has according `y(x)` value.

    :param x_values: list of equally spaced `x` float values of the given function.
    :param y_values: list of float values of the given function.
    :param x_point: `x` point at which the derivative is calculated.
    :param order: integer, order of the differentiation.
    :param precision: integer, represents number of signs after decimal point.
    :return: float value of derivative at the desired point.
    """

    return round(differential_3p(x_values, y_values, x_point, order), precision)


def differential_5_points(x_values, y_values, x_point, order=1, precision=4):
    r"""
    Find value of function derivative at certain 'x' point using five point schema.

    Function is present as two lists of values: `x` and `y`. Each `x` value has according `y(x)` value.

    :param x_values: list of equally spaced `x` float values of the given function.
    :param y_values: list of float values of the given function.
    :param x_point: `x` point at which the derivative is calculated.
    :param order: integer, order of the differentiation.
    :param precision: integer, represents number of signs after decimal point.
    :return: float value of derivative at the desired point.
    """

    return round(differential_5p(x_values, y_values, x_point, order), precision)


def differentiate_at_point(x_values, y_values, x_point, schema=2, order=1, precision=4):
    match schema:
        case 2:
            return round(differential_2p(x_values, y_values, x_point, order), precision)
        case 3:
            return round(differential_3p(x_values, y_values, x_point, order), precision)
        case 5:
            return round(differential_5p(x_values, y_values, x_point, order), precision)


def differential_2p_for_plot(x_values, y_values, order=1, precision=4):
    r"""
    Differentiate function at presented interval using two point schema.

    :param x_values: list of equally spaced `x` float values of the given function.
    :param y_values: list of float values of the given function.
    :param order: integer, order of the differentiation.
    :param precision: integer, represents number of signs after decimal point.
    :return: tuple consisting of two lists of float values: `x` and `y\'(x)`
    """

    x_for_diff = x_values[:-1 * order]
    order = int(order)
    y_for_plot = list()
    for i in x_for_diff:
        y_for_plot.append(round(differential_2p(x_values, y_values, i, order), precision))
        x_for_diff[x_for_diff.index(i)] = round(i, precision)
    return x_for_diff, list(dict.fromkeys(y_for_plot))


def differential_3p_for_plot(x_values, y_values, order=1, precision=4):
    r"""
    Differentiate function at presented interval using three point schema.

    :param x_values: list of equally spaced `x` float values of the given function.
    :param y_values: list of float values of the given function.
    :param order: integer, order of the differentiation.
    :param precision: integer, represents number of signs after decimal point.
    :return: tuple consisting of two lists of float values: `x` and `y\'(x)`
    """
    x_for_diff = x_values[1 * order:-1 * order]
    order = int(order)
    y_for_plot = list()
    for i in x_for_diff:
        y_for_plot.append(round(differential_3p(x_values, y_values, i, order), precision))
        x_for_diff[x_for_diff.index(i)] = round(i, precision)
    return x_for_diff, list(dict.fromkeys(y_for_plot))


def differential_5p_for_plot(x_values, y_values, order=1, precision=4):
    r"""
    Differentiate function at presented interval using three point schema.

    :param x_values: list of equally spaced `x` float values of the given function.
    :param y_values: list of float values of the given function.
    :param order: integer, order of the differentiation.
    :param precision: integer, represents number of signs after decimal point.
    :return: tuple consisting of two lists of float values: `x` and `y\'(x)`
    """

    x_for_diff = x_values[2*order:-2 * order]
    order = int(order)
    y_for_plot = list()
    for i in x_for_diff:
        y_for_plot.append(round(differential_5p(x_values, y_values, i, order), precision))
        x_for_diff[x_for_diff.index(i)] = round(i, precision)
    return x_for_diff, list(dict.fromkeys(y_for_plot))


def differentiate_func(x_values, y_values, schema=3, order=1, precision=4):
    x_values = x_values
    y_values = y_values
    order = int(order)
    y_for_plot = list()
    match schema:
        case 2:
            x_for_diff = x_values[:-1 * order]
            for i in x_for_diff:
                y_for_plot.append(differential_2p(x_values, y_values, i, order))
                x_for_diff[x_for_diff.index(i)] = round(i, precision)
            return x_for_diff, list(dict.fromkeys(y_for_plot))
        case 3:
            x_for_diff = x_values[1*order:-1 * order]
            for i in x_for_diff:
                y_for_plot.append(differential_3p(x_values, y_values, i, order))
                x_for_diff[x_for_diff.index(i)] = round(i, precision)
            return x_for_diff, list(dict.fromkeys(y_for_plot))
        case 5:
            x_for_diff = x_values[2 * order:-2 * order]
            for i in x_for_diff:
                y_for_plot.append(differential_5p(x_values, y_values, i, order))
                x_for_diff[x_for_diff.index(i)] = round(i, precision)
            return x_for_diff, list(dict.fromkeys(y_for_plot))
