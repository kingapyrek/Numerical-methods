#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "/opt/NR/numerical_recipes.c/nrutil.h"
#include "/opt/NR/numerical_recipes.c/nrutil.c"
#include "/opt/NR/numerical_recipes.c/gaussj.c"
#include "/opt/NR/numerical_recipes.c/tqli.c"
#include "/opt/NR/numerical_recipes.c/pythag.c"
#include "/opt/NR/numerical_recipes.c/tred2.c"



int main(){

int nx=20;
int ny=20;

int n=ny*nx;

int m=10;

float t=-0.021;

float **H, **Y, **X;

float *d,*e;

H=matrix(1,n,1,n);
Y=matrix(1,n,1,n);
X=matrix(1,n,1,n);

d=vector(1,n);
e=vector(1,n);

for(int i=1;i<=n;i++)
{
	for(int j=1;j<=n;j++)
	{
		if(i==j)
		{
			Y[i][j]=1;
		}
		else
		{
			Y[i][j]=0;
		}
	}
}

for(int i=1;i<=nx;i++)
{
	for(int j=1;j<=ny;j++)
	{
		int l=j+(i-1)*ny;
		for(int k=1;k<=n;k++)H[l][k]=0.;
		if(i>1) H[l][l-ny]=t; //dla i=1 nie ma sasiada z lewej strony
		if(i<nx) H[l][l+ny]=t; //dla i=nx nie ma sasiada z prawej strony
		H[l][l]=-4*t;
		if(j>1) H[l][l-1]=t; //dla j=1 nie ma sasiada ponizej siatki
		if(j<ny) H[l][l+1]=t; //dla j=ny nie ma sasiada powyzej siatki
	}
}

tred2(H, n, d, e);

tqli(d, e, n, Y );


for(int i=1; i<=n; i++){
  for(int j=1; j<=n; j++)
  {
    float s=0.0;
    for( int k=1; k<=n; k++) s +=H[i][k]*Y[k][j];
    X[i][j]=s;
  }}

int *indx=ivector(1,n);

for(int l=1;l<=n;l++) indx[l]=l; // inicjalizacja
	for(int l=1;l<=n-1;l++)
	{
		for(int k=n;k>=l+1;k--)
		{
			float e1=d[k-1];
			float e2=d[k];
			int l1=indx[k-1];
			int l2=indx[k];
			if(e2<e1)
			{ //wymieniamy energie i indeksy wektorów miejscami
				d[k]=e1;
				d[k-1]=e2;
				indx[k]=l1;
				indx[k-1]=l2;
			}
		}		
	}


FILE *fp;
fp=fopen("dane.dat","w");
for(int i=1;i<=nx;i++)
{
	for(int j=1;j<=ny;j++)
	{
		int l=j+(i-1)*ny;
		fprintf(fp,"%6d %6d ",i,j);
		for(int k=1;k<=m;k++)fprintf(fp," %12.6f ", X[l][indx[k]]);
			fprintf(fp,"\n");
	}
	fprintf(fp,"\n");
}
fclose(fp);


for(int i=1;i<=15;i++)
{
printf("%g\n",d[i]);
}

free_matrix(H,1,n,1,n);
free_matrix(X,1,n,1,n);
free_matrix(Y,1,n,1,n);
free_vector(d,1,n);
free_vector(e,1,n);
free_ivector(indx,1,n);





}