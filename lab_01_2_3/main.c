//Нахождение общего сопротивления параллельного соединения трех резисторов

#include <stdio.h>

int main(void)
{
    float resis1, resis2, resis3;
    float total_resis;

    printf("Enter three resistances: ");
    scanf("%f%f%f", &resis1, &resis2, &resis3);

    total_resis = 1 / (1 / resis1 + 1 / resis2 + 1 / resis3);

    printf("The total resistance is %.5f", total_resis);

    return 0;
}
