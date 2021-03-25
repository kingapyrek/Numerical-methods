#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double f(double x)
{
	return (1.0)/(1.0+x*x);
}

double interpolacja(double x, int n, double *xm, double **ym)
{
	double wynik=0.0;

	for(int j=0;j<n+1;j++)
	{
		double suma=1.0;
		for(int i=0;i<j;i++)
		{
			suma*=(x-xm[i]);
		}

		wynik+=ym[j][j]*suma;

	}

	return wynik;
}

int main()
{
	int xmin=-5;
	int xmax=5;
	int n;
	double *xm;
	double **ym;
 double h;

  // czybyszew tymczasowo zakomentowany do wypisania wynikow z metody newtona

	/******************************************NEWTON****************N=5**********************************************************************/
	n=5;
  h=(xmax-xmin)/n;
	xm=malloc((n+1)*sizeof(double));
	for(int i=0;i<n+1;i++)
	{
		xm[i]=xmin+i*h;
	}


	ym=malloc((n+1)*sizeof(double*));
	for(int i=0;i<=n;i++)
	{
		ym[i]=malloc((n+1)*sizeof(double));
	}

	for(int i=0;i<n+1;i++)
	{
		ym[i][0]=f(xm[i]);
	}

	for(int j = 1; j <= n; j++)
	{
		for(int i = j;i <= n;i++)
		{
			ym[i][j]=(ym[i][j-1]-ym[i-1][j-1])/(xm[i]-xm[i-j]);

		}
	}
 


 
  for (double x = xmin; x < xmax + 0.0001; x += 0.01)
  {
    printf("%f\t%f\n", x, interpolacja(x,n,xm,ym));
  }
  
  printf("\n\n");
 
 /******************************************NEWTON****************N=10**********************************************************************/
 	n=10;
 	h=(xmax-xmin)/n;
	xm=malloc((n+1)*sizeof(double));
	for(int i=0;i<n+1;i++)
	{
		xm[i]=xmin+i*h;
	}



	ym=malloc((n+1)*sizeof(double*));
	for(int i=0;i<=n;i++)
	{
		ym[i]=malloc((n+1)*sizeof(double));
	}

	for(int i=0;i<n+1;i++)
	{
		ym[i][0]=f(xm[i]);
	}

	for(int j = 1; j <= n; j++)
	{
		for(int i = j;i <= n;i++)
		{
			ym[i][j]=(ym[i][j-1]-ym[i-1][j-1])/(xm[i]-xm[i-j]);

		}
	}
 
 
 
  for (double x = xmin; x < xmax + 0.0001; x += 0.01)
  {
    printf("%f\t%f\n", x, interpolacja(x,n,xm,ym));
  }
 
 
 printf("\n\n");
 
/******************************************NEWTON****************N=15**********************************************************************/
 	n=15;
  h=(xmax-xmin)/(double)n;

	xm=malloc((n+1)*sizeof(double));
	for(int i=0;i<n+1;i++)
	{
		xm[i]=xmin+i*h;
	}



	ym=malloc((n+1)*sizeof(double*));
	for(int i=0;i<=n;i++)
	{
		ym[i]=malloc((n+1)*sizeof(double));
	}

	for(int i=0;i<n+1;i++)
	{
		ym[i][0]=f(xm[i]);
	}

	for(int j = 1; j <= n; j++)
	{
		for(int i = j;i <= n;i++)
		{
			ym[i][j]=(ym[i][j-1]-ym[i-1][j-1])/(xm[i]-xm[i-j]);

		}
	}
 
 
 
  for (double x = xmin; x < xmax + 0.0001; x += 0.01)
  {
    printf("%f\t%f\n", x, interpolacja(x,n,xm,ym));
  }
  printf("\n\n");
  
 /*******************************************************NEWTON**********************N=20*******************************************************/
   	n=20;
	  h=(xmax-xmin)/(double)n;

	xm=malloc((n+1)*sizeof(double));
	for(int i=0;i<n+1;i++)
	{
		xm[i]=xmin+i*h;
	}



	ym=malloc((n+1)*sizeof(double*));
	for(int i=0;i<=n;i++)
	{
		ym[i]=malloc((n+1)*sizeof(double));
	}

	for(int i=0;i<n+1;i++)
	{
		ym[i][0]=f(xm[i]);
	}

	for(int j = 1; j <= n; j++)
	{
		for(int i = j;i <= n;i++)
		{
			ym[i][j]=(ym[i][j-1]-ym[i-1][j-1])/(xm[i]-xm[i-j]);

		}
	}
 
 
 
  for (double x = xmin; x < xmax + 0.0001; x += 0.01)
  {
    printf("%f\t%f\n", x, interpolacja(x,n,xm,ym));
  }
  
 // printf("\n\n");
 
 
 /**********************************************CZYBYSZEW****************************N=5****************************************/ 
 //printf("\n\n");
   /*  n=5;
	  h=(xmax-xmin)/(double)n;
     
     	ym=malloc((n+1)*sizeof(double*));
	for(int i=0;i<=n;i++)
	{
		ym[i]=malloc((n+1)*sizeof(double));
	}

	xm=malloc((n+1)*sizeof(double));
 	for(int i=0;i<n+1;i++)
	{
		xm[i]=(1.0/2.0)*((xmin-xmax)*cos(M_PI*((2.0*i+1)/(2.0*n+2.0))+(xmin+xmax)));
  
	}
 

 

	for(int i=0;i<n+1;i++)
	{
		ym[i][0]=f(xm[i]);
	}

	for(int j = 1; j <= n; j++)
	{
		for(int i = j;i <= n;i++)
		{
			ym[i][j]=(ym[i][j-1]-ym[i-1][j-1])/(xm[i]-xm[i-j]);

		}
	}
 
 
  for (double x = xmin; x < xmax + 0.0001; x += 0.01)
  {
    printf("%f\t%f\n", x, interpolacja(x,n,xm,ym));
  }*/
 

/**********************************************CZYBYSZEW****************************N=10****************************************/ 
 /*printf("\n\n");
     n=10;
	  h=(xmax-xmin)/(double)n;
     
     
     	ym=malloc((n+1)*sizeof(double*));
	for(int i=0;i<=n;i++)
	{
		ym[i]=malloc((n+1)*sizeof(double));
	}

	xm=malloc((n+1)*sizeof(double));
 	for(int i=0;i<n+1;i++)
	{
		xm[i]=(1.0/2.0)*((xmin-xmax)*cos(M_PI*((2.0*i+1)/(2.0*n+2.0))+(xmin+xmax)));
  
	}
 

	for(int i=0;i<n+1;i++)
	{
		ym[i][0]=f(xm[i]);
	}

	for(int j = 1; j <= n; j++)
	{
		for(int i = j;i <= n;i++)
		{
			ym[i][j]=(ym[i][j-1]-ym[i-1][j-1])/(xm[i]-xm[i-j]);

		}
	}
 
 
  for (double x = xmin; x < xmax + 0.0001; x += 0.01)
  {
    printf("%f\t%f\n", x, interpolacja(x,n,xm,ym));
  }
  */
  
  
  /**********************************************CZYBYSZEW****************************N=15****************************************/ 
 /*printf("\n\n");
     n=15;
	  h=(xmax-xmin)/(double)n;
     
     
     	ym=malloc((n+1)*sizeof(double*));
	for(int i=0;i<=n;i++)
	{
		ym[i]=malloc((n+1)*sizeof(double));
	}

	xm=malloc((n+1)*sizeof(double));
 	for(int i=0;i<n+1;i++)
	{
		xm[i]=(1.0/2.0)*((xmin-xmax)*cos(M_PI*((2.0*i+1)/(2.0*n+2.0))+(xmin+xmax)));
  
	}
 

	for(int i=0;i<n+1;i++)
	{
		ym[i][0]=f(xm[i]);
	}

	for(int j = 1; j <= n; j++)
	{
		for(int i = j;i <= n;i++)
		{
			ym[i][j]=(ym[i][j-1]-ym[i-1][j-1])/(xm[i]-xm[i-j]);

		}
	}
 
 
  for (double x = xmin; x < xmax + 0.0001; x += 0.01)
  {
    printf("%f\t%f\n", x, interpolacja(x,n,xm,ym));
  }*/
 

 /**********************************************CZYBYSZEW****************************N=20****************************************/ 
 /*printf("\n\n");
     n=20;
	  h=(xmax-xmin)/(double)n;

	ym=malloc((n+1)*sizeof(double*));
	for(int i=0;i<=n;i++)
	{
		ym[i]=malloc((n+1)*sizeof(double));
	}
 
	xm=malloc((n+1)*sizeof(double));
 	for(int i=0;i<n+1;i++)
	{
		xm[i]=(1.0/2.0)*((xmin-xmax)*cos(M_PI*((2.0*i+1)/(2.0*n+2.0))+(xmin+xmax)));
  
	}
 

	for(int i=0;i<n+1;i++)
	{
		ym[i][0]=f(xm[i]);
	}

	for(int j = 1; j <= n; j++)
	{
		for(int i = j;i <= n;i++)
		{
			ym[i][j]=(ym[i][j-1]-ym[i-1][j-1])/(xm[i]-xm[i-j]);

		}
	}
 
 
  for (double x = xmin; x < xmax + 0.0001; x += 0.01)
  {
    printf("%f\t%f\n", x, interpolacja(x,n,xm,ym));
  }*/
 
 



	free(ym);
	free(xm);









}