#include <stdio.h>

typedef struct {
    const char *name;
} package;

typedef struct {
    const char *name;
    int age;
    package pack; /* ���� */
} person;

typedef enum {
    RED, GREEN, PUCE
} colors;

void person_detail(person *p)
{
    printf("person_detail��\n");
    printf("���֣�%s, ���䣺%d��������%s \n", p->name, p->age, p->pack.name);
}

int main(int argc, char *argv[])
{
    person wuzhc = {"wuzhc", 27, {"book"}};
    printf("���֣�%s, ���䣺%d��������%s \n", wuzhc.name, wuzhc.age, wuzhc.pack.name);
    person_detail(&wuzhc);
    colors favorite = PUCE;
    if (favorite == PUCE) {
        printf("my favorite is puce");
    }
    return 0;
}

