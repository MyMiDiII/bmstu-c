//Перевод секунд в часы, минуты и секунды

#include <stdio.h>

#define SEC_IN_HOURS 3600
#define SEC_IN_MINS 60

int main(void)
{
    int time;
    int hours, minutes, seconds;

    printf("Enter time in seconds: ");
    scanf("%d", &time);

    hours = time / SEC_IN_HOURS;
    time %= SEC_IN_HOURS;
    minutes = time / SEC_IN_MINS;
    seconds = time % SEC_IN_MINS;

    printf("%d hour(s), %d minute(s), %d second(s)", hours, minutes, seconds);

    return 0;
}
