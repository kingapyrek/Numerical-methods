#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include <time.h>


double f(double x, double y)
{
	return sin(x)*sin(y)-exp(-pow(x+(M_PI/2),2)-pow(y-(M_PI/2),2));
}

double d_rand ( const double min , const double max )
{
 double r = ( double ) rand () / RAND_MAX ; // Przedzial [0 , 1]
 r = r * ( max - min ) + min ; // Przeskalowanie do [min , max]

 return r;
}


int main()
{
	int N=1;
	double x0=5;
	double y0=5;
	//double xmin=-10;
	//double xmax=10;

	//double ymin=-10;
	//double ymax=10;
	double x[N];
	double y[N];
	double delta_x=0;
	double delta_y=0;

	FILE *fp1=fopen("w0.dat","w");
	FILE *fp2=fopen("T.dat","w");

	for(int i=0;i<N;i++)
	{
		x[i]=5;
		y[i]=5;
	}


	for(int it=0;it<=20;it++)
	{
		double T=10/pow(2,it);
		
		for(int k=0;k<100;k++)
		{
			for(int i=0;i<N;i++)
			{
				do
				{
					delta_x=d_rand(-1,1);
					delta_y=d_rand(-1,1);

				}
				while(x[i]+delta_x<-10 || x[i]+delta_x>10 || y[i]+delta_y<-10 || y[i]+delta_y>10);

				if(f(x[i]+delta_x,y[i]+delta_y)<f(x[i],y[i]))
				{
					x[i]=x[i]+delta_x;
					y[i]=y[i]+delta_y;
				}
				else if(d_rand(0,1)<exp(-((f(x[i]+delta_x,y[i]+delta_y)-f(x[i],y[i]))/T)))
				{
					x[i]=x[i]+delta_x;
					y[i]=y[i]+delta_y;

				}
				if(i==0)
				{
					fprintf(fp1,"%f\n",f(x[i],y[i]));
				}

			}
    //  printf("%f\n",T);

		}



		if(it==0 || it==7 || it==20)
		{
			for(int i=0;i<N;i++)
				fprintf(fp2, "%f\t%f\n",x[i],y[i]);

			fprintf(fp2, "\n\n");
      printf("%f\n",T);
		}

	}
 double wynik=f(x[0],y[0]);
 int it=0;
   
   for(int i=0;i<N;i++)
   {
    double temp=f(x[i],y[i]);
    if(temp<wynik)
    {
    wynik=temp;
    it=i;
    }
    
    }
   printf("%f %d %f %f",wynik,it,x[it],y[it]);
   

	fclose(fp1);
	fclose(fp2);


}