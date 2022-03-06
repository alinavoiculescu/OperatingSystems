#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

void * reverseString(void *v)
{
	char *str = (char*)v;
	int length, i;
	length = strlen(str);
	char *revStr = malloc(sizeof(char) * (length + 1));

	for (i = 0; i < length; i++)
		revStr[i] = str[length - i - 1];

	revStr[length] = '\0';

	return revStr;
}

int main(int argc, char *argv[])
{
	char *str = argv[1];

	pthread_t thr;
	if (pthread_create(&thr, NULL, reverseString, str))
	{
		perror(NULL);
		return errno;
	}

	char *result;
	if (pthread_join(thr, (void*)&result))
	{
		perror(NULL);
		return errno;
	}

	printf("%s\n", result);
	return 0;
}
