#include <stdio.h>
#include <stdlib.h>

/* alus�o da fun��o que implementa o algoritmo pretendido */
/* allusion to the function that implements the algorithm */
int VerifyDifferences (int [], int);

/* vari�vel global para contar as opera��es aritm�ticas executadas pelo algoritmo */
/* global variable for counting the arithmetic operations executed by the algorithm */
int Count = 0;

int main (void)
{
    /* declara��o dos arrays de teste - usar o pretendido para cada execu��o */
    /* declaration of the test arrays - use each one for each execution */

     //int Array[] = { 1, 3, 5, 7, 9, 11, 20, 25, 27, 29 }; 
    int Array[] = { 1, 3, 6, 9, 11, 13, 20, 25, 27, 29 };
    // int Array[] = { 1, 3, 6, 10, 11, 13, 20, 25, 27, 29 }; 
    // int Array[] = { 1, 3, 6, 10, 15, 17, 20, 25, 27, 29 }; 
    // int Array[] = { 1, 3, 6, 10, 15, 21, 22, 25, 27, 29 }; 
    // int Array[] = { 1, 3, 6, 10, 15, 21, 28, 30, 37, 39 }; 
    // int Array[] = { 1, 3, 6, 10, 15, 21, 28, 36, 39, 49 }; 
    // int Array[] = { 1, 3, 6, 10, 15, 21, 28, 36, 45, 49 }; 
    // int Array[] = { 1, 3, 6, 10, 15, 21, 28, 36, 45, 55 }; 
  
    int NElem = sizeof (Array) / sizeof (int); int Result;

    /* invoca��o do algoritmo pretendido */
    /* algorithm invocation */    
	Result = VerifyDifferences (Array, NElem);

	/* apresenta��o do resultado e do n�mero de opera��es aritm�ticas executadas pelo algoritmo */
	/* presenting the result and the number of arithmetic operations executed by the algorithm */
	if (Result) fprintf (stdout, "Verifica ");
	else fprintf (stdout, "Nao verifica ");

	fprintf (stdout, "e executou %10d operacoes aritmeticas\n", Count);

    exit (EXIT_SUCCESS);
}

/* implementa��o do algoritmo pretendido */
/* acrescentar a contagem das opera��es aritm�ticas executadas pelo algoritmo usando a vari�vel global */

/* implementation of the pretended algorithm */
/* do not forget to count the arithmetic operations using the global variable */

int VerifyDifferences (int array[], int n)
{
    /* acrescentar o c�digo do algoritmo */
    /* insert your code */
    
    if(n<3)return 0;

    int i,dif =array[1]-array[0];    
    
    Count++;

    for(i=2;i<n;i++){
        Count+=2;
        if((array[i]-array[i-1])!=++dif)
            return 0;
    }
    return 1;
}






