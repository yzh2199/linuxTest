#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
static void child()
{
	char *args[] = {"/bin/echo", "hello", NULL};
	printf("I'm child! my pid is %d.\n", getpid());
	fflush(stdout);
	execve("/bin/echo", args, NULL);
	err(EXIT_FAILURE, "exec() failed");
}
static void parent(pid_t pid_c)
{
	printf("I'm parent! my pid is %d and the pid of my child is %d.\n", getpid(), pid_c);
	exit(EXIT_SUCCESS);
}
int main(void)
{
	pid_t ret;
	ret = fork();
	if (ret == -1)
		err(EXIT_FAILURE, "fork() failed");
	if (ret == 0) {
		//fork()会返回0给子进程，因此这里调用child()
		child();
	} else {
		//fork()会返回新创建的子进程的进程ID（大于1）给父进程，因此这里调用parent()
		parent(ret);
	}
	// 在正常运行时，不可能运行到这里
	err(EXIT_FAILURE, "shoudln't reach here");
}