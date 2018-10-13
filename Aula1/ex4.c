#include <stdio.h>


void teste(char p1, char p2, char *p3)
{
	p2 = p2 + p1;
	*p3 = 3*p1;
}

int main()
{
	char a = 10;
	char b = 20;
	teste(10, a, &b);
	printf("%d, %d\n", a, b);

	// a = 10 -> É uma passagem por valor, 
	// ou seja não pode ser alterada em nenhuma função que não a main
}
