#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int A[100][100], B[100][100], C[100][100];
int rowsA, rowsB, rowsC, colsA, colsB, colsC;

void * multiply(void *v)
{
	int i;
	int *M = (int*) v;
	int *sum = malloc(sizeof(int));
	*sum = 0;

	for (i = 0 ; i < rowsB; i++)
		*sum += A[M[0]][i] * B[i][M[1]];

	return sum;
}

int main(int argc, char *argv[])
{
	int i,j;
	
	printf("A:\n");
	scanf("%d %d", &rowsA, &colsA);
	
	rowsC = rowsA;

	for(i = 0; i < rowsA; i++)
		for(j = 0; j < colsA; j++)
			scanf("%d", &A[i][j]);

	printf("\n");

	printf("B:\n");
	scanf("%d %d", &rowsB, &colsB);

	colsC = colsB;

	for(i = 0; i < rowsB; i++)
		for(j = 0; j < colsB; j++)
			scanf("%d", &B[i][j]);

	pthread_t thr[rowsC*colsC];
	int idx = 0;

	for (i = 0; i < rowsC; i++)
		for(j = 0; j < colsC; j++)
		{
			int * M = malloc(sizeof(int) * 2);
			M[0] = i;
			M[1] = j;
		
			if (pthread_create(&thr[idx++], NULL, multiply, M))
			{
				perror(NULL);
				return errno;
			}
		}

	idx = 0;
	for (i = 0; i < rowsC; i++)
		for(j = 0; j < colsC; j++)
		{
			int * result;
			if (pthread_join(thr[idx++], (void*)&result))
			{
				perror(NULL);
				return errno;
			}
			C[i][j] = *result;
		}

	printf("\n");

	printf("C:\n");
	for (i = 0; i < rowsC; i++)
	{
		for(j = 0; j < colsC; j++)
			printf("%d ", C[i][j]);
		printf("\n");
	}	

	return 0;
}