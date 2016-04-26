/*******************************************************************************

 Ficheiro de implementação do Tipo de Dados Abstrato POLiNOMiO (polynomial.c).
 A estrutura de dados de suporte do polinómio é uma estrutura, constituída pelo
 campo de tipo inteiro Degree para armazenar o grau do polinómio e o campo de
 tipo ponteiro Poly, para representar a sequência atribuída dinamicamente, que
 vai armazenar os seus coeficientes reais.
 
 Nome :                                                     NMec:

 implementation FILE of the abstract data type Poly (polynomial.c). The data
 structure to store the polynomial is composed with the integer field Degree for
 keeping the polynomial's degree and the pointer field Poly, that represents the
 allocated array in dynamic memory, for storing the polynomial's real coefficients.

*******************************************************************************/

#include <stdio.h>  
#include <stdlib.h>
#include <math.h>

#include "polynomial.h"    /* Ficheiro de interface do TDA - ADT interface FILE */

/************ Definição da Estrutura de Dados interna do POLiNOMiO ************/

struct poly
{
  unsigned int Degree;  /* grau do polinómio - polynomial degree */
  double *Poly;      /* ponteiro para os coeficientes do polinómio - pointer to polynomial's coefficients */
};

/*********************** Controlo Centralizado de Erro ************************/

static unsigned int Error = OK;  /* inicialização do erro */

static char *ErrorMessages[] = {
                                 "sem erro - Without Error",
                                 "polinomio(s) inexistente(s) - Polynomial(s) do not exist",
                                 "memoria esgotada - Out of memory",
                                 "ficheiro inexistente - FILE does not exist",
                                 "grau do polinomio errado - Wrong degree",
                                 "coeficiente inexistente no polinomio - Coefficient does not exist"
                               };

static char *AbnormalErrorMessage = "erro desconhecido - Unknown error";

/************** Número de mensagens de erro previstas no módulo ***************/

#define N (sizeof (ErrorMessages) / sizeof (char *))

/************************ Alusão às Funções Auxiliares ************************/

static int ValidPolys (PtPoly, PtPoly);
static void ReducePoly (PtPoly);

/*************************** Definição das Funções ****************************/

void PolyClearError (void)
{
  Error = OK;
}

int PolyError (void)
{
  return Error;
}

char *PolyErrorMessage (void)
{
  if (Error < N) return ErrorMessages[Error];
  else return AbnormalErrorMessage;    /* não há mensagem de erro - no error message */
}

PtPoly PolyCreate (unsigned int pdegree)
{
  
  PtPoly p;

  /* valida o grau do polinómio - degree validation */
  if (pdegree < 0) { Error = BAD_DEGREE; return NULL; }

  /* cria o poly nulo - allocating the supporting record (struct) and its supporting array */
  if ((p = (PtPoly) malloc (sizeof (struct poly))) == NULL)
  { 
    Error = NO_MEM; return NULL; 
  }
 
  p->Poly = (double *) calloc (pdegree+1, sizeof (double));
 
  if (p->Poly == NULL)
  { 
    free (p); 
    Error = NO_MEM; 
    return NULL; 
  }

  p->Degree = pdegree;     /* armazenamento da dimensão - storing the size */

  Error = OK;

  return p;
}

void PolyDestroy (PtPoly *ppoly)
{

  PtPoly TmpPoly= *ppoly;

  /* verifica se o poly existe - verifies if poly exists */
  if (TmpPoly == NULL) { 

    Error = NO_POLY; return ; 
  }

  /* libertação da memória dinâmica - free dynamic memory */

  free(TmpPoly->Poly);
  free (TmpPoly);    /* liberta a memória ocupada pelo poly - free the supporting record */

  Error = OK;
  *ppoly=NULL;
}

PtPoly PolyCopy (PtPoly ppoly)
{
  PtPoly Copy; int i;

  /* verifica se o poly existe - verifies if  exists */
  if (ppoly == NULL) { 
    Error = NO_POLY; return NULL; 
  }

  /* criação do poly copia nulo - creating an empty poly */
  if ((Copy = PolyCreate (ppoly->Degree)) == NULL){
    Error=NO_MEM;
    return NULL;
  } 


  /* fazer a copia do poly - copying the components */
  for (i = 0; i <(ppoly->Degree)+1; i++) Copy->Poly[i] = ppoly->Poly[i];

  Error=OK;
  ReducePoly(ppoly);
  return Copy;  /* devolve o poly copia - returning the new poly */
}

int PolyDegree (PtPoly ppoly)
{
 if (ppoly == NULL) { 
    Error = NO_POLY; 
    return 0; 
  }

  Error = OK;
  return ppoly->Degree;
}

