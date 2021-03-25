#include<stdio.h>
#include<math.h>


double f(double x)
{
	return log(x*x*x +3*x*x+x+0.1)*sin(18*x);
}

double a=0.0;
double b=1.0;


void simpson(int n)
{
	double tab[n+1][n+1];
	
	//int N=pow(2,n+1);
	 

	for(int w=0;w<=n;w++)
	{
		double N=pow(2,w+1);
		double h=((b-a)/N);

		double suma=0;

		for(int i=0;i<=N/2-1;i++)
		{
			suma+=(h/3)*(f(a+2*i*h)+4*f(a+(2*i+1)*h)+f(a+(2*i+2)*h));
		}

		tab[w][0]=suma;
	}





	for(int w=1;w<n+1;w++)
	{
		for(int k=1;k<w+1;k++)
		{
			tab[w][k]=(pow(4,k)*tab[w][k-1]-tab[w-1][k-1])/(pow(4,k)-1);
		}
	}


	for (int w = 0; w <=n; w++) {
        for(int k = 0; k < w+1; k++)
           printf("%f\t",tab[w][k] );
       printf("\n");
    }

   
}



void milne(int n)
{
	double tab[n+1][n+1];
	
	//int N=pow(2,n+1);
	 

	for(int w=0;w<=n;w++)
	{
		double N=pow(2,w+2);
		double h=((b-a)/N);

		double suma=0;

		for(int i=0;i<=N/4-1;i++)
		{
			suma+=(4*h/90)*(7*f(a+4*i*h)+32*f(a+(4*i+1)*h)+12*f(a+(4*i+2)*h)+32*f(a+(4*i+3)*h)+7*f(a+(4*i+4)*h));
		}

		tab[w][0]=suma;
	}





	for(int w=1;w<n+1;w++)
	{
		for(int k=1;k<w+1;k++)
		{
			tab[w][k]=(pow(4,k)*tab[w][k-1]-tab[w-1][k-1])/(pow(4,k)-1);
		}
	}


	for (int w = 0; w <=n; w++) {
        for(int k = 0; k < w+1; k++)
           printf("%f\t",tab[w][k] );
       printf("\n");
    }

   
}



int main()
{
	int n=8;

	printf("Metoda Simpsona\n");
	simpson(n);
	printf("\n\nMetoda Milne'a\n");
	milne(n);

}