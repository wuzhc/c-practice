#include <stdio.h>

static int count=0;
void full_permutation(char* str,int begin,int end);

main()
{
    char s[100];
    printf("请输入一个字符串:");
    scanf("%s",s);

    full_permutation(s,0,strlen(s));
    printf("当前字符串%s一共有%d种排列",s,count);
}

void funll_permutation(char * str,int begin,int end)
{

}
