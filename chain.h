#include <stdio.h>
#ifndef CHAIN_H_INCLUDED
#define CHAIN_H_INCLUDED

typedef int ElementType;

struct Node;
struct Node
{
    ElementType Element;
    struct Node * Next;
};

typedef struct Node * ptrToNode;
typedef ptrToNode List;
typedef ptrToNode Position;
int isEmpty(List L);
int isLast(Position P);
void insert(ElementType X, Position P);
Position find(ElementType, List L);
Position findPrevious(ElementType X, List L);
void print();



#endif // CHAIN_H_INCLUDED
