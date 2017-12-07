#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include "tlpi_hdr.h"

#define KEY_FILE "/some-path/some-file"

int main(int argc, char *argv[])
{
	key_t key;
	int msgid;
	const int MQ_PERMS = S_IRUSR | S_IWUSR | S_IRGRP;

	key = ftok(KEY_FILE, 1);
	if (key == -1) {
		errExit("ftok failed \n");
	}

	/* 删除旧的IPC对象 */
	while ((msgid = msgget(key, IPC_CREAT | IPC_EXCL | MQ_PERMS)) == -1) {
		if (errno == EEXIST) { /* 已经存在 */
			msgid = msgget(key, 0);
			if (msgid == -1) {
				errExit("msgget() failed to retrieve old queue ID");
			}
			if (msgctl(msgid, IPC_RMID, NULL) == -1) { /* 删除IPC对象 */
				errExit("msgget() failed to delete old queue");
			}
			printf("removed old message queue (id=%d)\n", msgid); 
		} else {
			errExit("msgget failed");
		}
	}
	return 0;
}