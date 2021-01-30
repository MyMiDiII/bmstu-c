//Подсчет суммы ряда с точностью eps

#include <stdio.h>
#include <math.h>

#define OK 0
#define INPUT_ERROR 1

double sum(double arg, double prec)
{
    double result = 0;
    double element = 1;
    int current_coef = 1;

    while (fabs(element) > prec)
    {
        result += element;
        element *= arg * arg * current_coef / (current_coef + 1);
        current_coef += 2;
    }

    return result;
}

int main(void)
{
    double x, eps;
    double sum_of_series, exact;
    double absolute, relative;
    int res_in;

    printf("Enter x and eps: ");
    res_in = scanf("%lf%lf", &x, &eps);

    if (res_in == 2 && fabs(x) < 1 && eps > 0 && eps < 1)
    {
        sum_of_series = sum(x, eps);
        exact = 1 / sqrt(1 - x * x);
        absolute = fabs(exact - sum_of_series);
        relative = fabs(absolute / exact);

        printf("Approximate value: %.6f\n", sum_of_series);
        printf("Exact value: %.6f\n", exact);
        printf("Absolute error: %.6f\n", absolute);
        printf("Relative error: %.6f\n", relative);

        return OK;
    }
    else
    {
        printf("Input error");
        return INPUT_ERROR;
    }
}
