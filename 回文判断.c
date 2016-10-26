#include <stdio.h>
#include <stdbool.h>

bool IsPalindrome(const char * s);

main()
{
    char s[] = "asdfdsa";
    if (IsPalindrome(s)) {
        printf("yes");
    } else {
        printf("no");
    }
}

bool IsPalindrome(const char * s)
{
    if (s == NULL) {
        return false;
    }

    const char * front, * back;

    //��ʼ��ͷָ���δָ��
    front = s;
    back = strlen(s) + s - 1;

    while (front < back)
    {
        if (*front != *back) {
            return false;
        }
        front++;
        back--;
    }

    return true;
}
