#include <stdbool.h>

#include "my_strspn.h"

my_size_t my_strspn(const char *str, const char *sym)
{
    my_size_t len = 0;

    for (const char *i = str; *i != '\0'; i++)
    {
        bool is_in_sym = false;
        for (const char *j = sym; *j != '\0'; j++)
        {
            if (*i == *j)
            {
                is_in_sym = true;
            }
        }

        if (!is_in_sym)
        {
            return len;
        }

        len++;
    }

    return len;
}

