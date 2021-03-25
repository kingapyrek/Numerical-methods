#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "/opt/NR/numerical_recipes.c/nrutil.h"
#include "/opt/NR/numerical_recipes.c/nrutil.c"
#include "/opt/NR/numerical_recipes.c/gaussj.c"
#include "/opt/NR/numerical_recipes.c/tqli.c"
#include "/opt/NR/numerical_recipes.c/pythag.c"
#include "/opt/NR/numerical_recipes.c/tred2.c"



/*w wynikach nie do konca zgadzaja sie wartosci, szczegolnie ostatnia*/

void wypisz(float **A, int n)
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			printf("%f  ",A[i][j]);
		}
		printf("\n");

	}
}


void mnoz_macierz_wektor( int n, float **W, float* x0, float* wynik)
{
	float temp=0.0;
	for (int i=1;i<=n;i++) 
	{
		temp=0.0;
		for (int j=1;j<=n;j++)
		{
			temp+= W[i][j]*x0[j];
		}
		wynik[i]=temp;
	}
}


float mnoz_w_w(float *w1, float *w2, int n)
{
	float wynik = 0.0;
	for (int i=1;i<=n; i++)
	{
		wynik +=w1[i]*w2[i];
	}

	return wynik;

}



void dzielenie(float *w, float a, int n)
{
	for(int i=1;i<=n;i++)
	{
		w[i]/=a;
	}
}

void mnoz_w_w_m(float *w1, float *w2, float**M, int n)
{

	for(int i=1; i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			M[i][j]=w1[i]*w2[j];
		}
	}
}



void mnoz_m_l(float wartosc, float** M, int n)
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
		M[i][j]*=wartosc;
		}
	}
}

void odejmij(float **wynik, float** A, int n)
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			wynik[i][j]-=A[i][j];
		}
	}
}

void kopiuj(float *w1, float* w2, int n)
{
	for(int i=1; i<=n; i++){
		w1[i] = w2[i];
	}
}




int main()
{
	int n=7;
	float **A, **A_kopia, **Z, **W, **H;
	float *d, *e, *x, *x0;

	A=matrix(1,n,1,n);
	A_kopia=matrix(1,n,1,n);
	Z=matrix(1,n,1,n);
	//W=matrix(1,n,1,n);
	H=matrix(1,n,1,n);
	d=vector(1,n);
	e=vector(1,n);
	x=vector(1,n);
	x0=vector(1,n);

	float l;

	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			A[i][j]=sqrt(i+j);
			A_kopia[i][j]=sqrt(i+j);
		}
	}
	

	//wypisz(A,n);
	//printf("\n\n");
	//wypisz(W,n);
	tred2(A, n, d,e);

	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i==j)
			{
				Z[i][j]=1.0;
			}
			else
			{
				Z[i][j]=0.0;
			}
		}
	}


	tqli(d, e, n, Z);



	printf("Wartosci wlasne- biblioteka\n");
	for(int i=1;i<=n;i++)
	{
		printf("%3g\t", d[i]);
		printf("\n");
	}
	printf("\n\n");

	////iteracyjnie

	W=A_kopia;
	printf("iteracyjnie\n");

	for(int k=1;k<=n;k++)
	{
		
		for(int i=1;i<=n;i++)
		{
			x0[i]=1.0;
		}

		for(int i=1;i<=1000;i++)
		{
			mnoz_macierz_wektor(n, W , x0, x);
			l=mnoz_w_w(x, x0, n)/mnoz_w_w(x0, x0, n);
			dzielenie(x, sqrt(mnoz_w_w(x, x, n)), n);
			kopiuj(x0,x,n);
      if(i==1000){
			printf("l%d=%g", k, l);
		    printf("\n");}

		}
		printf("\n\n");
		

		//redukcja
		//mnozenie wektorow wynik w macierzy H
		mnoz_w_w_m(x, x, H, n);
		mnoz_m_l(l, H, n);
		odejmij(W, H, n);

	}

	free_matrix(A,1,n,1,n);
// 	free_matrix(W,1,n,1,n);
	free_matrix(A_kopia,1,n,1,n);
	free_matrix(H,1,n,1,n);
	free_matrix(Z,1,n,1,n);
	free_vector(d,1,n);
	free_vector(e,1,n);
	free_vector(x0,1,n);
	free_vector(x,1,n);




}