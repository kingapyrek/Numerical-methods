#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "/opt/NR/numerical_recipes.c/nrutil.h"
#include "/opt/NR/numerical_recipes.c/nrutil.c"
#include "/opt/NR/numerical_recipes.c/gaussj.c"



void wyzM(float *xw,float *yw, float *w, int n, float alfa, float beta)
{

	float xmax=5.0;
	float xmin=-5.0;
	float h=(xmax-xmin)/(n-1);

	float lambda=0.5;
	float mi=1-lambda;
	float **A=matrix(1,n,1,n);
	float **d = matrix(1, n, 1, 1);

	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			A[i][i]=2.0;
			if (i==(j+1))
			{
				A[i][j]=mi;

			}

			else if(i==(j-1))
			{
				A[i][j]=lambda;
			}

			else
			{
				A[i][j]=0.0;
			}
		}
	}

	A[1][1]=1.0;
	A[n][n]=1.0;
	A[1][2]=0.0;
	A[n][n-1]=0.0;

	for(int i=1;i<=n;i++)
	{
		d[i][1]=(6.0/(2*h))*((yw[i+1]-yw[i])/h-(yw[i]-yw[i-1])/h);
	}

	d[1][1] = alfa;
	d[n][1] = beta;


	gaussj(A, n, d, 1);

	for(int i=1;i<=n;i++)
	{
		w[i]=d[i][1];
	}


	free_matrix(A, 1, n, 1, n);
	free_matrix(d, 1, n, 1, 1);

}


float wyzSx(float *xw,float *yw, float *m, int n, float x)
{

	float sx=0.0;
   	float xmax=5.0;
    float xmin=-5.0;
    float h=(xmax-xmin)/(n-1);
    

   
    float *A = vector(1, n);
    float *B = vector(1, n);

    for (int i=2; i<=n; i++)
    {
        A[i]=(yw[i]-yw[i-1])/h - (h/6)*(m[i]-m[i-1]);
        B[i]=yw[i-1] - m[i-1]*(pow(h,2)/6);

        if (xw[i-1]<=x && x<=xw[i])
        {
            sx=m[i-1]*pow(xw[i]-x,3)/(6*h) + m[i]*pow(x-xw[i-1],3)/(6*h) + A[i]*(x-xw[i-1]) + B[i];
            break;
        }
    }


    free_vector(A,1,n);
    free_vector(B,1,n);
    return sx;

}






float f1(float x)
{
	return 1/(1+x*x);
}


float f2(float x)
{
	return cos(2*x);
}


float pochodna(float x)
{
    float step = 0.01;
    float result = (f1(x - step) - 2 * f1(x) + f1(x + step)) / pow(step, 2);
    return result;
}


int main()
{

/* program by³ uruchamiany dla roznych n i z zapisywaniem do roznych plikow, aby otrzymac pliki f1.dat f2.dat pochodne.dat, tu akurat zostalo ostanie n=21*/
	int n;
	n=21;
	float *xw=vector(1,n);
	float *yw=vector(1,n);
	float *m=vector(1,n);
	float x_min=-5.0;
	float x_max=5.0;
	float alfa=0.0;
	float beta=0.0;
	//float step=0.01;
	float h=(x_max-x_min)/(n-1);

	FILE * fp1=fopen("f1.dat","a+");
	FILE * fp2=fopen("f2.dat","a+");
	FILE * fp3=fopen("pochodne.dat","a+");

	for(int i=1;i<=n;i++)
	{
		xw[i]=x_min+(i-1)*h;
		yw[i]=f2(xw[i]);
	}



	wyzM(xw, yw, m, n, alfa, beta);

  //tu pochodne dla n=10
	/*for(int i = 1; i <= n; i++)
	{
		fprintf(fp3,"%10f\t%10f\t%10f\n",xw[i], m[i], pochodna(xw[i]));
	}*/


	for(float x = x_min; x <=x_max; x += 0.01)
	{
   		fprintf(fp2, "%10f\t%10f\n", x, wyzSx(xw, yw, m, n, x));

	}


//2 puste linie do pliku
	//fprintf(fp1, "\n\n");


	fclose(fp1);
	fclose(fp2);
	fclose(fp3);


free_vector(xw, 1, n);
	free_vector(yw, 1, n);
	free_vector(m, 1, n);










}