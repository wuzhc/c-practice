/* �ݹ�ṹ����붨��ṹ�����������ñ��� */
typedef struct Node
{
	int data; /* ָ���� */
	struct Node *next; /* ָ����һ���ڵ��ָ�� */
}NODE, *PNODE;

PNODE init_chain(); /* ��ʼ������ */
void traverse_chain(PNODE pnode); /* �������� */
bool chain_push(PNODE pnode, int value); /* ��������ڵ� */
bool remove_node(PNODE pnode, int index); /* ɾ���ڵ� */
bool add_node(PNODE pnode, int pos, int index); /* ���ӽڵ� */
bool is_empty(PNODE pnode);
int chain_length(PNODE pnode);

