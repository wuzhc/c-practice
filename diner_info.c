#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    int i;
    for (i=0; i<argc; i++) {
        printf("%s \n", argv[i]);
    }
    printf("环境变量：%s \n", getenv("name")); /* getenv读取环境变量 */
    return 0;
}