void PolyModifyCoefficient (PtPoly ppoly, unsigned int ppos, double pvalue)
{
  /* verifica se o poly existe - verifies if poly exists */
  if (ppoly == NULL) {
    Error = NO_POLY; return; 
  }

  /* validação do elemento pretendido - validationng the element position */
  if ((ppos > (ppoly->Degree))) { 
    Error = BAD_INDEX; 
    return; 
  }

  Error = OK;
  /* escrita do valor na componente pretend ida do poly - storing the new value in the component */
  ppoly->Poly[ppos] = pvalue;
}

double PolyObserveCoefficient (PtPoly ppoly, unsigned int ppos)
{
  /* verifica se o poly existe - verifies if poly exists */
  if (ppoly == NULL) { 
    Error = NO_POLY; 
    return 0; 
  }

  /* validação do elemento pretendido - validating the element position */
  if ((ppos > (ppoly->Degree))) { 
    Error = BAD_INDEX; 
    return 0; 
  }

  Error = OK;
  /* devolve o valor armazenado na componente pretendida do poly - returning the component value */
  return ppoly->Poly[ppos];
}

int PolyisNull (PtPoly ppoly)
{
  int i;

  /* verifica se o polinomio existe - verifies if polinomio exists */
  if (ppoly == NULL) { 
    Error = NO_POLY; 
    return 0; 
  }
  Error = OK;

  /* verificação dos coeficientes do polinomio - verifying the polinomio's components */
  for (i = 0; i <(ppoly->Degree)+1; i++)
    if (ppoly->Poly[i]) return 0;

  return 1;  /* o polinomio é nulo*/

}

PtPoly PolySymmetrical (PtPoly ppoly)
{
  PtPoly Symmetrical;
  int i;

  /*verifica se o polinomio existe*/
  if (ppoly==NULL){
    Error= NO_POLY;
    return NULL;
  }

  if ((Symmetrical = PolyCreate (ppoly->Degree)) == NULL) { 
    Error = NO_MEM; 
    return NULL; 
  }
  for (i = 0; i <(ppoly->Degree)+1; i++){
    Symmetrical->Poly[i] = 0-(ppoly->Poly[i]);
  }
     
  ReducePoly(Symmetrical);

  return Symmetrical;
}

PtPoly PolyAddition (PtPoly ppoly1, PtPoly ppoly2)
{
   PtPoly Add;
    int i;

  /* Validação dos polinómios */
  if(!ValidPolys(ppoly1,ppoly2)){Error= NO_POLY; return NULL;}

   /* soma dos dois polinómios, verificar qual o maior polinómio */
  if (ppoly1->Degree >= ppoly2->Degree)
  {
    if ((Add = PolyCreate (ppoly1->Degree)) == NULL) { 
      Error = NO_MEM; 
      return NULL;
    }
  
    for (i = 0; i < (ppoly1->Degree)+1; i++){
            Add->Poly[i] = ppoly1->Poly[i] + ppoly2->Poly[i];
    }
  }
  
  else
  {
    if ((Add = PolyCreate (ppoly2->Degree)) == NULL) {
      Error = NO_MEM; 
      return NULL; 
    }
  
    for (i = 0; i <= (ppoly2->Degree)+1; i++){
      Add->Poly[i] = ppoly2->Poly[i] + ppoly1->Poly[i];
    }
  }

  Error=OK;

  ReducePoly(Add);
  return Add;
}

PtPoly PolySubtraction (PtPoly ppoly1, PtPoly ppoly2)
{
  PtPoly Sub; int i;

  /* Validação dos polinómios , */
  if(!ValidPolys(ppoly1,ppoly2)) {Error= NO_POLY; return NULL;}

  /*  verificação do polinomio maior */
  if(ppoly1->Degree >= ppoly2->Degree)
  {
    if ((Sub = PolyCreate (ppoly1->Degree)) == NULL) { 
      Error = NO_MEM; 
      return NULL; 
    }

    /* subtração dos dois polys */
    for (i = 0; i < (ppoly1->Degree)+1; i++){      
      Sub->Poly[i] = ppoly1->Poly[i] - ppoly2->Poly[i];
    }
  }

  else
  {
    if ((Sub = PolyCreate (ppoly2->Degree)) == NULL) { 
      Error = NO_MEM; 
      return NULL; 
    }
    for(i = 0; i < (ppoly2->Degree)+1; i++){
      Sub->Poly[i] =ppoly1->Poly[i]-ppoly2->Poly[i];
    }
  }
  Error=OK;

  ReducePoly(Sub);
  return Sub; 
}

PtPoly PolyMultiplication (PtPoly ppoly1, PtPoly ppoly2)
{
  if(!ValidPolys(ppoly1, ppoly2))
                return NULL;
               
        PtPoly mul;
        int i, j;
       
        if((mul = PolyCreate(ppoly1->Degree + ppoly2->Degree)) == NULL)
        {
                Error = NO_MEM;
                return NULL;
        }
       
        for(i = 0; i < ppoly1->Degree+1; i++) {
                for(j = 0; j < ppoly2->Degree+1; j++)
                        mul->Poly[i+j] += ppoly1->Poly[i] * ppoly2->Poly[j];     
        }
        ReducePoly(mul); 
        return mul;
}

