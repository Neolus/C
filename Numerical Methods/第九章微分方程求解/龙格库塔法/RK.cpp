/*本文件实现求解微分方程的龙格-库塔算法*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*****函数声明******/
void RK(double (*f)(double,double),double yk,double x0,double xn,double h,FILE *fp); //RK龙格-库塔法
double fa(double tk,double yk); //fa第一个题目微分方程
double fb(double tk,double yk); //fb第二个题目微分方程
double fc(double tk,double yk);
void main()
{
	double y0=0;//初始条件
	double A[3],B[3],step; //A存放两题的左端点，B为右端点

	step=1./8; //初始步长0.1
	A[0]=0;  
	B[0]=3;
	
	A[1]=0;
	B[1]=1;

	A[2]=0;
	B[2]=3;
	double yc=1;

	FILE*fp;//定义指向文件的指针变量fp
	fp=fopen("c.txt","w+");
	
	RK(fc,yc,A[0],B[0],step,fp); //调用RK函数求解第一题微分方程
//	fprintf(fp,"The answer of question B\n");
//	RK(fb,y0,A[1],B[1],step,fp); //调用RK函数求解第二题微分方程

	fclose(fp); //关闭文本
	getchar();
}

/*****定义龙格-库塔法求解微分方程函数***********/
void RK(double (*f)(double,double),double yk,double x0,double xn,double h,FILE *fp)//f需要求解的微分方程，yk初始条件，x0微分起点，xn微分终点，h步长,fp指向文本
{
	int n,i,j;
	n=fabs(x0-xn)/h;
	double *t=new double [n+1];
	//龙格-库塔法中需要的常系数
	double a[3]={0.5,0.5,1};
	double b[6]={0.5,0,0.5,0,0,1};
	double w[4]={1./6,1./3,1./3,1./6};
	double sum;
	double k[4];
	


	for(i=0;i<=n;i++)
	{
		sum=0; 
		t[i]=x0+i*h; //每一次tk
		printf("%f\t%f\n",t[i],yk);
		fprintf(fp,"%0.8f\t%0.8f\n",t[i],yk); //写入文本
		if(i==n) break; //tk到达右边界停止计算

		//计算k0-k3
		k[0]=h*f(t[i],yk);
		k[1]=h*f(t[i]+a[0]*h,yk+b[0]*k[0]);
		k[2]=h*f(t[i]+a[1]*h,yk+b[1]*k[0]+b[2]*k[1]);
		k[3]=h*f(t[i]+a[2]*h,yk+b[3]*k[0]+b[4]*k[1]+b[5]*k[2]);

		for(j=0;j<4;j++) 
		{
			sum=sum+w[j]*k[j]; //k乘以权重并求和
		}
		yk=yk+sum; //计算yk+1
	}
	
	delete []t; //释放内存

}

/****第一个微分方程*******/
double fa(double tk,double yk)
{
	double y;
	y=9*tk*exp(3*tk);
	return y;
}
/****第二个微分方程*******/
double fb(double tk,double yk)
{
	double y;
	y=2*atan(tk);
	return y;
}


double fc(double tk,double yk)
{
	double y;
	y=(tk-yk)/2;
	return y;

}