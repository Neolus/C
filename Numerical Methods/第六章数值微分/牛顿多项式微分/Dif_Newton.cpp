/*本文件实现牛顿多项式求解导数的算法*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


/*****函数声明*******/
float diffnew(float *x,float *y,float t,int n);  //diffnew函数为牛顿微分求导函数
float Compute(float (*f)(float),float a,float b,int n,float *x,float *y);  //Compute函数为计算点及其对应的函数f的值
 float f1(float x);  //f1为数学函数


void main()
{

	float x0,xn,step,t1,z;
	int i;
	int N=20; //取点的个数
	float *X=new float[N]; //存放分断点的值
	float *Y=new float[N];  //存放点对应的数学函数值

	FILE*fp;//定义指向文件的指针变量fp
    fp=fopen("20.txt","w+");  //创建文本

	x0=0.1; //起始点
	xn=2;   //终点
	step=(xn-x0)/(N-1); //步长
	Compute(f1,x0,xn,N,X,Y); //调用函数，计算出数组X，Y
	
	//计算出每个点对应的导数值
	for(i=0;i<N;i++)
	{
	  t1=x0+i*step;
	  z=diffnew(X,Y,t1,N); //调用牛顿微分函数
	  printf("%0.9f\t%0.9f\n",t1,z);  //输出导数值及其对应点，
	  fprintf(fp,"%0.9f\t%0.9f\n",t1,z);  //将导数及其对应值写入文本
	}
	fclose(fp); //关闭文本
	delete []X;
	delete []Y;
	getchar();
}


/*******定义牛顿微分函数****************/
float diffnew(float *x,float *y,float t,int n)  //x输入数组、y为x对应的函数值，t表示在t处求解导数，n为点的个数
{
	int i,j,k;
	float dif,temp,s;

	float *A=new float[n];  //A存放多项式系数
	for(i=0;i<n;i++)
	{
	  A[i]=y[i]; //赋初始值
	}

	
	for(i=1;i<n;i++) //利用循环，计算多项式系数
	{
	  for(j=n-1;j>=i;j--)
	  {
		  A[j]=(A[j]-A[j-1])/(x[j]-x[j-i]);
	  }

	}

	dif=A[1];//dif为最后的导数值

	for(i=2;i<n;i++)  //循环，计算最后的导数值
	{
		s=0; //求和变量赋初始值
		for(k=0;k<i;k++)
			{
			temp=1; //叠乘变量赋初始值
			for(j=0;j<i;j++)
				{
				  if(j==k) continue;
				  temp*=t-x[j];
				}
			s=s+temp;
			}
		dif=dif+A[i]*s; //导数
	}
	delete []A;
	return (dif); //返回导数值
}





/*****定义计算数组函数************/
float Compute(float (*f)(float),float a,float b,int n,float *x,float *y)  //f为需要计算的数学函数，a为横坐标的起点，b为横坐标的终点，n为取点个数，x用来存放横坐标，y用来存放纵坐标
{
	int i;
	float step;

	step=fabs(a-b)/(n-1);//步长
	for(i=0;i<n;i++)
	{
		x[i]=a+i*step;  //计算横坐标
		y[i]=f(x[i]);  //计算纵坐标

	}
	return 0;

}
/*****定义参与运算的数学函数*****/
float f1(float x)
{
	float y1;
	y1=log(x); //对数函数
	return (y1);


}