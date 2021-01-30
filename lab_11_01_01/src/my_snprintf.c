#include <stdarg.h>
#include <stdbool.h>

#include "my_snprintf.h"
#include "macrologger.h"

#define MAX_NUM_LEN 25

#define ADD_NUM(type, va_arg_type, func) \
    type num = va_arg(add_params, va_arg_type); \
    char str_num[MAX_NUM_LEN + 2]; \
    func(num, MAX_NUM_LEN + 2, str_num); \
    add_string(result, size, str_num, &cur_size, &format_size); \

void add_char(char *restrict result, const size_t size, const char cur_ch,
              size_t *const cur_size, size_t *const format_size)
{
    LOG_DEBUG("format_size = %ld", *format_size);
    LOG_DEBUG("size - 1 = %ld", size - 1);

    if (size && *format_size < size - 1)
        result[(*cur_size)++] = cur_ch;
}

void add_string(char *restrict result, const size_t size, char *restrict string,
                size_t *const cur_size, size_t *const format_size)
{
    if (!string)
        string = "(null)";

    while (*string)
    {
        add_char(result, size, *string, cur_size, format_size);

        (*format_size)++;
        string++;
    }

    (*format_size)--;
}

void nonnegative_num_to_str(unsigned long long int num, const size_t size, 
                            const unsigned int base, char *const str)
{
    if (!size || !str || !base)
        return;

    char tmp[MAX_NUM_LEN + 1];
    short int len = 0;

    while (num && len < size - 1)
    {
        tmp[len++] = num % base + ((num % base < 10) ? '0': 'a' - 10);
        num /= base;
    }

    str[0] = '0';
    short int num_len = len ? 0 : 1;
    while (len)
        str[num_len++] = tmp[--len];

    str[num_len] = '\0';
}

void hex_to_str(const unsigned int num, const size_t size, char *const str)
{
   nonnegative_num_to_str(num, size, 16, str); 
}

void long_octal_to_str(const unsigned long int num, const size_t size, char *const str)
{
   nonnegative_num_to_str(num, size, 8, str); 
}

void short_int_to_str(const short int num, const size_t size, char *const str)
{
    short int len = 0;
    int pos_num = num;

    if (num < 0)
    {
        str[len++] = '-';
        pos_num = -num;
    }

    LOG_DEBUG("%hd", pos_num);
    nonnegative_num_to_str(pos_num, size - 1, 10, str + len);
}

int my_snprintf(char *restrict result, const size_t size, const char *restrict format, ...)
{
    LOG_INFO("%s", "my_snprintf");

    size_t cur_size = 0;
    size_t format_size = 0;

    va_list add_params;
    va_start(add_params, format);

    for (size_t i = 0; format[i]; i++)
    {
        if ('%' == format[i])
        {
            LOG_INFO("%s", "%");
            i++;

            if ('c' == format[i])
                add_char(result, size, (char) va_arg(add_params, int), &cur_size, &format_size);
            else if ('s' == format[i])
            {
                char *string = va_arg(add_params, char *);
                add_string(result, size, string, &cur_size, &format_size);
            }
            else if ('x' == format[i])
            {
                LOG_INFO("%s", "hex");
                ADD_NUM(unsigned int, unsigned int, hex_to_str);
            }
            else if ('h' == format[i] && '\0' != format[i] && 'd' == format[i + 1])
            {
                LOG_INFO("%s", "short");
                i++;
                ADD_NUM(short int, int, short_int_to_str);
            }
            else if ('l' == format[i] && '\0' != format[i] && 'o' == format[i + 1])
            {
                LOG_INFO("%s", "long octal");
                i++;
                ADD_NUM(long unsigned int, long unsigned int, long_octal_to_str);
            }
            else
                add_char(result, size, '%', &cur_size, &format_size);
        }
        else
            add_char(result, size, format[i], &cur_size, &format_size);

        format_size++;
    }

    if (size)
        result[cur_size] = '\0';

    va_end(add_params);
    return format_size;
}
