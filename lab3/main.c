#include <stdio.h>
#include <stdlib.h>
#include <math.h>



#define N 2001


double suma_kwadratow(double *x,int n)
{
	double suma=0.0;
	for(int i=0;i<n;i++)
	{
		suma+=(x[i]*x[i]);
	}

	return suma;

}

int main()
{


	int v0=0;
	int x0=1;
	int w=1;

	double h=0.02;

	double B1=0.0;
	double Fo1=0.0;
	double omega1=0.8;

	double a1=1.0;
	double a2=w*w*h*h-2-(B1*h);
	double a3=1+B1*h;

	//printf("%f,%f,%f\n",a1,a2,a3 );


	double *b, *d0, *d1, *d2, *xs, *xn;

	b=malloc(N*sizeof(double));
	d0=calloc(N,sizeof(double));
	d1=calloc(N,sizeof(double));
	d2=calloc(N,sizeof(double));
	xs=calloc(N,sizeof(double));
	xn=calloc(N,sizeof(double));


	b[0]=1.0;
	b[1]=0.0;

	for(int i=1;i<N-1;i++)
	{
		b[i+1]=Fo1*sin(omega1*i*h)*(h*h);
	}

/*for(int i=0;i<N;i++)
{
	printf("%f\n",b[i]);
}*/

	d0[0]=1.0;
	d0[1]=1.0;

	for(int i=2;i<N;i++)
	{
		d0[i]=a3;
	}

	d1[0]=0.0;
	d1[1]=-1.0;

	for(int i=2;i<N;i++)
	{
		d1[i]=a2;

	}


	d2[0]=0.0;
	d2[1]=0.0;

	for(int i=2;i<N;i++)
	{
		d2[i]=a1;

	}

	int it=0;

	while(it<100000)
	{
		++it;


		for(int i=0;i<N;i++)
		{
			if(i==0 || i==1)
			{
				xn[i]=(1.0/d0[i])*(b[i]-d1[i]*1.0-d2[i]*2.0);
		

			}
			else
			{
				xn[i]=(1.0/d0[i])*(b[i]-d1[i]*xs[i-1]-d2[i]*xs[i-2]);
			}
		}

		if(fabs(suma_kwadratow(xn,N)-suma_kwadratow(xs,N))< 1e-6)
		break;
		

		for(int i=0;i<N;i++)
		{
			xs[i]=xn[i];
		}



	}	

	for(int i=0;i<N;i++)
	{
		printf("%g	%g\n",i*h,xn[i]);
	}
	//printf("%d\n",it);

/***************************************DRUGI_PRZYPADEK***********************************************/


	double B2=0.4;
	double Fo2=0.0;
	double omega2=0.8;

	a1=1.0;
	a2=w*w*h*h-2-(B2*h);
	a3=1+B2*h;



	b[0]=1.0;
	b[1]=0.0;

	for(int i=1;i<N-1;i++)
	{
		b[i+1]=Fo2*sin(omega2*i*h)*(h*h);
	}


	d0[0]=1.0;
	d0[1]=1.0;

	for(int i=2;i<N;i++)
	{
		d0[i]=a3;
	}

	d1[0]=0.0;
	d1[1]=-1.0;

	for(int i=2;i<N;i++)
	{
		d1[i]=a2;

	}


	d2[0]=0.0;
	d2[1]=0.0;

	for(int i=2;i<N;i++)
	{
		d2[i]=a1;

	}

	it=0;

	while(it<100000)
	{
		++it;


		for(int i=0;i<N;i++)
		{
			if(i==0 || i==1)
			{
				xn[i]=(1.0/d0[i])*(b[i]-d1[i]*1.0-d2[i]*2.0);
		

			}
			else
			{
				xn[i]=(1.0/d0[i])*(b[i]-d1[i]*xs[i-1]-d2[i]*xs[i-2]);
			}
		}

		if(fabs(suma_kwadratow(xn,N)-suma_kwadratow(xs,N))< 1e-6)
		break;
		

		for(int i=0;i<N;i++)
		{
			xs[i]=xn[i];
		}



	}	

	printf("\n\n\n");

	for(int i=0;i<N;i++)
	{
		printf("%g	%g\n",i*h,xn[i]);
	}


	/**************************************************TRZECI_PRZYPADEK*********************************/

	double B3=0.4;
	double Fo3=0.1;
	double omega3=0.8;

	a1=1.0;
	a2=w*w*h*h-2-(B3*h);
	a3=1+B3*h;

	b[0]=1.0;
	b[1]=0.0;

	for(int i=1;i<N-1;i++)
	{
		b[i+1]=Fo3*sin(omega3*i*h)*(h*h);
	}



	d0[0]=1.0;
	d0[1]=1.0;

	for(int i=2;i<N;i++)
	{
		d0[i]=a3;
	}

	d1[0]=0.0;
	d1[1]=-1.0;

	for(int i=2;i<N;i++)
	{
		d1[i]=a2;

	}


	d2[0]=0.0;
	d2[1]=0.0;

	for(int i=2;i<N;i++)
	{
		d2[i]=a1;

	}

	it=0;

	while(it<100000)
	{
		++it;


		for(int i=0;i<N;i++)
		{
			if(i==0 || i==1)
			{
				xn[i]=(1.0/d0[i])*(b[i]-d1[i]*1.0-d2[i]*2.0);
		

			}
			else
			{
				xn[i]=(1.0/d0[i])*(b[i]-d1[i]*xs[i-1]-d2[i]*xs[i-2]);
			}
		}

		if(fabs(suma_kwadratow(xn,N)-suma_kwadratow(xs,N))< 1e-6)
		break;
		

		for(int i=0;i<N;i++)
		{
			xs[i]=xn[i];
		}



	}	

	printf("\n\n\n");

	for(int i=0;i<N;i++)
	{
		printf("%g	%g\n",i*h,xn[i]);
	}



	free(b);
	free(d0);
	free(d1);
	free(d2);
	free(xs);
	free(xn);


}