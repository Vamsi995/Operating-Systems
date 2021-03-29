#include "error_handler.h"


void print_exit(char *str) 
{
	fprintf(stderr,"Error: %s\n",str);
	exit(1);
}