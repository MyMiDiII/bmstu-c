"""
    Модуль c командами, вызывающимися из интерфейса
"""

import tkinter.messagebox as box

from py.c_commands import create_fib_arr
from py.c_commands import delete_repeated

MAX_INT_FIB_NUM = 47
MAX_INT = 32767
MAX_LEN = MAX_INT
MIN_INT = -(MAX_INT - 1)


def generate(size_entry, res_entry):
    """
        Генерация массива с числами Фибоначчи
    """

    try:
        size = int(size_entry.get())
        assert size > 0
        assert size < MAX_INT_FIB_NUM + 1

        arr = create_fib_arr(size)
        clear(res_entry)
        res_entry.insert(0, arr)

    except (ValueError, AssertionError):
        box.showerror("Неверный размер", "Размер -- целое k, где 0 < k < 48")


def delete(enter_arr, res_arr):
    """
        Удаление повторяющиxся элементов массива
    """

    try:
        arr = list(map(int, enter_arr.get().split()))

        for element in arr:
            assert element <= MAX_INT
            assert element >= MIN_INT

        assert len(arr) > 0
        assert len(arr) < MAX_LEN

        result = delete_repeated(arr)
        clear(res_arr)
        res_arr.insert(0, result)

    except ValueError:
        box.showerror("Неверные данные массива",
                      "Элементы -- целые числа, разделенные пробелом!")

    except AssertionError:
        box.showerror("Неверные данные массива",
                      "Длина от 1 до %d,\n" % MAX_LEN +
                      "элементы от %d до %d!" % (MAX_INT, MIN_INT))


def close(window):
    """
        Закрытие приложения
    """

    window.destroy()


def author():
    """
        Открытие окна с информацией об авторе
    """

    box.showinfo('Об авторе', 'Маслова Марина.\nИУ7-33Б.')


def clear(entry):
    """
        Очистка поля ввода
    """

    entry.delete(0, 'end')


def clear_all(entries):
    """
        Очистка нескольких полей ввода
    """

    for entry in entries:
        clear(entry)
