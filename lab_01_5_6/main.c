//Пересечение двух отрезков

#include <stdio.h>
#include <math.h>

#define OK 0
#define INPUT_ERROR 1
#define LOGIC_INPUT_ERROR 2
#define CROSS 1
#define NOT_CROSS 0
#define EPS 1e-7

float skew(float xv1, float yv1, float xv2, float yv2, float xv3, float yv3)
{
    return (xv1 - xv2) * (yv1 - yv3) - (xv1 - xv3) * (yv1 - yv2);
}

int cross(float x1, float y1, float x2, float y2, float x3, float y3, float x4,
float y4)
{
    float skew_1, skew_2, skew_3, skew_4;

    skew_1 = skew(x1, y1, x2, y2, x3, y3);
    skew_2 = skew(x1, y1, x2, y2, x4, y4);
    skew_3 = skew(x3, y3, x4, y4, x1, y1);
    skew_4 = skew(x3, y3, x4, y4, x2, y2);

    if (skew_1 * skew_2 < 0 && skew_3 * skew_4 < 0)
    {
        return CROSS;
    }
    else
    {
        return NOT_CROSS;
    }
}

int main(void)
{
    //координаты концов отрезков
    float x_p1, x_p2, y_p1, y_p2;
    float x_m1, x_m2, y_m1, y_m2;
    int res_in_1, res_in_2;
    int is_cross;

    printf("Enter the coordinates of the ends of the first segment: ");
    res_in_1 = scanf("%f%f%f%f", &x_p1, &y_p1, &x_p2, &y_p2);

    printf("Enter the coordinates of the ends of the second segment: ");
    res_in_2 = scanf("%f%f%f%f", &x_m1, &y_m1, &x_m2, &y_m2);

    if (res_in_1 == 4 && res_in_2 == 4)
    {
        if ((fabs(x_p1 - x_p2) < EPS && fabs(y_p1 - y_p2) < EPS)
            || (fabs(x_m1 - x_m2) < EPS && fabs(y_m1 - y_m2) < EPS))
        {
            printf("Incorrect coordinates");
            return LOGIC_INPUT_ERROR;
        }
        else
        {
            is_cross = cross(x_p1, y_p1, x_p2, y_p2, x_m1, y_m1, x_m2, y_m2);
            printf("%d", is_cross);
        }
    }
    else
    {
        printf("Input error");
        return INPUT_ERROR;
    }
}
