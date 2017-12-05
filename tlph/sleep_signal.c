#include <signal.h>
#include "tlpi_hdr.h"

void handler(int sig)
{
	printf("catch signal %d\n", sig);
}

int main(int argc, char const *argv[])
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	if (sigaction(SIGINT, &sa, NULL) == -1) {
		errExit("sigaction \n");
	}

	printf("begin sleep 10 specs .....\n");
	sleep(10);
	printf("after sleep\n");

	return 0;
}