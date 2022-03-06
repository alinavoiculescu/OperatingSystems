#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

#define MAX_RESOURCES 10

int available_resources = MAX_RESOURCES;
pthread_mutex_t mtx;

int decrease_count (int count)
{
	pthread_mutex_lock(&mtx);
	if (available_resources < count)
	{
		pthread_mutex_unlock(&mtx);
		return -1;
	}
	else
	{
		available_resources -= count;
		printf("Got %d resources %d remaining\n", count, available_resources);
	}

	pthread_mutex_unlock(&mtx);
	return 0;
}

int increase_count (int count)
{
	pthread_mutex_lock(&mtx);

	available_resources += count;
	printf("Released %d resources %d remaining\n", count, available_resources);

	pthread_mutex_unlock(&mtx);

	return 0;
}

void* thr(void* arg)
{
	int res = *(int*) arg;

	if (res > MAX_RESOURCES)
		return NULL;

	while (decrease_count(res));
	sleep(1);
	if (res == 0)
		increase_count(res);

	return NULL;

}

int main()
{
	int i;

	srand(time(0));
	printf("MAX_RESOURCES=%d\n", MAX_RESOURCES);

	if (pthread_mutex_init(&mtx, NULL))
	{
		perror(NULL);
		return errno;
	}

	pthread_t thrs[12];
	int arg[12];

	for (i = 0; i < 12; i++)
		arg[i] = rand() % MAX_RESOURCES + 1;

	for (i = 0; i < 12; i++)
	{
		if (pthread_create(&thrs[i], NULL, thr, &arg[i]))
		{
			perror(NULL);
			return errno;
		}
	}

	for (i = 0; i < 12; i++)
	{
		if(pthread_join(thrs[i], NULL))
		{
			perror(NULL);
			return errno;
		}
	}

	pthread_mutex_destroy(&mtx);
	return 0;
}
