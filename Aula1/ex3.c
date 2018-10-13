#include <stdio.h>

int main()
{
	char a = 46;
	char *ptr;
	ptr = &a;
	*ptr = 47; // O mesmo do que dar o valor 47 à variável a 
	a = 48;

	//*ptr vai buscar o valor colocado em a
	printf("%d, %d\n", *ptr, a);
	a = '0';
	printf("%d, %c, %x\n", a, a, a);

	return 0;

}
