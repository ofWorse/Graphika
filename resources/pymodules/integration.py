def integral_linear(x_values, y_values, a=None, b=None, precision=4):
    if a or b:
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
    y_values = y_values
    delta = x_values[1] - x_values[0]
    integral = 0
    for i in range(len(x_values)-1):
        integral += y_values[i]
    return round(integral*delta, precision)


def integral_trapezoid(x_values, y_values, a=None, b=None, precision=4):
    if a or b:
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
    y_values = y_values
    delta = x_values[1] - x_values[0]
    integral = (y_values[0] + y_values[-1])/2
    for i in range(1, len(x_values)-1):
        integral += y_values[i]
    return round(integral*delta, precision)


def integral_parabolic(x_values, y_values, a=None, b=None, precision=4):
    if a or b:
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
    if len(x_values) // 2 != 0:
        x_values = x_values[0:-1]
        y_values = y_values[0:-1]
    y_values_l = y_values[0::2]
    y_values_r = y_values[1::2]
    delta = x_values[1] - x_values[0]
    integral = y_values[0] + y_values[-1]
    for i in range(len(x_values)//2):
        integral += (4*y_values_l[i] + 2*y_values_r[i])
    return round(integral*(delta/3), precision)
