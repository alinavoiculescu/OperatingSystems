#include <unistd.h>
#include <stdio.h>

int main()
{
	pid_t x = Fork();
	if (x == 0)
	{
		printf("%d %d pp1\n", getpid(), getppid());
		char *argv[] = {"pwd", NULL};
		execve("/bin/pwd", argv, NULL);
		perror(NULL);
		printf("pp2\n");
	}
	else
	{
		wait(NULL);
		printf("%d %d parinte\n", getpid(), getppid());
	}

	return 0;
}
