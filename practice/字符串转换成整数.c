#include <stdio.h>

int StrToInt(char *str);

main()
{
    char s[] = "10522545459";
    printf("%d", StrToInt(s));
}

int StrToInt(char *str)
{
    int n = 0;
    int sign = 1; //1是正数，-1是负数

    int MAX_INT = (int)((unsigned)~0 >> 1);
    int MIN_INT = -(int)((unsigned)~0 >> 1) - 1;

    if (*str == '-' || *str == '+') {
        if (*str == '-') {
            sign = -1;
        }
        *str++;
    }


    while(*str)
    {
        int c = *str - '0';

        //处理溢出
        if (sign > 0 && (n > MAX_INT / 10 || (n == MAX_INT / 10 && c > MAX_INT % 10)))
        {
            n = MAX_INT;
            break;
        }
        else if (sign < 0 && (n >(unsigned)MIN_INT / 10 || (n == (unsigned)MIN_INT / 10 && c > (unsigned)MIN_INT % 10)))
        {
            n = MIN_INT;
            break;
        }

        n = n * 10 + c;
        *str++;
    }

    return n;
}
