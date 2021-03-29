#include "error_handler.h"
#include "calc.h"


void imul(int a, int b) {
	iresult = a * b;
}

void idiv(int a, int b) {

	if(b == 0){
		print_exit("Division by zero");
	}
	iresult = a/b;
}

void imod(int a, int b)
{

	if(b == 0) 
	{
		print_exit("Division by zero");
	}

	iresult = a%b;
}



