"""
    Модуль для работы с массивами ctypes
"""

import ctypes

LIBS_PATH = './libs/'
ARR_LIB_NAME = 'libarray.so'


def create_fib_arr(size):
    """
        Вызов функции create_fib_arr из библиотеки на Си.
    """

    lib = ctypes.CDLL(LIBS_PATH + ARR_LIB_NAME)

    _create_fib_array = lib.create_fib_array
    _create_fib_array.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int)
    _create_fib_array.restype = None

    arr = (ctypes.c_int * size)()
    _create_fib_array(arr, size)

    return list(arr)


def delete_repeated(arr):
    """
        Вызов функции delete_repeated из библиотеки на Си.
    """

    lib = ctypes.CDLL(LIBS_PATH + ARR_LIB_NAME)

    _delete_repeated = lib.delete_repeated
    _delete_repeated.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int,
                                 ctypes.POINTER(ctypes.c_int), ctypes.c_int)
    _delete_repeated.restype = ctypes.c_int

    len_arr = len(arr)
    tmp_arr = (ctypes.c_int * len_arr)(*arr)

    new_arr_len = 0
    new_arr = (ctypes.c_int * new_arr_len)()

    new_arr_len = _delete_repeated(tmp_arr, len_arr, new_arr, new_arr_len)

    new_arr = (ctypes.c_int * new_arr_len)(*new_arr)

    new_arr_len = _delete_repeated(tmp_arr, len_arr, new_arr, new_arr_len)

    return list(new_arr)
