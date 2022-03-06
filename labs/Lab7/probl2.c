#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>

int count = 0;
pthread_mutex_t mtx;
sem_t sem;

void barrier_point()
{
	int i;
	pthread_mutex_lock(&mtx);

	count++;

	if (count == 5)
		for (i = 0; i < 5; i++)
			sem_post(&sem);
	
	pthread_mutex_unlock(&mtx);

	sem_wait(&sem);
}

void* thr (void* v)
{
	int tid = *(int*) v;
	printf("%d reached the barrier\n", tid);
	barrier_point();
	printf("%d passed the barrier\n", tid);

	return NULL;
}

int main()
{
	printf("NTHRS=%d\n", 5);

	if (pthread_mutex_init(&mtx, NULL))
	{
		perror(NULL);
		return errno;
	}

	if (sem_init(&sem, 0, 0))
	{
		perror(NULL);
		return errno;
	}

	int arg[5], i;
	pthread_t thrs[5];

	for (i = 0; i < 5; i++)
	{
		arg[i] = i;
		if (pthread_create(&thrs[i], NULL, thr, &arg[i]))
		{
			perror(NULL);
			return errno;
		}
	}

	for (i = 0; i < 5; i++)
	{
		if(pthread_join(thrs[i], NULL))
		{
			perror(NULL);
			return errno;
		}
	}

	pthread_mutex_destroy(&mtx);
	sem_destroy(&sem);
	
	return 0;
}