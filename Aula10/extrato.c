ISEP – LEEC - Sistemas Computacionais 2017/2018
Listagens da ficha "Serviços web"


POST /~sistc/subdiretorio_do_aluno/vehicle.php HTTP/1.1
Host: localhost
Content-Type: application/x-www-form-urlencoded
Content-Length: 44   
<linha em branco>
plate=11AA22&owner=John Jones&value=10000.00




//assume que a resposta do servidor está armazenada na variável char buffer[]
char *ptr,*ptr2;
//procura a tag <ws-error>
if( (ptr = strstr(buffer, "<ws-error>"))!=NULL)
{
	//ptr fica a apontar para o primeiro carácter da mensagem de erro
	ptr = strstr(ptr,">") + 1;

	//função strsep substitui o ‘<’ de “</ws-error>” pelo fim de string
	ptr2 = ptr;
	ptr = strsep(&ptr2, "<");

	printf("Error message from server: \"%s\"\n\n", ptr);
}






char c; //contains received character
vehic_t v;
char buffer2[256];  
int nchars, state = 0;

switch(state) {
	case 0:
	case 2:
	case 4:            
		if( c == '"' ) { //found opening "
			state++;
			nchars = 0;
			break;
		}

		if( c == '['  && state != 0 ) { //new record before completing current one
			printf("invalid record\n");
			state = 0;
			break;
		}

		break;

	case 1://reading plate
		if( c == '"' ) {  //found closing "
			state = 2;
			break;
		}

		if( nchars == 6 ) //discard unexpected chars
			break;

		v.plate[nchars++] = c;      
		break;

	case 3://reading owner
		if( c == '"' ) { //found closing "
			state = 4;
			v.owner[nchars] = 0;
			break;
		}

		if( nchars == VEHIC_MAXPLEN-1 ) //discard unexpected chars
			break;

		v.owner[nchars++] = c;                
		break;

	case 5://reading value 
		if( c == '"' ) { //found closing "
			state = 0;

			buffer2[nchars] = 0;
			v.value = atof(buffer2);
			vehic_print(&v);
			break;
		}

		if( nchars == sizeof(buffer2)-1 ) //discard unexpected chars
			break;

		buffer2[nchars++] = c;                
		break;
}

