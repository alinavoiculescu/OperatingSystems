#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[])
{

	int i, nr, shm_fd, j, k;
	char *shm_ptr;

	char shm_name[] = "myshm";

	printf("Starting parent %d\n", getpid());

	shm_fd = shm_open(shm_name, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);

	if(shm_fd < 0)
	{
		perror(NULL);
		return errno;
	}

	size_t buffer = 1000;
	size_t shm_size = buffer * (argc - 1);

	if (ftruncate(shm_fd, shm_size) == -1)
	{
		perror(NULL);
		shm_unlink(shm_name);
		return errno;
	}
	shm_ptr = mmap(0, shm_size, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (shm_ptr == MAP_FAILED)
	{
		perror(NULL);
		shm_unlink(shm_name);
		return errno;
	}

	for (i = 1; i < argc; i++)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			shm_ptr = mmap(0, buffer, PROT_WRITE, MAP_SHARED, shm_fd, buffer * (i - 1));
			if (shm_ptr == MAP_FAILED)
			{
				perror(NULL);
				shm_unlink(shm_name);
				return errno;
			}

			nr = atoi(argv[i]);
			j = 0;

			while(nr != 1)
			{
				j += 1;
				shm_ptr[j] = nr;
				if (nr % 2 == 0)
					nr = nr / 2;
				else
					nr = nr * 3 + 1;
			}
			j++;
			shm_ptr[j] = 1;
			shm_ptr[0] = j;

			printf("Done Parent %d Me %d\n", getppid(), getpid());
			return 0;
		}
		///munmap(shm_ptr, buffer);
	}

	for (i = 1; i < argc; i++)
	{
		wait(NULL);
	}

	for (i = 1; i < argc; i++)
	{
		shm_ptr = mmap(0, buffer, PROT_READ, MAP_SHARED, shm_fd, buffer * (i - 1));
		j = shm_ptr[0];
		printf("%d: %d ", shm_ptr[1], shm_ptr[1]);
		for(k = 2; k <= j; k++)
			printf("%d ", shm_ptr[k]);
		printf("\n");
	}

	printf("Done Parent %d Me %d\n", getppid(), getpid());

    munmap(shm_ptr, shm_size);
	shm_unlink(shm_name);
	close(shm_fd);

	return 0;
}
