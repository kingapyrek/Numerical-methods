#include <stdio.h>
#include<stdlib.h>
#include<math.h>


#define frand() ((double)rand())/(RAND_MAX+1.0)


/*program był uruchamiany dla roznych m aby zapisywac do pliku dane dla m=10,30,50*/
int main()
{
	int N=201;
	double xmax=4.0;
	double xmin=-4.0;
	double sigma=(xmax-xmin)/16;
	double x0=2.0;
	double delta=(xmax-xmin)/(N-1);
	double x[N];
	double y[N];
	double phi [51][N];
	double beta,alfa;
	int m=50;
	double szum[N];
	double F,c,s;

	FILE *fp1;
	fp1=fopen("Gram.dat","w");

	for (int i=0;i<N;i++)
	{
		x[i]=xmin+i*delta;
		y[i]=sin((14*M_PI*x[i])/(xmax-xmin))*(exp(-(x[i]-x0)*(x[i]-x0)/(2*sigma*sigma))+exp(-(x[i]+x0)*(x[i]+x0)/(2 * sigma * sigma)));

	}

	for(int i=0;i<N;i++)
	{
		phi[0][i]=1.0;
	}


		/*for(int j=0;j<N;j++)
		{
			printf("%f\t%f\n",x[j],y[j]);
		}*/


	for(int j=1;j<m+1;j++)
	{
		double alfa_l=0.0;
		double alfa_m=0.0;
		double beta_l=0.0;
		double beta_m=0.0;

		for(int i=0;i<N;i++)
		{
			alfa_l+=x[i]*phi[j-1][i]*phi[j-1][i];
			alfa_m+=phi[j-1][i]*phi[j-1][i];

			if(j>1)
			{
			beta_l+=x[i]*phi[j-2][i]*phi[j-1][i];
			beta_m+=phi[j-2][i]*phi[j-2][i];
			}
		}

		if(j==1)
		{
			beta=0;
		}
		else
		{
			beta=beta_l/beta_m;
		}
		alfa=alfa_l/alfa_m;

		//printf("%g\t%f\n",alfa,beta);


		for(int k=0;k<N;k++)
		{
			if(j>1)
			phi[j][k]=(x[k]-alfa)*phi[j-1][k]-beta*phi[j-2][k];
			if(j==1)
			{
				phi[j][k] = (x[k] - alfa) * phi[j - 1][k];
			}
		}


	}

	for(int i=0;i<N;i++)
	{
		fprintf(fp1,"%g\t",x[i]);
		for(int j=0;j<7;j++)
		{
			fprintf(fp1,"%g\t",(phi[j][i]/phi[j][0]));
		}
		fprintf(fp1,"\n");
	}

	fclose(fp1);

	for(int i=0;i<N;i++)
	{
		szum[i]=y[i]+(frand()-0.5)/5;
	}

	//m=10;
	//m=30;
	

	FILE *fp2;
	fp2=fopen("pkt.dat","w");

	FILE *fp3;
	fp3=fopen("approx.dat","a+");

	for(int i=0;i<N;i++)
	{
		fprintf(fp2,"%f\t%f\n",x[i],y[i]);
	}

	for(int k=0;k<N;k++)
	{
		F=0;
		for(int j=0;j<=m;j++)
		{
			c=0;
			s=0;

			for(int i=0;i<N;i++)
			{
				c+=y[i]*phi[j][i];
				s+=phi[j][i]*phi[j][i];
			}

			F+= (c/s)*phi[j][k];
		}

		fprintf(fp3, "%f\t%f\n",x[k],F);
	}

	//fprintf(fp3,"\n\n");

	fclose(fp2);
	fclose(fp3);

	return 0;









	



}