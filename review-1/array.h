typedef struct {
	int len;
	int num;
	int *head;
} A;

void init_array(A *a, int len); /* 初始化数组 */
bool array_push(A *a, int value); /* 将元素推到数组末尾， */
bool is_full(A *a); /* 数组是否已满 */
void traverse_array(A *a); /* 遍历数组 */
void inverse_array(A *a); /* 翻转数组 */
int array_pop(A *a); /* 删除最后一个元素，返回被删除的元素 */
void array_insert(A *a, int index, int value); /* 插入元素 */
