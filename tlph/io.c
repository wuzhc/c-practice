#include <stdio.h>
#include <unistd.h>

int main() 
{
    printf("this is printf \n");
    write(STDOUT_FILENO, "this is writen \n", 16);
    return 0;
}
