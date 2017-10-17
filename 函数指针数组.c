#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
    ONE, TWO, THREE
} reponse_type;

typedef struct {
    char* name;
    reponse_type type;
} response;

size_t compute_len(response* r)
{
    size_t len = 0;
    while (r->name != NULL) {
        r++;
        len++;
    }
    return len;
}

void display_one(char* name)
{
    puts("display one:");
    printf("%s\n", name);
}

void display_two(char* name)
{
    puts("display two:");
    printf("%s\n", name);
}

void display_three(char* name)
{
    puts("display three:");
    printf("%s\n", name);
}

void (*display[])(char*) = {display_one, display_two, display_three};

int main(int argc, char** argv)
{
    int i = 0;
    size_t len = 0;
    response r[] = {
        {"Mike", ONE},
        {"Matt", TWO},
        {"Wuzhc", THREE}
    };

    len = compute_len(r); /* ÔªËØ¸öÊý */

    for (; i < len; i++) {
        (display[i])(r[i].name);
    }

    return 0;
}
