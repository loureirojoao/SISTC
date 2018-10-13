#include <stdio.h>

void minha_divisao(int dividendo, int divisor, int *ptr_quociente, int *ptr_resto)
{
	*ptr_quociente = dividendo / divisor;
	*ptr_resto = dividendo % divisor;
}

int main()
{
	int a=1,b,c,r;

	while ( a != 0)
	{
		printf("Escolha um valor inteiro positivo: \n");
		scanf("%d",&a);
		printf("Escolha outro valor inteiro positivo: \n");
		scanf("%d",&b);
		
		minha_divisao(a,b,&c,&r);

		printf("Divisão inteira: %d\n",c);
		printf("Resto: %d\n",r);
	}	
}	