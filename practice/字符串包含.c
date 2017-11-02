#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool StringContain(char *a,char *b);

main()
{
    char a[] = "sdfegh";
    char b[] = "dh";

    if (StringContain(a, b)) {
        printf("yes");
    } else {
        printf("no");
    }

}

// ����õķ�������ʱ�临�Ӷ�O(n + m)���ռ临�Ӷ�O(1)
bool StringContain(char *a,char *b)
{
    int hash = 0;
    int i;
    for (i = 0; i < strlen(a); ++i)
    {
        hash |= (1 << (a[i] - 'A'));
    }

    for (i = 0; i < strlen(b); ++i)
    {
        if ((hash & (1 << (b[i] - 'A'))) == 0)
        {
            return false;
        }
    }
    return true;
}

