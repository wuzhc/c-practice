#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	pid_t pid = getpid();
	pid_t ppid = getppid();
	printf("farther %d\n", ppid);
	printf("child %d\n", pid);
	return 0;
}