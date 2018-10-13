#include <stdio.h>
#include <string.h>


int main()
{
	char s1[100]; 
	char s2[100];
	int ret;
	int n;

	printf("s1 = ");
	scanf("%s",s1);
	printf("s2 = ");
	scanf("%s",s2);

	printf("Numero de bytes a comparar: ");
	scanf("%d",&n);

	ret = memcmp(s1,s2,n);

	if (ret == 0){
		printf ("str1 igual a str2\n");
	}
	else{
		printf("str1 diferente de str2\n"); 
	}
}