def integral_linear(x_values, y_values, a=None, b=None, precision=4):
    if a and b:
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
    for i in range(len(x_values)):
        integral += y_values[i]
    return round(integral*delta, precision)


def integral_trapezoid(x_values, y_values, a=None, b=None, precision=4):
    if a and b:
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
    integral = (y_values[0] + y_values[-1])/2
    for i in range(1, len(x_values)-1):
        integral += y_values[i]
    return round(integral*delta, precision)


def integral_parabolic(x_values, y_values, a=None, b=None, precision=4):
    if a and b:
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