#include <unistd.h>
#include <stdio.h>

int main()
{
	pid_t x = fork();
	if (x)
	{
		wait(NULL);
		printf("parinte\n");
	}
	else
		printf("copil\n");
	return 0;
}