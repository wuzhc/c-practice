#include <stdio.h>

int max(int x, int y);
int min(int x,int y);
int get_arr_max_val(int * arr);
void printf_arr(int * p);


main()
{
    char s[100] = "$#1#2#2#1#2#3#2#1#";
    //printf("请输入一个字符串:");
    //scanf("%s", s);

    int i;
    int id=0; //中心位置
    int mx=0; //最大边界值
    int p[1000];
    memset(p, 0, sizeof(p));

    for(i=1;s[i]!='\0';i++)
    {
        p[i] = mx > i ? min(p[2*id-i], mx-i) : 1;
        //printf("p[2*%d-%d]=%d\n", id, i, p[2*id-i]);
        //exit(-1);
        while(s[i+p[i]] == s[i-p[i]])
        {
            p[i]++;
        }
        //printf("p[%d]=%d\n",i,p[i]);
        if(i+p[i]>mx)
        {
            mx=i+p[i];
            id=i;
        }
    }

    printf("当前字符串%s的最长回文子串为%d\n", s, get_arr_max_val(p));
}

int max(int x, int y)
{
    return x>y?x:y;
}

int min(int x,int y)
{
    return x<y?x:y;
}

int get_arr_max_val(int * arr)
{
    int i=0;
    int maxVal=arr[i];
    while(arr[i+1]>0)
    {
        maxVal = max(maxVal,arr[i+1]);
        i++;
    }
    return maxVal;
}

void printf_arr(int * p)
{
    int j;
    int len = sizeof(p)/sizeof(p[0]);
    for(j=0;j<len;j++)
    {
        printf("%d\n", p[j]);
    }
}