int PolyEquals (PtPoly ppoly1, PtPoly ppoly2)
{
  int i;

  /* Validação dos polinómios */
  if(!ValidPolys(ppoly1,ppoly2)){
    return 0;
    Error=NO_POLY;
  } 
  Error = OK;
  ReducePoly(ppoly1);

  ReducePoly(ppoly2);
  /* comparaçao das componentes dos 2 polinomios */
  for(i = 0; i < (ppoly1->Degree)+1; i++)
    if(ppoly1->Poly[i] != ppoly2->Poly[i]) return 0;

  /* os  polinomios sao iguais */
  return 1;
}

void PolyStoreFile (PtPoly ppoly, char *pnomef)
{
  FILE *PtF; unsigned int i;

  /* verifica se o polinomio existe - verifies if polinomio exists */
  if (ppoly == NULL) { 
    Error = NO_POLY; 
    return ; 
  }

  /* abertura com validacao do ficheiro para escrita - opening the text FILE for writing */
  if ((PtF = fopen (pnomef, "w")) == NULL) { 
    Error = NO_FILE; 
    return ; 
  }

  /* escrita da dimensão do polinomio no ficheiro - writing the polinomio's size */
  fprintf (PtF, "%u\n", ppoly->Degree);

  /* escrita das componentes do polinomio no ficheiro - writing the polinomio's components */
  for (i = 0; i < (ppoly->Degree)+1; i++) {
    fprintf (PtF, "%lf\n", ppoly->Poly[i]);
  }

  Error = OK;
  fclose (PtF);  /* fecho do ficheiro - closing the text FILE */
}
PtPoly PolyCreateFile (char *pnomef)
{
  PtPoly Poly; FILE *PtF; unsigned int Degree, i;

  /* abertura com validacao do ficheiro para leitura - opening the text FILE for reading */
  if ( (PtF = fopen (pnomef, "r")) == NULL) { Error = NO_FILE; return NULL; }

  /* leitura da dimensão do polinomio do ficheiro - reading the polinomio's size from the text FILE */
  fscanf (PtF, "%u", &Degree);
  if (Degree < 1) { Error = BAD_DEGREE; fclose (PtF); return NULL; }

  /* criação do polinomio nulo - creating an empty polinomio */
  if ((Poly = PolyCreate (Degree)) == NULL) { fclose (PtF); return NULL; }

  /* leitura das componentes do polinomio do ficheiro - reading the polinomio's components from the text FILE */
  for (i = 0; i < Degree+1; i++) fscanf (PtF, "%lf", Poly->Poly+i);

  fclose (PtF);  /* fecho do ficheiro - closing the text FILE */
  return Poly;  /* devolve o polinomio criado - returning the new polinomio */

}

double PolyEvaluation (PtPoly ppoly, double px)
{
 unsigned int i;
  double x = ppoly->Poly[0];
  
  if (ppoly == NULL) { Error = NO_POLY; return 0.0; }
  
  for(i = 1; i< (ppoly->Degree)+1; i++)
    x += ppoly->Poly[i] * pow(px,i);

  Error = OK;
  return x;
}

/*******************************************************************************
 Função auxiliar que verifica se os dois polinómios existem. Devolve 1 em caso
 afirmativo e 0 em caso contrário. Valores de erro: OK ou NO_POLY.
  
 Auxiliary function to verify if the two polynomials exist. Returns 1 in 
 affirmative case and 0 otherwise. Error codes: OK or NO_POLY. 
*******************************************************************************/

static int ValidPolys (PtPoly ppoly1, PtPoly ppoly2)
{
  /* verifica se os dois polinómios existem - verifies if the two polynomials exist */
  if ((ppoly1 == NULL) || (ppoly2 == NULL)) { 
    Error = NO_POLY; 
    return 0; 
  }

  Error = OK;
  return 1;  /* os dois polinómios existem - they exist */
}

/*******************************************************************************
 Função auxiliar que reduz o polinómio ao menor grau possível. Valores de erro:
 NO_POLY.
  
 Auxiliary function to reduce the polynomial to its least degree. Error codes: NO_POLY. 
  
*******************************************************************************/

static void ReducePoly (PtPoly ppoly)
{
  unsigned int Degree;

  /* verifica se o polinómio existe - verifies if the polynomial exists */
  if (ppoly == NULL) { Error = NO_POLY; return ; }

  Degree = ppoly->Degree;

  while (Degree > 0 && ppoly->Poly[Degree] == 0.0) Degree--;

  if (Degree != ppoly->Degree)
     ppoly->Poly = (double *) realloc (ppoly->Poly, (Degree+1) * sizeof (double));

  ppoly->Degree = Degree;
  Error = OK;
}

