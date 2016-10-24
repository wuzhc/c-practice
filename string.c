#include <stdio.h>
#include <string.h>

void leftShiftOne(char * s, int len);
void leftRotateString(char * s, int len, int start);
void reverseStr(char * s, int from, int to);
void leftRotateString_2(char* s,int len,int start);

main()
{
    //解法一：暴力移位法
    //char str[] = "Hello world";
    //printf("原有字符串%s\n", str);
    //leftRotateString(str, strlen(str), 2);
    //printf("移动后的字符串%s\n",str);

    //解法二：三步反转法
    char str[] = "123456789";
    printf("原有字符串%s\n", str);
    leftRotateString_2(str, strlen(str), 7);
    printf("翻转后的字符串%s\n", str);
}

//将首位字符移动到最后一位
void leftShiftOne(char * s, int len)
{
    int i;
    char t = s[0];
    for (i=1;i<len;i++) {
        s[i-1] = s[i];
    }
    s[len-1] = t;
}

//从start位置开始放在末尾
void leftRotateString(char * s, int len, int start)
{
    while (start--)
    {
        leftShiftOne(s, len);
    }
}

//翻转字符串
void reverseStr(char * s, int from, int to)
{
    char t;
    while (to > from) {
        t = s[from];
        s[from] = s[to];
        s[to] = t;
        --to;
        ++from;
    }
}

//三步反转法
void leftRotateString_2(char* s,int len,int start)
{
    start %= len; //start不能大于len的值

    reverseStr(s, 0, start-1);
    printf("第一次翻转%s\n", s);

    reverseStr(s, start, len-1);
    printf("第二次翻转%s\n", s);

    reverseStr(s, 0, len-1);
    printf("第三次翻转%s\n", s);
}
