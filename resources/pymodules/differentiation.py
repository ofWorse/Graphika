import sympy

"""Core functions"""


def differential_2p(x_values, y_values, x_point, order=1):
    x_values = x_values
    y_values = y_values
    x_point = x_point
    order = order
    delta = sympy.Rational(x_values[1] - x_values[0])
    index = 0
    for i in x_values:
        if i > x_point:
            break
        index = x_values.index(i)
    if order == 1:
        return (y_values[index+1] - y_values[index]) / delta
    else:
        order -= 1
        return ((differential_2p(x_values, y_values, x_values[index+1], order) -
                 differential_2p(x_values, y_values, x_values[index], order))
                / delta)


def differential_3p(x_values, y_values, x_point, order=1):
    x_values = x_values
    y_values = y_values
    x_point = x_point
    order = order
    delta = sympy.Rational(x_values[1] - x_values[0])
    index = 0
    for i in x_values:
        if i > x_point:
            break
        index = x_values.index(i)
    if order == 1:
        return (y_values[index+1] - y_values[index-1]) / (2 * delta)
    else:
        order -= 1
        return ((differential_3p(x_values, y_values, x_values[index+1], order) -
                 (differential_3p(x_values, y_values, x_values[index-1], order))) / (2 * delta))


def differential_5p(x_values, y_values, x_point, order=1):
    x_values = x_values
    y_values = y_values
    x_point = x_point
    order = order
    delta = sympy.Rational(x_values[1] - x_values[0])
    index = 0
    for i in x_values:
        if i > x_point:
            break
        index = x_values.index(i)
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


"""Wrap functions with formatted output"""


def differential_2_points(x_values, y_values, x_point, order=1, precision=4):
    return differential_2p(x_values, y_values, x_point, order).evalf(n=precision, chop=1e-5)


def differential_3_points(x_values, y_values, x_point, order=1, precision=4):
    return differential_3p(x_values, y_values, x_point, order).evalf(n=precision, chop=1e-5)


def differential_5_points(x_values, y_values, x_point, order=1, precision=4):
    return differential_5p(x_values, y_values, x_point, order).evalf(n=precision, chop=1e-5)


def differentiate_at_point(x_values, y_values, x_point, schema=2, order=1, precision=4):
    match schema:
        case 2:
            return differential_2p(x_values, y_values, x_point, order).evalf(n=precision, chop=1e-5)
        case 3:
            return differential_3p(x_values, y_values, x_point, order).evalf(n=precision, chop=1e-5)
        case 5:
            return differential_5p(x_values, y_values, x_point, order).evalf(n=precision, chop=1e-5)


"""Polt-ready functions"""


def differential_2p_for_plot(x_values, y_values, order=1, precision=4):
    x_for_diff = x_values[:-1 * order]
    order = order
    y_for_plot = list()
    for i in x_for_diff:
        y_for_plot.append(differential_2p(x_values, y_values, i, order).evalf(n=precision))
        x_for_diff[x_for_diff.index(i)] = round(i, precision)
    return x_for_diff, list(dict.fromkeys(y_for_plot))


def differential_3p_for_plot(x_values, y_values, order=1, precision=4):
    x_for_diff = x_values[1 * order:-1 * order]
    order = order
    y_for_plot = list()
    for i in x_for_diff:
        y_for_plot.append(differential_3p(x_values, y_values, i, order).evalf(n=precision))
        x_for_diff[x_for_diff.index(i)] = round(i, precision)
    return x_for_diff, list(dict.fromkeys(y_for_plot))


def differential_5p_for_plot(x_values, y_values, order=1, precision=4):
    x_for_diff = x_values[2*order:-2*order]
    order = order
    y_for_plot = list()
    for i in x_for_diff:
        y_for_plot.append(differential_5p(x_values, y_values, i, order).evalf(n=precision))
        x_for_diff[x_for_diff.index(i)] = round(i, precision)
    return x_for_diff, list(dict.fromkeys(y_for_plot))


def differentiate_func(x_values, y_values, schema=3, order=1, precision=4):
    x_values = x_values
    y_values = y_values
    order = order
    y_for_plot = list()
    match schema:
        case 2:
            x_for_diff = x_values[:-1 * order]
            for i in x_for_diff:
                y_for_plot.append(differential_2p(x_values, y_values, i, order).evalf(n=precision))
                x_for_diff[x_for_diff.index(i)] = round(i, precision)
            return x_for_diff, list(dict.fromkeys(y_for_plot))
        case 3:
            x_for_diff = x_values[:-1 * order]
            for i in x_for_diff:
                y_for_plot.append(differential_3p(x_values, y_values, i, order).evalf(n=precision))
                x_for_diff[x_for_diff.index(i)] = round(i, precision)
            return x_for_diff, list(dict.fromkeys(y_for_plot))
        case 5:
            x_for_diff = x_values[:-1 * order]
            for i in x_for_diff:
                y_for_plot.append(differential_5p(x_values, y_values, i, order).evalf(n=precision))
                x_for_diff[x_for_diff.index(i)] = round(i, precision)
            return x_for_diff, list(dict.fromkeys(y_for_plot))
