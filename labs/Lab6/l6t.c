#include <stdio.h>
#include <pthread.h>

void * hello(void *v)
{
	char *who = (char*)v;
	printf("Hello, %s!\n", who);
	return NULL;
}

int main()
{
	pthread_t thr;
	pthread_create(&thr, NULL, hello, "world!");
	void * result;
	pthread_join(thr, &result);
	return 0;
}