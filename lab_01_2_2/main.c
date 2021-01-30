// Нахождение периметра треугольника по координатам его вершин.

#include <stdio.h>
#include <math.h>

int main()
{
    float x1, y1, x2, y2, x3, y3;
    float diffx1, diffx2, diffx3;
    float diffy1, diffy2, diffy3;
    float side1, side2, side3;
    float perimeter;

    printf("Enter the coorginates of first point: ");
    scanf("%f%f", &x1, &y1);

    printf("Enter the coorginates of second point: ");
    scanf("%f%f", &x2, &y2);

    printf("Enter the coorginates of third point: ");
    scanf("%f%f", &x3, &y3);

    //вычисление разности координат
    diffx1 = x1 - x2;
    diffx2 = x2 - x3;
    diffx3 = x3 - x1;
    diffy1 = y1 - y2;
    diffy2 = y2 - y3;
    diffy3 = y3 - y1;

    //вычисление длин сторон
    side1 = sqrt(diffx1 * diffx1 + diffy1 * diffy1);
    side2 = sqrt(diffx2 * diffx2 + diffy2 * diffy2);
    side3 = sqrt(diffx3 * diffx3 + diffy3 * diffy3);

    //вычисление периметра
    perimeter = side1 + side2 + side3;

    printf("The perimeter of that triangle is %.5f", perimeter);

    return 0;
}
