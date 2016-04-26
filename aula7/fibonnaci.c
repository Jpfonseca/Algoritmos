#include <stdio.h>
#include <stdlib.h>

int Count;

int Fibonnacirec(int);

int main(int argc, char const *argv[])
{
	unsigned int X,Test;

	int Result;
	
	do{
		printf ("Numero da Potencia? ");
		Test = scanf ("%d", &X);
		scanf ("%*[^\n]");
		scanf ("%*c");
	}while(Test==0);

	/*printf("%d \n", NPotencia);
	*/
	Count=0;
	Result=Fibonnacirec(X);

	fprintf (stdout, "A Sequencia de Fibonnaci de %10d  é : %10d. \nForam executadas %10d adicoes\n",X, Result, Count);

	exit (EXIT_SUCCESS);

}

int Fibonnacirec(int n){
	if (n==0)
	{
		return 0;
	}
	else if (n==1)
	{
		return 1;
	}
	else if (n>=2)
	{
		Count++;
		return Fibonnacirec(n-1)+Fibonnacirec(n-2);
	}
	
}