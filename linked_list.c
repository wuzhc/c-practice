#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

/*�ڵ�ṹ��*/
typedef struct Node {
    int data;
    struct Node * pNext;
}NODE, * PNODE;

//��������
PNODE create_list();
//��ʾ����
void traverse_list(PNODE pHead);
//�����Ƿ�Ϊ��
bool is_empty(PNODE pHead);
//������
int list_length(PNODE pHead);
//ɾ��ָ��λ�õĽڵ�
int delete_node(PNODE pHead, int pos);
//�����½ڵ�
bool insert_node(PNODE pHead, int pos, int val);


main()
{
    PNODE pHead;

    //��������
    pHead = create_list();

    //��ӡ����
    traverse_list(pHead);

    //�ж������Ƿ�Ϊ��
    if (is_empty(pHead)) {
        printf("��ǰ����Ϊ��!\n");
    } else {
        printf("��ǰ����Ϊ��!\n");
    }

    //�ж�������
    printf("��ǰ����ĳ��ȣ�%d\n", list_length(pHead));

	//�����½ڵ�
	insert_node(pHead, 1, 999);
	printf("------------------�²���ڵ��ı仯-----------------\n");
	printf("�²���Ľڵ���999��λ����1\n");
	traverse_list(pHead);
	printf("��ǰ����ĳ��ȣ�%d\n", list_length(pHead));

	//ɾ������ڵ�
	int hasDel = delete_node(pHead, 2);
	printf("------------------ɾ���ڵ��ı仯-----------------\n");
	printf("ɾ���Ľڵ���%d��λ����2\n", hasDel);
	traverse_list(pHead);
	printf("��ǰ����ĳ��ȣ�%d\n", list_length(pHead));

}

//��������
PNODE create_list()
{
    int i;int len;int val;
    PNODE pHead; //�����׵�ַ
    PNODE pNew;  //�����ӵĽڵ�
    PNODE pLast; //�������һ���ڵ�

    //�ȷ����ͷ
    pHead = (PNODE)malloc(sizeof(NODE));
    if (NULL == pHead) {
        printf("������ͷʧ�ܣ�\n");
        exit(-1);
    }

    //����һ���ڵ��ָ�����������������������һ���ڵ�
    pLast = pHead;
    pLast->pNext = NULL;

    printf("���������������");
    scanf("%d", &len);

    for(i=0;i<len;i++) {
        printf("�������%d��ֵ��", i+1);
        scanf("%d", &val);

        pNew = (PNODE)malloc(sizeof(NODE));
        if (NULL == pNew) {
            printf("��������ڴ�ʧ�ܣ�\n");
            exit(-1);
        }
        pNew->data = val;
        pLast->pNext = pNew;
        pNew->pNext = NULL;
        pLast = pNew;         //���½ڵ���Ϊ���һ���ڵ�
    }

    return pHead;
}

//��ӡ����
void traverse_list(PNODE pHead)
{
    PNODE p = pHead->pNext; //�׽ڵ㣨��һ����Ч�ڵ㣩
    while (p != NULL) {
        printf("%d\n",p->data);
        p = p->pNext;
    }
}

//�����Ƿ�Ϊ��
bool is_empty(PNODE pHead)
{
    return pHead->pNext == NULL;
}

//������
int list_length(PNODE pHead)
{
    int len = 0;
    PNODE p = pHead->pNext; //�׽ڵ㣨��һ����Ч�ڵ㣩
    while (p != NULL) {
        ++len;
        p = p->pNext;
    }
    return len;
}

//�����½ڵ�
bool insert_node(PNODE pHead, int pos, int val)
{
	int i = 0;
	PNODE p = pHead;
	while (i<pos-1 && p != NULL) {
		p = p->pNext;
		i++;
	}

	int len = list_length(pHead);
	if (pos<i || pos>len+1) {
        return false;
	}

	PNODE pNew = (PNODE)malloc(sizeof(NODE));
	if (NULL == pNew) {
		printf("�����ڴ�ʧ�ܣ�\n");
		exit(-1);
	}
	pNew->data = val;
	pNew->pNext = p->pNext;
	p->pNext = pNew;
}

//ɾ���ڵ�
int delete_node(PNODE pHead, int pos)
{
    int i = 0;
	PNODE p = pHead;
	while (i<pos-1 && p != NULL) {
		p = p->pNext;
		i++;
	}

	if (pos<i || pos>list_length(pHead)) {
        return 0;
	}

	PNODE nextNode = p->pNext;
	int val = nextNode->data;
	p->pNext = nextNode->pNext;
	free(nextNode);
	return val;
}
