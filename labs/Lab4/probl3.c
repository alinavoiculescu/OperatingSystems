#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	printf("Starting parent %d\n", getpid());
	int i, nr;
	for (i = 1; i <= argc; i++)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			nr = atoi(argv[i]);
			printf("%d: %d ", nr, nr);
			while(nr != 1)
			{
				if (nr % 2 == 0)
					nr = nr / 2;
				else
					nr = nr * 3 + 1;
				printf("%d ", nr);
			}
			printf(".\nDone Parent %d Me %d\n", getppid(), getpid());
			return 0;
		}
	}

	for (i = 1; i <= argc; i++)
	{
		wait(NULL);
	}
	printf("Done Parent %d Me %d\n", getppid(), getpid());

	return 0;
}