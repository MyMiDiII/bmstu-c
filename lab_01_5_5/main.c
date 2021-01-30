//Вывод числа по цифрам

#include <stdio.h>

#define OK 0
#define INPUT_ERROR 1
#define NOT_NATURAL 2
#define NUM_BASE 10

int out_number(int num)
{
    if (num > 0)
    {
        int max_digit_place = 1;
        long long int div_num = NUM_BASE;
        int i;

        //поиск количества цифр в числе
        while (num > div_num)
        {
            max_digit_place += 1;
            div_num *= NUM_BASE;
        }
        div_num /= NUM_BASE;

        //вывод
        while (max_digit_place > 0)
        {
            i = num / div_num;
            printf("%d", i);
            num = num % div_num;
            div_num /= NUM_BASE;
            max_digit_place -= 1;
        }
		
        return OK;
    }
    else
    {
        printf("Non-natural number was entered.");
        return NOT_NATURAL;
    }
}

int main(void)
{
    int number;
    int res_in;
    int exit_code;

    printf("Input a natural number: ");
    res_in = scanf("%d", &number);

    if (res_in == 1)
    {
        exit_code = out_number(number);
    }
    else
    {
        printf("Input error.");
        exit_code = INPUT_ERROR;
    }
	
    return exit_code;
}
