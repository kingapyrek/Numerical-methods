#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define N 5
#define IT_MAX 30



double licz_r(double *a, double *b, int n, double xj)
{
	b[n]=0.0;
	for(int k=n-1;k>=0;k--)
	{
		b[k]=a[k+1]+(xj*b[k+1]);
	}

	return (a[0]+xj*b[0]);




}


int main()
{
	double *a=malloc((N+1)*sizeof(double));
	double *b=malloc((N+1)*sizeof(double));
	double *c=malloc(N*sizeof(double));
	a[0]=240.0;
	a[1]=-196.0;
	a[2]=-92.0;
	a[3]=33.0;
	a[4]=14.0;
	a[5]=1.0;

	int L;
	int n;
	int it;
	double x0,x1, Rj, Rj2;

	//petla po kolejnych zerach wielomianu
	for(L=1; L<=N; L++)
	{
	//ustalamy aktualny stopien wielomanu: n=N-L+1
		n=N-L+1;
	//inicjalizacja wzoru iteracyjnego: x0
		x0=0;
	for(it=1; it<=IT_MAX; it++)
		{
		Rj=licz_r(a,b,n,x0);
		Rj2=licz_r(b,c,n-1,x0);
		x1=x0-Rj/Rj2;

		printf("L=%d, it=%d, x=%f, Rj=%g, Rj'=%f\n", L,it,x1,Rj,Rj2);
		
		//warunek wczesniejszego opuszczenia petli: |x1-x0| <1.0E-7
		if(fabs(x1-x0)<1.0e-7)
		{
			break;
		}
		//zachowujemy nowe przybliżenie:
		x0=x1;
		//zapisujemy do pliku: L, it, x0, Rj,Rj’
		//printf("L=%d, it=%d, x0=%f, Rj=%f, Rj'=%f\n", L,it,x0,Rj,Rj2);
		}
		printf("\n\n");
	//usuwamy znalezione zero z wielomianu (redukcja stopnia wiel. o 1):
	for(int i=0; i<=(n-1); i++)
		a[i]=b[i];
	}




	free(a);
	free(b);
	free(c);
	return 0;


}