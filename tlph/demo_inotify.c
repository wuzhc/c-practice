#include <sys/inotify.h>
#include <limits.h>
#include "tlpi_hdr.h"
#define BUF_LEN  (10 * (sizeof(struct inotify_event) + NAME_MAX + 1))

void displaylInotifyEvent(struct inotify_event *i)
{
	printf("	wd=%2d;", i->wd);
	if (i->cookie > 0) {
		printf("cookie=%4d;", i->cookie);
	}

	printf("mask=");
	if (i->mask & IN_ACCESS) 
		printf("文件被访问");
	if (i->mask & IN_ATTRIB)
		printf("文件元数据改变");
	if (i->mask & IN_CLOSE_NOWRITE) 
		printf("关闭以只读方式打开的文件");
	if (i->mask & IN_CLOSE_WRITE)
		printf("关闭为了写入而打开的文件");
	if (i->mask & IN_CREATE) 
		printf("在受控目录内创建文件或目录");
	if (i->mask & IN_DELETE)
		printf("在受控目录内删除文件或目录");
	if (i->mask & IN_DELETE_SELF)
		printf("删除受控文件或目录本身");
	if (i->mask & IN_IGNORED)
		printf("监控项为内核或应用程序所删除");
	if (i->mask & IN_ISDIR)
		printf("name中所返回的文件名为路径");
	if (i->mask & IN_MODIFY)
		printf("文件被修改")
	if (i->mask & IN_MOVE_SELF)
		printf("移动受监控文件或目录本身");
	if (i->mask & IN_MOVED_FROM)
		printf("文件移出收监控目录之外");
	if (i->mask & IN_MOVED_TO)
		printf("文件移入受监控目录");
	if (i->mask & IN_OPEN)
		printf("文件被打开");
	if (i->mask & IN_Q_OVERFLOW)
		printf("事件队列溢出");
	if (i->mask & IN_UNMOUNT)
		printf("包含对象的文件系统遭卸载");
	printf("\n");

	if (i->len > 0) {
		printf("	name=%s\n", i->name);
	}
}

int main(int argc, char *argv[])
{
	int fd, wd, j;
	char buf[BUF_LEN];
	ssize_t numRead;
	char *p;
	struct inotify_event *event;

	if (argc < 2 || strcmp(argv[1], "--help") == 0) {
		usageErr("%s pathname ... \n", argv[0]);
	}

	fd = inotify_init();
	if (fd == -1) {
		errExit("inotify_init \n");
	}

	for (j=1;j<argc;j++) {
		wd = inotify_add_watch(fd, argv[j], IN_ALL_EVENTS);
		if (wd == -1) {
			errExit("inotify_add_watch \n");
		}

		printf("watching %s using wd %d\n", argv[1], wd);
	}

	/* read读取事件 */
	for (;;) {
		numRead = read(fd, buf, BUF_LEN);
		if (numRead == 0) {
			fatal("read() from inotify fd return 0\n");
		}
		if (numRead == -1) {
			errExit("read \n");
		}
		printf("read %ld bytes from inotify fd\n", (long)numRead);
		for (p = buf; p < buf + numRead;) {
			event = (struct inotify_event *)p;
			displaylInotifyEvent(event);
			p += sizeof(struct inotify_event) + event->len;
		}
	}

	return 0;
}