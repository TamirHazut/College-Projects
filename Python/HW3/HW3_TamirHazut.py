from functools import reduce
import functools
import datetime
import traceback


# Q1
def sum_lst(lst):
    return reduce((lambda x, y: x + y), lst)


# Q2
def goto_replacement():
    while True:
        number = int(input())
        if number < 0:
            break
        if number % 2 == 0:
            print("even")
        else:
            print("odd")
    print("all done")


# Q3
def dater(func):
    functools.wraps(func)

    def wrapper_dater(*args, **kwargs):
        value = func(*args, **kwargs)
        print(datetime.datetime.now().strftime("%d/%m/%Y - %H:%M:%S"))
        return value
    return wrapper_dater


class Account(object):
    def __init__(self, name, acc_num, balance: float):
        self._name = name
        self._acc_num = acc_num
        self._balance = balance
        self._credit = 1500

    @dater
    def deposit(self, amount: float):
        if amount > 0:
            self._balance = self._balance + amount
            print("DEPOSIT:", self._acc_num, "-", self._name, "- AMOUNT:", amount, "- New Balance:", self.get_balance())
            return True
        return False

    @dater
    def withdraw(self, amount: float):
        if amount <= self.get_balance():
            self._balance -= amount
            print("WITHDRAW:", self._acc_num, "-", self._name, "- AMOUNT:", amount, "- New Balance:", self.get_balance())
            return True
        return False

    def get_balance(self):
        return self._balance

    def transfer_through_accounts(self, receiver, amount: float):
        if self.withdraw(amount):
            receiver.deposit(amount)
            return True
        return False


def bank_balance(bank: list):
    current_balance = 0
    for account in bank:
        current_balance += account.get_balance()
    yield float(current_balance)


def q3():
    acc1 = Account('Tamir', 1000, 1150)
    acc2 = Account('Noy', 1001, 3000)
    acc3 = Account('Gal', 1001, 1000)
    acc4 = Account('Shalev', 1001, 3000)
    acc5 = Account('Dor', 1001, 3000)
    acc6 = Account('Shahar', 1001, 3000)
    bank = [acc1, acc2, acc3, acc4, acc5, acc6]
    for balance in bank_balance(bank):
        print(balance)


def q4():
    test_acc = Account('Test', 1000, 1000)
    test_acc2 = Account('Test2', 1000, 844.5)
    acc_methods = Account.__dict__
    acc_methods = list(k for k, v in acc_methods.items() if '__' not in k)
    try:
        getattr(test_acc, acc_methods[0])(155.5)
        assert getattr(test_acc, acc_methods[2])() == 1155.5, 'After deposit method should be 1155.5'
        getattr(test_acc, acc_methods[1])(155.5)
        assert getattr(test_acc, acc_methods[2])() == 1000, 'After withdraw method should be 1000'
        getattr(test_acc, acc_methods[0])(155.5)
        assert getattr(test_acc, acc_methods[2])() == 1155.5, 'Balance should be 1155.5'
        getattr(test_acc, acc_methods[3])(test_acc2, 155.5)
        assert getattr(test_acc, acc_methods[2])() == 1000, 'Account 1: Balance should be 1000'
        assert getattr(test_acc2, acc_methods[2])() == 1000, 'Account 2: Balance should be 1000'
    except AssertionError:
        traceback.print_exc()


def word_generator(words):
    for word in words:
        if word.find('e') == -1:
            yield str(word)


def q5():
    f = open("words.txt", 'r')
    words = f.read().split(',')
    for word in word_generator(words):
        print(word)


if __name__ == '__main__':
    # print(sum_lst((1, 4, 5, 10)))
    # goto_replacement()
    # 2.b - פרוצדורה
    # acc1 = Account('Tamir', 313521965, 1150)
    # acc2 = Account('Noy', 313586935, 3000)
    # acc1.withdraw(50)
    # acc2.transfer_through_accounts(acc1, 190)
    # q3()
    # q4()
    q5()
