/*This file coontains the definition of class PC.
**Meanings of values and functions have been declared in PC.h. 
*/

#include "PC.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
//Constructor.  f1 is a function pointer. area is the integral interval. points are initial points which are computed by other method. h is the step. 
PC::PC(double (*f1)(double,double),std::vector<double> area,std::vector<double>points,double h):f(f1),interval(area),step(h)
{
	small=2*err;
	int n=abs(interval[1]-interval[0])/step; //get the number of points. 
	x.resize(n+1);
	y.resize(n+1);

	double b=interval[0];
	for(int i=0;i!=(n+1);++i)
	{
		x[i]=b; // abscissas. 
		b+=step;
	}


	for(int i=0;i!=4;++i) //four initial points's ordinates.
	{
		y[i]=points[i];
	}
	
	k=4;  //the start point 
}


void PC::Adams()
{
	k=4; //the start point 
	double fk[4],coef1[4],coef2[4]; 
	//fk stores answers of differential equation. coef1 is coefficient of prediction equation.coef2 is coefficient of correction  equation
	coef1[0]=-9;
	coef1[1]=37;
	coef1[2]=-59;
	coef1[3]=55;

	coef2[0]=0;
	coef2[1]=1;
	coef2[2]=-5;
	coef2[3]=19;	
	int n=y.size();
	while(k<n) //Compute all points' ordinates. 
	 {
		 double p,s,sum1,sum2;
		 sum1=0;
		 sum2=0;

		 for(int i=0;i!=4;++i)
		 {
			 fk[i]=f(x[i+k-4],y[i+k-4]);
			 sum1+=coef1[i]*fk[i];
		 }

		 for(int i=1;i!=4;++i)
		 {
			 sum2+=coef2[i]*fk[i];
		 }
	
		 p=y[k-1]+step/24*sum1; //predictor 
		 s=y[k-1]+step/24*(sum2+9*f(x[k],p)); //corrector 
		  y[k]=s;//insert ordinate.
		  ++k;
	 }

}


void PC::Milne() //This function is similar to function Adams. The only change is coefficients of predictor and corrector. 
{
	 k=4;
	 double fk[3],coef1[3],coef2[3];
	 coef1[0]=2;
	 coef1[1]=-1;
	 coef1[2]=2;

	 coef2[0]=0;
	 coef2[1]=1;
	 coef2[2]=4;

	 int n=y.size();
	 while(k<n)
	 {
		 double p,s,sum1,sum2;
		 sum1=0;
		 sum2=0;

		 for(int i=0;i!=3;++i)
		 {
			 fk[i]=f(x[i+k-3],y[i+k-3]);
			 sum1+=coef1[i]*fk[i];
		 }

		 for(int i=1;i!=3;++i)
		 {
			 sum2+=coef2[i]*fk[i];
		 }
	
		 p=y[k-4]+step*4/3*sum1;
		 s=y[k-2]+step/3*(sum2+f(x[k],p));
	
		  y[k]=s;
		  k++;
	 }
}


void PC::Hamming() //This function is similar to function Adams. The only change is coefficients of predictor and corrector. 
{
	 k=4;
	 double fk[3],coef1[3],coef2[3];
	 coef1[0]=2;
	 coef1[1]=-1;
	 coef1[2]=2;
	 coef2[0]=0;
	 coef2[1]=-1;
	 coef2[2]=2;
	 int n=y.size();
	 while(k<n)
	 {
		 double p,s,sum1,sum2;
		 sum1=0;
		 sum2=0;

		 for(int i=0;i!=3;++i)
		 {
			 fk[i]=f(x[i+k-3],y[i+k-3]);
			 sum1+=coef1[i]*fk[i];
		 }

		 for(int i=1;i!=3;++i)
		 {
			 sum2+=coef2[i]*fk[i];
		 }
	
		 p=y[k-4]+step*4/3*sum1;
		 s=(-y[k-3]+9*y[k-1])/8+step*3/8*(sum2+f(x[k],p));
	
		 y[k]=s;
		 k++;
	 }
}


void print(const PC & pc,ofstream &out)
{
	for(int i=0;i!=pc.x.size();++i)
	{

//		cout<<fixed<<setprecision(2)<<pc.x[i]<<'\t'<<setprecision(9)<<pc.y[i]<<endl;
		out<<pc.x[i]<<'\t'<<setprecision(9)<<pc.y[i]<<endl;
	}
}
