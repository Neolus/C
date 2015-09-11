/* This program realize the prediction&correction algorithm.
**main fucntion is included in this file.
*/

#include <iostream>
#include <vector>
#include "PC.h"
#include <fstream>
using namespace std;

//declaration of differential equations. 
double f(double t,double y);
double f1(double t,double y);
double f2(double t,double y);
double f3(double t,double y);


void main()
{
	vector<vector<double>> points; 
	vector<vector<double>> area;	
	
	//initial condintions of three equations
	double initial[3][4]={{1,1.0499584,1.0996680,1.1488850},{0,0.049979169,0.099833417,0.14943813},{1,1.0012513,1.0050209,1.0113564}};
	//boundary conditions of three equations
	double boundary[3][2]={{0,5},{0,1.55},{0,1.55}};
	//integral step
	double step[3]={0.05,0.05,0.05};

	//write conditons into vector
	for(int i=0;i!=3;++i)
	{
		vector<double> vec(4);
		for(int j=0;j!=4;j++)
		{
			vec[j]=initial[i][j];
		}
		points.push_back(vec);
	}

	for(int i=0;i!=3;++i)
	{
		vector<double> vec(2);
		for(int j=0;j!=2;++j)
		{
			vec[j]=boundary[i][j];
		}
		area.push_back(vec);
	}

	//construct three PC objects 
	PC pc1(f1,area[0],points[0],step[0]); //corresponding the first equation
	PC pc2(f2,area[1],points[1],step[1]); //corresponding the second equation
	PC pc3(f3,area[2],points[2],step[2]); //corresponding the third equation

    ofstream out1("11.txt"),out2("22.txt"),out3("33.txt"); //ofstream is used to record results

/*
	vector<PC> allPc(3);
	allPc[0]=pc1;
	allPc[1]=pc2;
	allPc[2]=pc3;
*/

	//Use three methods to compute the first equation
	pc1.Adams();
	print(pc1,out1); //record the result of Adams method
	pc1.Milne();
    print(pc1,out1); //record the result of Milne method
	pc1.Hamming();
	print(pc1,out1); //record the result of Hamming method
	

	//Use three methods to compute the second equation
	pc2.Adams();
	print(pc2,out2);
	pc2.Milne();
	print(pc2,out2);
	pc2.Hamming();
	print(pc2,out2);

	//Use three methods to compute the third equation
	pc3.Adams();
	print(pc3,out3);
	pc1.Milne();
	print(pc3,out3);
	pc1.Hamming();
	print(pc3,out3);
	
	system("pause");
}





//Differential equations will be computed. 
double f(double t,double y)
{
	return (t-y)/2;
}

double f1(double t,double y)
{
	double r=y*(2-y);
	return r;
}

double f2(double t,double y)
{
	double r=sqrt(1-y*y);
	return r;
}


double f3(double t,double y)
{
	double r=y*y*sin(t);
	return r;
}