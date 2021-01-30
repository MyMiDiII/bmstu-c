#include <stdio.h>
#include <stdlib.h>

#include "list_matrix.h"
#include "errors.h"
#include "macrologger.h"
#include "io.h"

int main(void)
{
    int exit_code = OK;

    command_t command;
    exit_code = read_command(&command);

    if (!exit_code)
    {
        if (OUT == command)
            exit_code = do_out();
        else if (ADD == command)
            exit_code = do_add_or_mul(command);
        else if (MUL == command)
            exit_code = do_add_or_mul(command);
        else if (LIN == command)
            exit_code = do_lin();
    }

    return exit_code;
}
