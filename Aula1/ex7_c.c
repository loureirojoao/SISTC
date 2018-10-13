#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compara(char *s1, char *s2)
{
	while (*s1 == *s2){
		if (*s1==0){
			return 0;
		}
		else {
			s1++,s2++;
		}
	}
	return -1;
}

int main()
{
	char s1[100]; 
	char s2[100];
	int ret;

	printf("s1 = ");
	scanf("%s",s1);
	printf("s2 = ");
	scanf("%s",s2);

	ret = compara(s1,s2);

	if (ret == 0){
		printf ("str1 igual a str2\n");
	}
	else{
		printf("str1 diferente de str2\n"); 
	}
}
