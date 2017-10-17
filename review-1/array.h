typedef struct {
	int len;
	int num;
	int *head;
} A;

void init_array(A *a, int len); /* ��ʼ������ */
bool array_push(A *a, int value); /* ��Ԫ���Ƶ�����ĩβ�� */
bool is_full(A *a); /* �����Ƿ����� */
void traverse_array(A *a); /* �������� */
void inverse_array(A *a); /* ��ת���� */
int array_pop(A *a); /* ɾ�����һ��Ԫ�أ����ر�ɾ����Ԫ�� */
void array_insert(A *a, int index, int value); /* ����Ԫ�� */
