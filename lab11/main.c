#include <stdio.h>
#include<stdlib.h>
#include <time.h>


#include  <gsl/gsl_fft_complex.h>
#include <math.h>
#define max(a,b) ((a)>(b)? (a):(b))

double rand_delta() {
	return (((double) rand()) / (RAND_MAX+1.0))  - 0.5;
}

int main()
{
	FILE *fp1=fopen("k8.dat","w");
	FILE *fp2=fopen("k10.dat","w");
	FILE *fp3=fopen("k12.dat","w");



	for(int k=8;k<=12;k+=2)
	{
		int N=pow(2,k);
		double f0[2*N];
		double f[2*N];
		double g1[2*N];
		double g2[2*N];
		double T=1.0;
		double t_max=3*T;
		double dt=t_max/N;
		double sigma=T/20;

		for(int i=0;i<N;i++)
		{
			double ti=dt*i;
			f0[2*i]=sin((2*M_PI/T)*ti)+sin(2*((2*M_PI/T)*ti))+sin(3*((2*M_PI/T)*ti));
			f0[2*i+1]=0.0;
			f[2*i+1]=0.0;
			f[2*i]=sin((2*M_PI/T)*ti)+sin(2*((2*M_PI/T)*ti))+sin(3*((2*M_PI/T)*ti))+rand_delta();
			g1[2*i]=(1.0 / (sigma * sqrt(2 * M_PI))) * exp(-(ti * ti) / (2* sigma * sigma));
			g2[2*i]=(1.0 / (sigma * sqrt(2 * M_PI))) * exp(-(ti * ti) / (2* sigma * sigma));
			g1[2*i+1]=g2[2*i+1]=0.0;

		
			if(k==8)
			{
				fprintf(fp1,"%f\t%f\n",ti,f[2*i]);
			}
			if(k==10)
			{
				fprintf(fp2,"%f\t%f\n",ti,f[2*i]);
			}
			if(k==12)
			{
				fprintf(fp3,"%f\t%f\n",ti,f[2*i]);
			}
		}
		fprintf(fp1,"\n\n");
		fprintf(fp2,"\n\n");
		fprintf(fp3,"\n\n");

		gsl_fft_complex_radix2_forward(f,1,N);
		gsl_fft_complex_radix2_forward(g1,1,N);
		gsl_fft_complex_radix2_backward(g2, 1, N);
		for(int i=0;i<N;i++)
		{
			double a1=f[2*i];
			double b1=f[2*i+1];
			double a2=g1[2*i]+g2[2*i];
			double b2=g1[2*i+1]+g2[2*i+1];
			f[2*i]=a1*a2-b1*b2;
			f[2*i+1]=a1*b2+a2*b1;
		}

		gsl_fft_complex_radix2_backward(f,1,N);

		double max_f=fabs(f[0]);

		for(int i=0;i<N;i++)
		{
			max_f=max(fabs(max_f),fabs(f[2*i]));
		}

		for(int i=0;i<N;i++)
		{
			double ti=dt*i;
			if(k==8)
			{
				fprintf(fp1,"%f\t%f\n",ti,(f[2*i]*2.5)/max_f);
			}
			if(k==10)
			{
				fprintf(fp2,"%f\t%f\n",ti,(f[2*i]*2.5)/max_f);
			}
			if(k==12)
			{
				fprintf(fp3,"%f\t%f\n",ti,(f[2*i]*2.5)/max_f);
			}

		}





	}


	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
}