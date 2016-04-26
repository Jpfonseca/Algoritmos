#include <stdio.h>
#include <stdlib.h>

int Count;

int functionrecpn(int);
int functionpnddin(int);
int functionpnddineff(int);
int main(int argc, char const *argv[])
{

	int Result[13];

	for (int i = 0; i < 13; ++i)
	{
		Count=0;
		Result[i]=functionrecpn(i);
		fprintf(stdout, "A função recursiva de %3d  é : %3d .Foram executadas %3d divisões\n",i, Result[i], Count);
	}
	printf("\n");
	printf("\n");
	printf("\n");
	for (int i = 0; i < 13; ++i)
	{
		Count=0;
		Result[i]=functionpnddin(i);
		fprintf(stdout, "A função dinâmica de %3d  é : %3d .Foram executadas %3d divisões\n",i, Result[i], Count);	
	}
	printf("\n");
	printf("\n");
	printf("\n");
	for (int i = 0; i < 13; ++i)
	{
		Count=0;
		Result[i]=functionpnddineff(i);
		fprintf(stdout, "A função dinâmica eficiente de %3d  é : %3d .Foram executadas %3d divisões\n",i, Result[i], Count);	
	}
	exit (EXIT_SUCCESS);

}

int functionrecpn(int n){
	int right=(n+1)/2;
	int left=n/2;
	if (n<=0)
	{
		return-1;
	}
	else if (n==1)
	{
		return 0;
	}
	else if (n>1)
	{
		Count=Count+2;
		return functionrecpn(left)+functionrecpn(right)+(left)+(right);
	}
	return -2;
}

int functionpnddin(int n){
	int intermidiate[n];
	int right, left;
	intermidiate[0]=0;
	intermidiate[1]=0;
	if (n==1)
	{
		return 0;
	}
	for (int i = 2; i <=n; ++i)
	{
		Count+=2;
		right=(i+1)/2;
		left=i/2;
		intermidiate[i]=(left)+(right)+intermidiate[left]+intermidiate[right];
		/*printf("%d \n", intermidiate[i]);*/
	}
	return intermidiate[n];
}

int functionpnddineff(int n){
	
	int right, left;
	int c=n/2;
	int d=(n+1)/2;
	int intermidiate[d+1];
	
	intermidiate[0]=0;
	intermidiate[1]=0;
	if (n==1)
	{
		return 0;
	}
	if (n<=0)
	{
		return -1;
	}
	Count=2;
	
	for (int i = 2; i <=d; ++i)
	{
		Count+=2;
		right=((i+1)/2);
		left=(i/2);
		intermidiate[i]=(left)+(right)+intermidiate[left]+intermidiate[right];
		/*printf("%d \n", intermidiate[i]);*/
	}
	/*printf("%d \n", intermidiate[c] );*/
	return intermidiate[d]+intermidiate[c]+c+d;
}
