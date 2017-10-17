/* 递归结构体必须定义结构体名，不能用别名 */
typedef struct Node
{
	int data; /* 指针域 */
	struct Node *next; /* 指向下一个节点的指针 */
}NODE, *PNODE;

PNODE init_chain(); /* 初始化链表 */
void traverse_chain(PNODE pnode); /* 遍历链表 */
bool chain_push(PNODE pnode, int value); /* 增加链表节点 */
bool remove_node(PNODE pnode, int index); /* 删除节点 */
bool add_node(PNODE pnode, int pos, int index); /* 增加节点 */
bool is_empty(PNODE pnode);
int chain_length(PNODE pnode);

