#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char** argv)
{

//Problema 1
	write(1, "Hello, World!\n", 15);















/*
	printf("%d\n", argc);
	int i, a;
	struct stat x;
	a = stat(argv[1], &x);
	if(a)
	{
		printf("Eroare\n");
	}
	else
	{
		printf("Codul este %d. Fisierul %s va spune <<Hello, World!>>.\n", a, argv[1]);
	}
*/



/*
	printf("%d\n", argc);
	int i, a;
	struct stat x;
	a = stat(argv[1], &x);
	if(a)
	{
		printf("Eroare\n");
	}
	else
	{
		printf("Codul este %d. Fisierul %s ocupa %d bytes.\n", a, argv[1], x.st_size);
	}
*/

/*
	//argv[1] - numele fisierului
	for (i = 0; i < argc; i++)
		printf("%s\n", argv[i]);
*/
	return 0;
}
