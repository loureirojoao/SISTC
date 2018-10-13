char filename[1024];
  	strcpy(filename, "fileXXXXXX.bin");
  	int fd = mkstemps(filename, 4);
