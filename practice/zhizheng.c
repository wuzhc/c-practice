#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct island {
    char *name;
    struct island *next;
} island;


void display(island *island)
{
    for (; island != NULL; island = island->next) {
        printf("name: %s\n", island->name);
    }
}

island* create(char *name)
{
    island *i = malloc(sizeof(island));
    i->name = strdup(name); /* �ǵ�Ҫ�ͷ�strdup�ڶ��ϴ����Ŀռ� */
    i->next = NULL;
    return i;
}

void release(island *start)
{
    island *i = start;
    island *next = NULL;

    while (i != NULL) {
        next = i->next;
        free(i->name); /* �ͷ�strdup������name�ֶ� */
        free(i);
        i = next;
    }
}

int main()
{
    island *start = NULL;
    island *i = NULL;
    island *next = NULL;
    char name[80];

    for (; fgets(name, 80, stdin) != NULL; i = next) {
        next = create(name);
        if (start == NULL) {
            start = next;
        }
        if (i != NULL) {
            i->next = next;
        }
    }

    display(start);
    release(start);
}
