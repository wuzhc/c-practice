#include <stdio.h>
#include <string.h>

void leftShiftOne(char * s, int len);
void leftRotateString(char * s, int len, int start);
void reverseStr(char * s, int from, int to);
void leftRotateString_2(char* s,int len,int start);

main()
{
    //�ⷨһ��������λ��
    //char str[] = "Hello world";
    //printf("ԭ���ַ���%s\n", str);
    //leftRotateString(str, strlen(str), 2);
    //printf("�ƶ�����ַ���%s\n",str);

    //�ⷨ����������ת��
    char str[] = "123456789";
    printf("ԭ���ַ���%s\n", str);
    leftRotateString_2(str, strlen(str), 7);
    printf("��ת����ַ���%s\n", str);
}

//����λ�ַ��ƶ������һλ
void leftShiftOne(char * s, int len)
{
    int i;
    char t = s[0];
    for (i=1;i<len;i++) {
        s[i-1] = s[i];
    }
    s[len-1] = t;
}

//��startλ�ÿ�ʼ����ĩβ
void leftRotateString(char * s, int len, int start)
{
    while (start--)
    {
        leftShiftOne(s, len);
    }
}

//��ת�ַ���
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

//������ת��
void leftRotateString_2(char* s,int len,int start)
{
    start %= len; //start���ܴ���len��ֵ

    reverseStr(s, 0, start-1);
    printf("��һ�η�ת%s\n", s);

    reverseStr(s, start, len-1);
    printf("�ڶ��η�ת%s\n", s);

    reverseStr(s, 0, len-1);
    printf("�����η�ת%s\n", s);
}
