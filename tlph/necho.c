#include "tlpi_hdr.h"

int main(int argc, char **argv)
{
	int i;
	char **p;
	for (i = 0;i < argc; i++) {
		printf("argv[%d] = %s\n", i, argv[i]);
	}

	printf("或者这么做\n");

	for (p = argv; *p != NULL; p++) {
		puts(*p);
	}

	exit(EXIT_SUCCESS);
	return 0;
}
