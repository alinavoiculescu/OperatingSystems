#include <unistd.h>
#include <stdio.h>

int main()
{
	printf("Apel\n");
	syscall(4, 1, "Hello!", 6);
	syscall(331, "foo");
	printf("\nFinal\n");
	return 0;
}
