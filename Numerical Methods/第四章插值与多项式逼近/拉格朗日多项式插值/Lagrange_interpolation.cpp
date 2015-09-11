/*本文件实现拉格朗日多项式逼近算法*/

#include <stdio.h>
#include <stdlib.h>         //结果写入文本，头函数
   
double lagrange(double *x,double *y,double z,int n);   //函数声明，lagrange为拉格朗日多项式插值函数

void main()
{

	 const int N=6;
	 int k,max;
	double X[N]={1,2,3,4,5,6};    //定义自变量数组
	double Y[N]={66,66,65,64,63,63};   //定义因变量数组
	double step,z,y,y_mean,L,y0;   
	y0=0;
	step=0.001;   //步长，x轴上样本点的距离
	L=X[N-1]-X[0];  //求出最远两点的距离
	max=int((L/step));   //计算出所有样本点的个数
	
		   FILE*fp;//定义指向文件的指针变量fp
		if((fp=fopen("point3.txt","w"))==NULL)//打开输出文件并使fp指向该文件
		{
			printf("cannot open the file\n");//如果打开出错，这输出打开失败
			exit(0);//终止程序
		}

	for(k=0;k<=max;k++)   //循环，计算出每点的对应的拉格朗日多项式的值的和
	{
	   z=X[0]+k*step;
	   	fprintf(fp,"%f\t",z);   //将横坐标输入文本
	   y=lagrange(X,Y,z,6);
	   	fprintf(fp,"%f\n ",y);  //将纵坐标输入文本
	   y0=y0+y;     //叠加求出和
	}
	fclose(fp);//关闭fp。
	 printf("%f\n",y);
	y_mean=y0/(max+1);  //求出平均值
	printf("%f",y_mean);

	getchar();
}

//定义函数，拉格朗日插值多项式
double lagrange(double *x,double *y,double z,int n)  // *x为横坐标样本点数组，*y为对应的值数组，z为其中未知数，n为点的个数
{
	int i,j;
	double *L=new double[n];   //定义拉格朗日多项式系数
	double P,a,b;
	P=0;
	for(i=0;i<n;i++)   //计算每一个系数
	{ 
	     a=1;   //初始化中间变量
		 b=1;
	  for(j=0;j<n;j++) //for循环迭代计算出乘积项
	  {  
		  if (i==j) continue;
		  a=a*(z-x[j]);     
	      b=b*(x[i]-x[j]);
	  }
	  L[i]=a/b; 
	}
	printf("%f\t",z);

	for(i=0;i<n;i++)  //循环计算出z值带入拉格朗日多项式的函数值
	{
	    P+=y[i]*L[i];   
	}
	printf("%f\n",P);

	delete []L;

	return (P);      //返回最终的计算结果
}