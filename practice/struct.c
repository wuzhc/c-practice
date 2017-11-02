#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} *PNODE, NODE;

int main()
{
    NODE node;
    node.data = 11;
    printf("%p\n", &node);
    printf("%i\n", node.data);
    return 0;
}


