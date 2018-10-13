#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char str1[] = "Teste!";
	int data1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	char str2[1000];
	int data2[1000];
	int i;

	printf("sizeof str1 = %ld\n", sizeof(str1));
	printf("sizeof data1 = %ld\n\n", sizeof(data1));

	printf("str1 = %s\n",str1);

	printf("data1 = ");
	for (i=0; i<10; i++)
	printf("%d ",data1[i]);

	printf("\n\n");

	strcpy(str2, str1);
	memcpy(data2, data1, sizeof(data1));

	printf("str2 = %s\n",str2);
	
	printf("data2 = ");
	for (i=0; i<10; i++)
	printf("%d ",data2[i]);

	printf("\n");

	printf("sizeof str2 = %ld\n", sizeof(str2));
	printf("sizeof data2 = %ld\n", sizeof(data2));

}