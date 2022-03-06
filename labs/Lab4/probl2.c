#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	pid_t pid = fork();
	int nr = atoi(argv[1]);

	if (pid)
	{
		wait(NULL);
		printf("Child %d finished\n", pid);
	}
	else
	{
		printf("%d: %d ", nr, nr);
		while(nr != 1)
		{
			if (nr % 2 == 0)
				nr = nr / 2;
			else
				nr = nr * 3 + 1;
			printf("%d ", nr);
		}
		printf("\n");
	}
	return 0;
}