#include <stdio.h>
#include <stdlib.h>

int Count;

double Potencia1(double, int);

double Potencia2(double, int);

int main(int argc, char const *argv[])
{
	unsigned int NPotencia,Test;

	double X, Result;
	
	do{
		printf ("Numero da Potencia? ");
		Test = scanf ("%d", &NPotencia);
		scanf ("%*[^\n]");
		scanf ("%*c");
	}while(Test==0);

	/*printf("%d \n", NPotencia);
	*/
	do{
		printf ("VAlor de X ");
		Test = scanf ("%lf", &X);
		scanf ("%*[^\n]");
		scanf ("%*c");
	}while(Test==0);
	for (int j = 1; j < NPotencia+1; j++)
	{ 
		for (int control = 0; control < 2; control++)
		{
			Count = 0;
			switch(control){
				case 0:Result = Potencia1(X,j);
				break;
				case 1:Result = Potencia2(X,j);
				break;			
			}

			fprintf (stdout, "A potencia de %10d de %10lf é : %16lf . \nForam executadas %10d multiplicações\n",j,X,  Result, Count);
			
			if(control==1){
				fprintf(stdout, "-------------------------------------------\n");
			}
		}
	}
	

	exit (EXIT_SUCCESS);

}

double Potencia1(double x , int n){
	if (n==0)
	{
		return 1;
	}
	else if (n==1)
	{
		return x;
	}
	else
	{
		Count++;
		return x*Potencia1(x, n-1);
	}
}

double Potencia2(double x, int n){

	if (n==0)
	{
		return 1;
	}
	else if (n==1)
	{
		return x;
	}
	else if (n%2==0)
	{
		Count++;
		return Potencia2(x*x,n/2);
	}
	else 
	{
		Count++;
		return (x*Potencia2(x*x,n/2));
	}
}