#include <stdio.h>
#include <stdlib.h>

void minha_divisao(int dividendo, int divisor, int *ptr_quociente, int *ptr_resto)
{
	*ptr_quociente = dividendo / divisor;
	*ptr_resto = dividendo % divisor;
}

int main(int argc, char *argv[])
{

	int a = 1;
	int b;
	int c,r;

	if (argc == 3)
	{
		 a = atoi(argv[1]);
		 b = atoi(argv[2]);

		if (b == 0) 
		{
			printf("Impossivel dividir por zero\n");
			return 0;
		}

		minha_divisao(a,b,&c,&r);
		
		printf("Divisão inteira: %d\n",c);
		printf("Resto: %d\n",r);	
	}
	
	else if (argc == 1)
	
	{
		while ( a != 0)
		{
			printf("Escolha um valor inteiro positivo: \n");
			scanf("%d",&a);
			do {
				printf("Escolha outro valor inteiro positivo: \n");
				scanf("%d",&b);
				}
			while (b==0);
			minha_divisao(a,b,&c,&r);
			
			printf("Divisão inteira: %d\n",c);
			printf("Resto: %d\n",r);
		}
	}	
}	
	