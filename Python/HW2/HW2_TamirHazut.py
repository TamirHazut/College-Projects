import collections
import operator


def sum_nested_lists(temp_list: list):
    total = 0
    for i in temp_list:
        if isinstance(i, list):
            total += sum_nested_lists(i)
        else:
            total += i
    return total


def q1():
    current_list = [[12, 4], [1], [2, 3]]
    print(sum_nested_lists(current_list))


def hailstone(n: int):
    while n > 1:
        if n % 2 == 0:
            n = int(n/2)
        else:
            n = int(n*3+1)
        yield n


def q2_a():
    n = 5
    print(n)
    for i in hailstone(n):
        print(i)


class Hailstone:
    def __init__(self, n: int):
        self.stopIter = 1
        self.n = n

    def __iter__(self):
        return self

    def __next__(self):
        if self.n == self.stopIter:
            raise StopIteration
        if self.n % 2 == 0:
            self.n = int(self.n / 2)
        else:
            self.n = int(self.n * 3 + 1)
        return self.n


def q2_b():
    n = 5
    print(n)
    for i in Hailstone(n):
        print(i)


def q2_c():
    n = 5
    print(n)
    generator = (i for i in hailstone(n))
    for num in generator:
        print(num)


def reachable(graph: dict, node):
    visited, queue = [node], collections.deque([node])
    while queue:
        node = queue.popleft()
        for n in graph[node]:
            if n not in visited:
                visited.append(n)
                queue.append(n)
    return visited


def q3():
    my_graph = {'a': ['b', 'c'], 'b': ['d'], 'c': [], 'd': ['a'], 'e': ['d']}
    print(reachable(my_graph, 'a'))


def q5_a():
    x = 10
    print(id(x))
    x += 1
    print(id(x))


class MutableInt(int):
    def __init__(self, value=0):
        self._value = int(value)

    def __add__(self, n):
        if isinstance(n, MutableInt):
            return MutableInt(self._value + n._value)
        return MutableInt(self._value + n)

    def __iadd__(self, n):
        if isinstance(n, MutableInt):
            self._value += n._value
        else:
            self._value += n
        return self

    def __sub__(self, n):
        if isinstance(n, MutableInt):
            return MutableInt(self._value - n._value)
        return MutableInt(self._value - n)

    def __isub__(self, n):
        if isinstance(n, MutableInt):
            self._value -= n._value
        else:
            self._value -= n
        return self

    def __mul__(self, n):
        if isinstance(n, MutableInt):
            return MutableInt(self._value * n._value)
        return MutableInt(self._value * n)

    def __str__(self):
        return str(self._value)

    def __int__(self):
        return self._value

    def __float__(self):
        return float(self._value)

    def __repr__(self):
        return 'Mutable Integer(%s)' % self._value


def q5_b():
    mutable_int = MutableInt()
    print(mutable_int, end=" ")
    print(id(mutable_int))
    mutable_int += 10
    print(mutable_int, end=" ")
    print(id(mutable_int))


def average(x, y):
    return (x + y)/2


def improve(update, close, guess=1):
    while not close(guess):
        guess = update(guess)
    return guess


def approx_eq(x, y, tolerance=1e-3):
    return abs(x-y) < tolerance


def sqrt(a):
    def sqrt_update(x):
        return average(a/x, x)

    def sqrt_close(x):
        return approx_eq(a/x, x)

    return improve(sqrt_update, sqrt_close)


def q6():
    print(sqrt(256))


def sum_all_num_two_pow(temp_list: list):
    needed_nums = list(filter(lambda i: (i < 12) and (i >= 0), temp_list))
    total = 0
    for i in needed_nums:
        total += 2**i
    return total


def q7_a():
    temp_list = [1, 2, 5, 12, 24, 6, 8, -5]
    print(sum_all_num_two_pow(temp_list))


def find_max_res_camera(temp_dict: dict):
    return max(temp_dict.items(), key=lambda k: k[1][1])


def q7_b_c():
    cameras = {'LEQ2B': ('Nikon', 3.68, 4995), 'CAE5D424105': ('Cannon', 3.40, 3899)}
    camera = find_max_res_camera(cameras)
    print(camera[1][1])
    print(camera[0])


if __name__ == '__main__':
    q1()
    q2_a()
    q2_b()
    q2_c()
    q3()
    """
    Q4:
    A tuple is unchangeable so if you want to add a new item/object to the instance python will create a new instance
    with the old objects and the new objects, While list is changeable so you can add new objects to the same instance. 
    """
    q5_a()
    q5_b()
    q6()
    q7_a()
    q7_b_c()