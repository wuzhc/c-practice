#include <sys/types.h>
#include <sys/msg.h>
#include "tlpi_hdr.h"

void usageError(const char *progName, const char *msg)
{
	if (msg != NULL) {
		fprintf(stderr, "%s\n", msg);
	}
}

int main(int argc, char *argv)
{

	exit(EXIT_SUCCESS);
}