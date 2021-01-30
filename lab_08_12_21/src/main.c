#include <stdio.h>

#include "errors.h"
#include "macrologger.h"
#include "fileio.h"
#include "modes.h"
#include "matrix.h"
#include "actions.h"

int main(int argc, char **argv)
{
    LOG_INFO("%s", "BEGIN");

    FILE *fmatrix1 = NULL, *fresult = NULL;
    int exit_code = OK, mode;
    matrix_t matrix1 = { .data = NULL }; 

    exit_code = check_main_parameters(argc, argv, &mode);

    if (!exit_code)
        exit_code = fopen_by_mode(&fmatrix1, argv[2], MATRIX1_MODE);

    if (!exit_code)
        exit_code = fopen_by_mode(&fresult, argv[(O_MODE == mode) ? 3 : 4],
                                  RESULTS_MODE);

    if (!exit_code)
       exit_code = fread_matrix(fmatrix1, &matrix1);

    if (!exit_code && O_MODE == mode)
    {
        double determinant;
        exit_code = find_determinant(&matrix1, &determinant);

        if (!exit_code)
            if (fprintf(fresult, "%lf", determinant) < 0)
                exit_code = ERR_FPRINTF;
    }
    else if (!exit_code)
    {
        matrix_t matrix2 = { .data = NULL }, result = { .data = NULL };
        FILE *fmatrix2 = NULL;
        exit_code = fopen_by_mode(&fmatrix2, argv[3], MATRIX2_MODE);

        if (!exit_code)
            exit_code = fread_matrix(fmatrix2, &matrix2);

        if (!exit_code && A_MODE == mode)
            exit_code = add_matrixes(&matrix1, &matrix2, &result);

        else if (!exit_code)
            exit_code = multiply_matrixes(&matrix1, &matrix2, &result);
        
        if (!exit_code)
            exit_code = fwrite_matrix(fresult, &result);

        free_data(matrix2.data);
        free_data(result.data);
        fclose_by_error(&fmatrix2, &exit_code, ERR_OPEN_MATRIX2_FILE);
    }

    free_data(matrix1.data);
    fclose_by_error(&fmatrix1, &exit_code, ERR_OPEN_MATRIX1_FILE);
    fclose_by_error(&fresult, &exit_code, ERR_OPEN_RESULTS_FILE);
    print_error(exit_code);

    return exit_code;
}