# Tamir Hazut
# 313521965


def q1_a(q1_a_list):
    total_sum = 0
    for i in range(len(q1_a_list)):
        total_sum += sum(q1_a_list[i])
    print(total_sum)


def q1_b(q1_b_list):
    total_sum = sum([sum(j) for j in q1_b_list])
    print(total_sum)


def q2_a(q2_a_string) -> str:
    return q2_a_string[::-1]


def q2_b(q2_b_list) -> list:
    return [b[::-1] for b in q2_b_list][::-1]


def q2_c(q2_c_tuple) -> tuple:
    return q2_a(q2_c_tuple)


def q3_a(q3_a_tuple) -> set:
    union_set = {}
    for temp_set in q3_a_tuple:
        union_set = temp_set.union(union_set)
    chars = sorted(set(filter(lambda item: type(item) == str, union_set)))
    numbers = sorted(set(filter(lambda item: type(item) == int, union_set)))
    union_set = chars + numbers
    return union_set


def q3_b(q3_b_tuple) -> dict:
    temp_set = q3_a(q3_b_tuple)
    temp_dict = {}
    for i in range(len(temp_set)):
        temp_dict[i] = temp_set[i]
    return temp_dict


def q6_a():
    greater_than = 6
    less_than_equal = 9
    compared_number = 10
    x = int(input("Please enter a number: "))
    temp_tuple = (less_than_equal, less_than_equal, greater_than)
    y = temp_tuple[index(x-compared_number)]
    print(y)


def q6_b():
    greater_than = 6
    less_than_equal = 9
    compared_number = 10
    x = int(input("Please enter a number: "))
    y = greater_than if x > compared_number else less_than_equal
    print(y)


def q7_a():
    num1, num2 = [int(x) for x in input("Please enter 2 numbers: ").split()]
    temp_tuple = ((int(num1/2)*2, num2), (int(num2/2)*2, num1), (int(num2/2)*2, num1))
    print_lists(insert_values_using_for(temp_tuple[index(num2-num1)]))


def insert_values_using_for(temp_tuple) -> list:
    high_num = temp_tuple[0]
    low_num = temp_tuple[1]
    temp_list = []
    for i in range(high_num, low_num-1, -2):
        temp_list.append(i)
    return temp_list


def q7_b():
    num1, num2 = [int(x) for x in input("Please enter 2 numbers: ").split()]
    temp_tuple = ((int(num1/2)*2, num2), (int(num2/2)*2, num1), (int(num2/2)*2, num1))
    print_lists(insert_values_using_while(temp_tuple[index(num2-num1)]))


def index(i) -> int:
    return 1 + (i >> 31) - (-i >> 31)


def insert_values_using_while(temp_tuple) -> list:
    high_num = temp_tuple[0]
    low_num = temp_tuple[1]
    temp_list = []
    while high_num >= low_num:
        temp_list.append(high_num)
        high_num -= 2
    return temp_list


def print_lists(temp_list):
    print(*temp_list, sep=' ')
    print(*temp_list[::-1], sep=' ')


if __name__ == '__main__':
    q1_a([[12, 4], [1], [2, 3]])
    q1_b([[12, 4], [1], [2, 3]])
    print(q2_a('hello world'))
    print(q2_b([[12, 4], [1], [2, 3]]))
    print(q2_c((12, 4, 'b', 'A')))
    print(q3_a(({'a', 'b', 'c'}, {2.4, 12, 24.4}, {'b', 'a'}, {'c', 'a', 'b'}, {1, 6, 15, 24})))
    print(q3_b(({'a', 'b', 'c'}, {2.4, 12, 24.4}, {'b', 'a'}, {'c', 'a', 'b'}, {1, 6, 15, 24})))
    q6_a()
    q6_b()
    q7_a()
    q7_b()


