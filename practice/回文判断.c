#include <stdio.h>
#include <stdbool.h>

bool isPalindrome(char * s);

int main()
{
    char s[] = "asd1fdsa";
    if (isPalindrome(s)) {
        printf("yes");
    } else {
        printf("no");
    }

    return 0;
}

bool isPalindrome(char * s)
{
    if (NULL == s) {
        return false;
    }

    char * front, * rear;
    front = s;
    rear = strlen(s) + s - 1;
    while (front < rear) {
        if (*front != *rear) {
            return false;
        }
        front++;
        rear--;
    }
    return true;
}
