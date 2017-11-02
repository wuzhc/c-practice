#include <stdio.h>

typedef struct {
    const char *name;
} package;

typedef struct {
    const char *name;
    int age;
    package pack; /* 包裹 */
} person;

typedef enum {
    RED, GREEN, PUCE
} colors;

void person_detail(person *p)
{
    printf("person_detail：\n");
    printf("名字：%s, 年龄：%d，包裹：%s \n", p->name, p->age, p->pack.name);
}

int main(int argc, char *argv[])
{
    person wuzhc = {"wuzhc", 27, {"book"}};
    printf("名字：%s, 年龄：%d，包裹：%s \n", wuzhc.name, wuzhc.age, wuzhc.pack.name);
    person_detail(&wuzhc);
    colors favorite = PUCE;
    if (favorite == PUCE) {
        printf("my favorite is puce");
    }
    return 0;
}

