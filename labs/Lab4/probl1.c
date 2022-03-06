#include <unistd.h>
#include <stdio.h>

int main()
{
	pid_t x = fork();
	if (x)
	{
		printf("My PID=%d, Child PID=%d\n", getpid(), x);
		wait(NULL);
		printf("Child %d finished\n", x);
	}
	else
	{	
		char *argv[] = {"ls", NULL};
		execve("/bin/ls", argv, NULL);
		perror(NULL);
	}
	return 0;
}