#define _USE_MATH_DEFINES
#include "math.h"
#include "stdio.h"
#include "winbgi2.h"
#include "stdlib.h"
#include "rk4.h"
double C=0.5;
double q=1.2;
double g=9.81;
double a;
double r;
double H;
double S;
double m;
void fun(double t,double *X, double *F)
{
	
	F[3]=-g+q*pow(X[3],2)*S*C/(2*m);
	F[2]=X[3];
	F[1]=q*pow(X[1],2)*S*C/(2*m)-a*(H-X[2])/m;
	F[0]=X[1];

}
void main()
{
	int N;
	double vy0=0;
	double vx0=0;
	double x0=0;
	double t=0;
	double h=0.001;	
	double F[4];
	double X1[4];
	do
	{
		printf("podaj mase kuli m [kg]\n");
		scanf("%lf",&m);
	}while(m<=0);
	do
	{
		printf("podaj promien kuli r [cm]\n");
		scanf("%lf",&r);
	}while(r<=0);
	printf("podaj wspolczynnik predkosci wiatru a [N/m]\n");
	scanf("%lf",&a);
	do
	{
		printf("podaj wysokosc H z jakiej upuszczono kule [m]\n");
		scanf("%lf",&H);
	}while(H<=0);
	double X[4]={x0,vx0,H,vy0};
	S=M_PI*pow(0.01*r,2.);
	graphics(1000,1000);
	printf("Wybierz wykres ktory wykona program:\n");
	printf("1. wykres x(t)\n");
	printf("2. wykres vx(t)\n");
	printf("3. wykres y(t)\n");
	printf("4. wykres vy(t)\n");
	scanf("%d",&N);
	switch(N)
	{
	case 1:
		scale(0,-4*a*H,40,a*H);
		break;
	case 2:
		scale(0,10,40,-60);
		break;
	case 3:
		scale(0,-10,40,H+10);
		break;
	case 4:
		scale(0,5,40,-20);
		break;
	}
	while(t>=0)
	{
		
		vrk4(t,X,h,4,fun,X1);
		if(X1[2]<=0){break;}
		setcolor(0);
		switch(N)
		{
		case 1:
			circle(t,X1[0],2);
			break;
		case 2:
			circle(t,X1[1],2);
			break;
		case 3:
			circle(t,X1[2],2);
			break;
		case 4:
			circle(t,X1[3],2);
			break;
		}
		X[0]=X1[0];
		X[1]=X1[1];
		X[2]=X1[2];
		X[3]=X1[3];
		t+=h;
	}
	wait();
}




