#include <stdio.h>

static int count=0;
void full_permutation(char* str,int begin,int end);

main()
{
    char s[100];
    printf("������һ���ַ���:");
    scanf("%s",s);

    full_permutation(s,0,strlen(s));
    printf("��ǰ�ַ���%sһ����%d������",s,count);
}

void funll_permutation(char * str,int begin,int end)
{

}
