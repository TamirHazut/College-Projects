import numpy as np
import matplotlib.pyplot as plt
"""
Tamir Hazut
313521965

f(x) = 2^x
Interpolation Points: (0,1), (1,2), (2,4)
"""


def divide_difference(x, F, n):
    for j in range(1,n):
        for i in range(0,n-j):
            F[i][j] = (F[i][j-1] - F[i+1][j-1])/(x[i]-x[i+j])


def print_difference_table(F, n):
    for i in range(0, n):
        for j in range(0, n-i):
                print(F[i][j], end="\t")
        print("")


def print_polynom(x, F, n):
    if n == 1:
        print(F[0][n], end="", sep="")
    else:
        print_polynom(x, F, n-1)
        print('+', F[0][n-1], end="", sep="")
        for i in range(0, n-1):
            print('(x-', x[i], end=")", sep="")


def plot_graph():
    x = np.arange(0, 4, 0.01)
    f = 2**x
    p = 0.5*x**2+0.5*x+1
    e = f-p
    plt.plot(x, f, color='b', label='f(x)')
    plt.plot(x, p, color='g', label='p(x)')
    plt.plot(x, e, color='r', label='e(x)')
    plt.legend(bbox_to_anchor=(0, 1.02, 1, .102), loc=3, ncol=2, mode='expand', borderaxespad=0)
    plt.show()


if __name__ == '__main__':
    n = 3
    x = np.array([0, 1, 2])
    y = np.zeros((n, n))
    y[0][0] = 1
    y[1][0] = 2
    y[2][0] = 4
    divide_difference(x, y, n)
    print_difference_table(y, n)
    print('P', n-1, '(x)=', end="", sep="")
    print_polynom(x, y, n)
    plot_graph()
