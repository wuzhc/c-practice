#include <stdio.h>
#include <string.h>
#include <errno.h>

void error_exit(char *);

int main(int argc, char *argv[])
{
	return 0;
}



void error_exit(char *msg)
{
	printf("%s : %s \n", msg, strerror(errno));
	exit(1);
}