/*本文件实现了非线性方程求解的牛顿-拉夫森算法*/

#include <math.h>                //常用数学函数
#include <stdio.h>            //输入输出函数
#include <float.h>            //对应于FLT_MIN的函数

double eps=FLT_MIN;
int b,M;                //定义全局变量 b代表题号为1、2、3,M为需要求解的阶数此处对应5、3、2

//函数声明
double fm(double x);    //数学函数
double df(double x);   //数学函数的一阶导数
double Newton (double p0,double tol,int max,double (*fm)(double),double (*df)(double)); //函数声明Newton为牛顿-拉夫森算法

void main()            //主函数
{ 

	double z;                             //定义变量
	printf("Please input the number of title \n ");            //输出题目选择
	scanf("%d",&b);                                        //题号赋值给b
	printf("Please input the order M \n");                 //输入求解阶数要求
	scanf("%d",&M);

	z=Newton(1,1e-7,1000,fm,df); //调用牛顿-拉夫森函数求解
	printf("z is %0.8f",z);
	getchar();
	getchar();

}


//定义牛顿-拉夫森方法 p0初始估计点，tol误差，max最大的计算次数，fm函数指针指向数学函数，df为其一阶导数
double Newton (double p0,double tol,int max,double (*fm)(double),double (*df)(double)) 
{

	int i;
	double err,rel;
	double pk,pkpre;
	pkpre=p0;
	for (i=0;i<max;i++)
	{
		pk=pkpre-M*fm(pkpre)/(df(pkpre)+eps); //牛顿-拉夫森迭代公式
		err=fabs(pk-pkpre);
		rel=err/(fabs(pk)+eps);
		pkpre=pk;
		printf ("p[%d] is %0.9f\n",i,pk);

	}
	return pk;

}

//fm需要求解的三个方程
double fm(double x)
{
	
	double fx,f1,f2,f3;

	if (b==1)
	{
		fx=pow(x-2,5);
	}
	if (b==2)
	{
		fx=sin(pow(x,3));
	}
	if(b==3)
	{
	fx=(x-1)*log(x);
	}
	return fx;
}

//一阶导数采用导数定义
double df(double x)
{
	double f(double x);
	double d,dx=1e-5;

  // df=5*pow(x-2,4);
    d=(f(x+dx)-f(x))/dx;
	return d;
}