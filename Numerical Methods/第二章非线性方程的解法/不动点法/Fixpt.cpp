/*本文件实现非线性方程的不动点解法*/

#include <math.h>                         //常用数学函数
#include <stdio.h>                        //输入输出函数
#include <float.h>                        //对应于FLT_MIN的函数

double fixpt(double (*g) (double),double p0,double tol, int max);     //函数声明，不动点函数
double g(double x);												   //函数声明，参与运算的实际函数g（x）

void main()                                                      //主函数
{   

	 double z;
	 z=fixpt(g,1.2,1e-12,1000);   //函数调用，g为具体函数，1.2为不动点运算的初始值，1e12为相对误差和绝对误差的判断值，1000为运算最多次数max
     printf("p is %0.12f",z);                 //输出不动点算法的最终值,%0.12f表示输出值小数位数保留12位
	 getchar();                         //保持运行窗
	 getchar();
	 getchar();
}


 double fixpt(double (*g) (double),double p0,double tol,int max)  //定义函数不动点算法函数fixpt，并声明其中各个参数类型，double (*g) (double)为函数指针，p0为运算初始点，tol为误差及相对误差的判断值，max为运算次数
{
	 double res,err, rel,eps=FLT_MIN;                                //对下面要用到的变量定义，FLT_MIN为float最小数
	 double *p=new double[max];                                     //定义一个指针，用来存储函数g（x）中x的地址
  //   double *p=new double[max];
	   p[0]=p0;                                             //初始化p【0】使其为不动点运算的初始值
		int i;
		for(i=0;i<max-1;i++)                                  //运用for循环，进行多次计算
		{
		p[i+1]=g(p[i]);                                       //不动点算法公式
		err=fabs(p[i+1]-p[i]);								//绝对误差err的计算
		rel=err/(fabs(p[i+1])+eps);						   //相对误差rel的计算，用err/abs(p[i+1]),eps为float最小数，用来保证分母不为零
     	 printf("p[%d] is %0.12f\n",i,p[i]);     //输出每次的p[i],方便观测
		if((err<tol)||(rel<tol)) break;                     //绝对误差和当相对误差低于预定值时终止循环
		}
		
		if(i==max-1)                                      //如果当循环运算到预设最大次数时还没有终止运算，输出maximum number of iterations exceed
		{
			printf("maximum number of iterations exceed\n");             //"\n"换行
		}
		res=p[i];
		
		delete[]p;
		return res;                     //函数的返回值;

}


double g(double x)                       //定义运算的实际数学函数g（x）
{
	double gx;
	gx=pow(x,x-cos(x));                        //g(x)的具体表达形式
	return gx;                           //返回函数计算结果
}

