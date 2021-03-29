#include <stdio.h>
#include <stdlib.h>

int iresult = 0;
void print_exit(char *str);
void imod(int a, int b);
void idiv(int a, int b);
void imul(int a, int b);
void isub(int a, int b);
void iadd(int a, int b);


int main(void) {

	int a=0, b=0;
	char op = '\0';
	printf("Enter the expression: ");
	scanf("%d %c %d", &a, &op, &b);

	switch(op) {

		case '+': iadd(a, b);
			  break;
		case '-': isub(a, b);
			  break;
		case '*': imul(a,b);
			  break;

		case '/': idiv(a,b);
			break;
		case '%': imod(a,b);
		default:
			print_exit("Unrecognized operation");

	}

	printf("Result of the expression is: %d\n",iresult);

}

void iadd(int a, int b) {
	iresult = a + b;
}

void isub(int a, int b) {
	iresult = a - b;
}

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

void print_exit(char *str) 
{
	fprintf(stderr,"Error: %s\n",str);
	exit(1);
}