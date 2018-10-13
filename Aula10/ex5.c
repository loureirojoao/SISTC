char c; //contains received character
vehic_t v ;
char buffer2[256];
int nchars, state = 0 ;
switch(state) {
	case 0:
	case 2:
	case 4:
		if( c == '"' ) { //found opening "
			state++;
			nchars = 0;
			break;
		}
		if( c == '[' && state != 0 ) { //new record before completing current one
			printf("invalid record \n");
			state = 0;
			break;
		}
		break;
	case 1://reading plate
		if( c == '"' ) { //found closing "
			state = 2;
			break;
		}

		if( nchars == 6 ) //discard unexpected chars
			break;
		v.plate[nchars++] = c;
		break;
	case 3://reading owner
		if( c == '"' ) { //found closi ng "
			state = 4;
			v.owner[nchars] = 0;
			break;
		}
		if( nchars == VEHIC_MAXPLEN -1 ) //discard unexpected chars
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
		if( nchars == sizeof(buffer2) -1 ) //discard unexpected chars
			break;
		buffer2[nchars++] = c;
		break;
}
