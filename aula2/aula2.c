#include <stdio.h>
#include <stdlib.h>

/* alusão da função que implementa o algoritmo */
/* allusion to the function that implements the algorithm */
int CountElements (int [], int);
int Nop(int[],int);
/* variável global para contar as operações aritméticas executadas pelo algoritmo */
/* global variable for counting the arithmetic operations executed by the algorithm */
int Count = 0;

int main (void)
{
    /* declaração dos arrays de teste - usar o pretendido para cada execução */
    /* declaration of the test arrays - use each one for each execution */

    //int Array[] = { 10, 3, 15, 7, 9, 20, 11, 25, 27, 29 }; 
    //int Array[] = { 10, 3, 15, 7, 25, 33, 20, 55, 27, 29 }; 
    //int Array[] = { 10, 3, 15, 9, 25, 12, 20, 55, 27, 29 }; 
    //int Array[] = { 10, 3, 15, 9, 25, 12, 50, 55, 27, 29 }; 
    //int Array[] = { 10, 3, 15, 9, 25, 12, 50, 23, 27, 47 }; 
    // int Array[] = { 10, 3, 15, 9, 25, 12, 50, 24, 100, 47 };
    // int Array[] = { 10, 3, 15, 9, 25, 12, 50, 24, 100, 48 };
    // int Array[] = { 10, 3, 10, 9, 20, 12, 40, 24, 80, 48 };
    int Array[] = { 10, 3, 10, 3, 20, 6, 40, 12, 80, 24, 160 };
    //int Array[] = { 10, 3, 10, 3, 20, 6, 40, 12, 80, 24, 160,48,320};
 
    int NElem = sizeof (Array) / sizeof (int); int Result;

    /* invocação do algoritmo */
    /* algorithm invocation */  
	Result = CountElements (Array, NElem);

	/* apresentação do resultado e do número de operações aritméticas executadas pelo algoritmo */
	/* presenting the result and the number of arithmetic operations executed by the algorithm */
	fprintf (stdout, "Nº de elementos = %12u e custou %3d operacoes\n", Result, Count);

    exit (EXIT_SUCCESS);
}

/* implementação do algoritmo pretendido */
/* acrescentar a contagem das operações aritméticas executadas pelo algoritmo usando a variável global */

/* implementation of the pretended algorithm */
/* do not forget to count the arithmetic operations using the global variable */

int CountElements (int array[], int n)
{
    /* acrescentar o código do algoritmo */
    /* insert your code */
    int contagem=0;
    int somapares=0;
    int somaimpares=0;
    for(int i=0; i<n-2; i++){
        if (i%2==0){
            somapares+=array[i];
            Count++;
            if(somapares==array[i+2]){
                contagem++;
            }
        }
        else{
            somaimpares+=array[i];
            Count++;
            if(somaimpares==array[i+2]){
                contagem++;
            }
        }
    }
    return contagem;
}