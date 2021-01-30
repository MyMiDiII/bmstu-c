"""
    Модуль для создания графического интерфейса приложения
"""

import tkinter as tk

import py.commands as commands

CLOUD = '#F1F1F2'
GREY = '#BDBABE'
LIGHT_BLUE = '#A1D6E2'
BLUE = '#1996B0'

TITLE_FONT = ('Times New Roman', 18)
FONT = ('Times New Roman', 14)

X = 10
HEIGHT = 30
WIDTH = 340


def create_menu(window):
    """
        Создание строки меню
    """

    menu = tk.Menu()

    menu.add_command(label='Об авторе', command=commands.author)
    menu.add_command(label='Выход', command=lambda: commands.close(window))

    window.config(menu=menu)


def create_enter(window):
    """
        Создание элементов, отвечающих за ввод
    """

    enter_arr_size = tk.Entry(window, font='Calibry 12', bg=CLOUD)
    arr_size_clear = tk.Button(window, text='Очистить', bg=GREY,
                               command=lambda: commands.clear(enter_arr_size))
    generate_btn = tk.Button(window, text='Сгенерировать', bg=GREY,
                             command=lambda: commands.generate(enter_arr_size,
                                                               generated_arr))
    generated_arr = tk.Entry(window, font='Calibry 12', bg=CLOUD)

    enter_arr_size.place(x=X, y=75, height=HEIGHT, width=WIDTH)
    arr_size_clear.place(x=X, y=115, height=HEIGHT, width=WIDTH // 2 - 5)
    generate_btn.place(x=X + WIDTH // 2 + 5, y=115, height=HEIGHT,
                       width=WIDTH // 2 - 5)
    generated_arr.place(x=X, y=185, height=HEIGHT, width=WIDTH)

    enter_arr = tk.Entry(window, font='Calibry 12', bg=CLOUD)
    arr_clear = tk.Button(window, text='Очистить', bg=GREY,
                          command=lambda: commands.clear(enter_arr))
    delete_btn = tk.Button(window, text='Убрать', bg=GREY,
                           command=lambda: commands.delete(enter_arr, res_arr))
    res_arr = tk.Entry(window, font='Calibry 12', bg=CLOUD)

    enter_arr.place(x=X, y=270, height=HEIGHT, width=WIDTH)
    arr_clear.place(x=X, y=310, height=HEIGHT, width=WIDTH // 2 - 5)
    delete_btn.place(x=X + WIDTH // 2 + 5, y=310, height=HEIGHT,
                     width=WIDTH // 2 - 5)
    res_arr.place(x=X, y=390, height=HEIGHT, width=WIDTH)

    clear_all_entries = tk.Button(window, text='Очистить всё',
                                  bg=GREY, command=lambda:
                                  commands.clear_all((enter_arr_size,
                                                      generated_arr,
                                                      enter_arr, res_arr)))
    clear_all_entries.place(x=X, y=430, height=HEIGHT, width=WIDTH)


def create_texts(window):
    """
        Создание текстовых подсказок
    """

    title = tk.Label(window, text='CTYPES', bg=LIGHT_BLUE,
                     font=TITLE_FONT, fg=BLUE)
    arr_size_hint = tk.Label(window, text='Количество чисел Фибоначчи:',
                             bg=LIGHT_BLUE, font=FONT)
    fib_arr_hint = tk.Label(window, text='Числа Фибоначчи:', bg=LIGHT_BLUE,
                            font=FONT)
    delete_hint = tk.Label(window, text='Убрать повторяющиеся из:',
                           bg=LIGHT_BLUE, font=FONT)
    delete_res_hint = tk.Label(window, text='Без повторяющихся:',
                               bg=LIGHT_BLUE, font=FONT)

    title.pack(side='top')
    arr_size_hint.place(x=X, y=40)
    fib_arr_hint.place(x=X, y=150)

    delete_hint.place(x=X, y=230)
    delete_res_hint.place(x=X, y=350)


def create_window():
    """
        Создание и запуск окна приложения
    """

    window = tk.Tk()
    window.title('CTYPES')
    window.geometry('360x480+500+200')
    window.resizable(False, False)
    window.configure(bg=LIGHT_BLUE)

    create_menu(window)
    create_texts(window)
    create_enter(window)

    window.mainloop()


if __name__ == '__main__':
    create_window()
