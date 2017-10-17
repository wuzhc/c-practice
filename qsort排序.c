#include <stdio.h>
#include <string.h>

void display(char** songs)
{
    int i;
    for (i = 0; i < 4; i++) {
        printf("%s \n", *(songs+i));
    }
}

int compare_name(const void* a, const void* b)
{
    char** sa = (char**)a;
    char** sb = (char**)b;
    return strcmp(*sa, *sb);
}

int main(int argc, char** argv)
{
    char *songs[] = {
        "my love",
        "as long as you love me",
        "no project",
        "in the world"
    };
    qsort(songs, 4, sizeof(char*), compare_name);
    display(songs);
}
