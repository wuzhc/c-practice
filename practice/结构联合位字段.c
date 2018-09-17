#include <stdio.h>
#include <string.h>

// 枚举
typedef enum 
{
  PREPATE_TYPE, HOMEWORK_TYPE, SCANEXAM_TYPE
} sourceType;

// 联合
typedef union
{
  short count;
  short weight;
} quantity;

// 结构体
typedef struct 
{
  const char *subject;
  int score;
} report;

// 结构体
typedef struct 
{
  const char *name;
  const char *address;
  int age;
  report card; // 这是一个嵌套结构体
  sourceType type;
  quantity q;
} stu;

// 位字段
typedef struct 
{
  unsigned int fist_visit:1;
  unsigned int come_age:1;
  unsigned int fingers_lost:4;
  unsigned int days_a_week:3;
} survey;

// 结构体指针
void modifyAge(stu *s) 
{
  s->age = 23;
  // 等价于(*s).age = 23
}

int main(int argc, char const *argv[])
{
  stu person = {"wuzhc", "Guangzhou", 18, {"english", 59}, HOMEWORK_TYPE, {.weight=118}};

  if (person.type == HOMEWORK_TYPE) {
    printf("%s\n", "homework");
  } else {
    printf("%s\n", "other");
  }

  modifyAge(&person);
  printf("%i\n", person.age);

  printf("%i\n", person.q);
  return 0;
}