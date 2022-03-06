#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
	//argv[1] - numele primului fisier
	//argv[2] - numele celui de-al doilea fisier

	int n;
	char buf[2];
	int fisier1 = open(argv[1], O_RDONLY);
	int fisier2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 00777);

	if (fisier1 == -1)
	{
		perror("error while opening fisier1");
		return 0;
	}

	if (fisier2 == -1)
	{
		perror("error while writing in fisier2");
		return 0;
	}

	do
	{
		n = read(fisier1, buf, 1);
		//printf("%d\n", n);
		write(fisier2, buf, n);
	} while (n != 0);

	close(fisier1);
	close(fisier2);

/*
	int i;
	for (i = 0; i < argc; i++)
		printf("%s\n", argv[i]);
*/

	return 0;
}
