/*本文件实现三角多项式插值算法*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>         //结果写入文本，头函数
#define pi 3.1415927 //定义pi
 float tpcof(float *x,float *y,float z,int M,int N);  //函数声明，tpcof三角多项式函数

void main()
{
   const int n=24;  //n为数据点的个数
   float X[n]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24}; //时间
   float Y[n]={58,58,58,58,57,57,57,58,60,64,67,68,66,66,65,64,63,63,62,61,60,60,59,58}; //温度

   int i,max1;
   float step,x,x1,step1;  
 
   step=0.1; //x的步长0.1
   max1=(X[n-1]-X[0])/step; //计算出参与循环的次数

   step1=(2*pi)/(23); //三角多项式的-pi到pi的点x[k]

   float *t=new float [max1+1];
   float *X1=new float [max1+1];

   FILE *fp;//定义指向文件的指针变量fp
		if((fp=fopen("tri.txt","w"))==NULL)//打开输出文件并使fp指向该文件
		 {
		printf("cannot open the file\n");//如果打开出错，这输出打开失败
		exit(0);//终止程序
		 }

		 for (i=1;i<=n;i++)
		 {
		 	X1[i]=-pi+i*step1; //-pi到pi取等距点
		 
		 }

/******循环调用三角多项式函数，计算x=1到24时刻之间的温度*********/
   for (i=0;i<=max1;i++)
	   {
		    x=X[0]+i*step;  //计算中的时间x
			x1=-pi+i*step*step1; //计算三角多项式系数aj，bj的-pi到pi的等间距的点
			
           t[i]=tpcof(X1,Y,x1,7,n); //调用三角多项式函数

		   printf("%f\t%f\n",x,t[i]);
           fprintf(fp,"%f\t%f\n",x,t[i]);//将float型变量x，t[i]]输出到fp指向的文件中。
	   }
   fclose(fp); //关闭文本

   delete []t;
   delete []X1;
   getchar();
}



/********定义三角多项式函数****************/
float tpcof(float *x,float *y,float z,int M,int N) //x为-pi到pi的等距点，y为对应点的温度，z为某个具体时刻，M为三角多项式的阶数，N为输入点的个数
{
	N=N-1;  //计算时，N取点数少1
	float *a=new float [M+1]; //定义a[j]
	float *b=new float [M+1]; //定义b[j]

	float s1=0,s2=0,s3=0;
	int j,k;
	float T;


	 for(k=1;k<=N;k++)
		 {
		  s1+=y[k];
		 }
	 a[0]=s1*2/N;       //单独计算a[0]
	 printf("%f\n",a[0]);

	for (j=1;j<=M;j++)   //循环计算a[j],b[j]
	{
		s1=0;  //初始化中间变量
		s2=0;
	  for(k=1;k<=N;k++)   //求和项
	  {
	  s1=s1+y[k]*cos(j*x[k]);
	  s2=s2+y[k]*sin(j*x[k]);
	  }
	  a[j]=s1*2/N; //计算a[j]
	  b[j]=s2*2/N;   //计算b[j]
	  printf("%f\t%f\n",a[j],b[j]);

	  s3=s3+a[j]*cos(j*z)+b[j]*sin(j*z);   //T中的后面的求和项,为z时刻的温度
	}
	T=a[0]/2+s3;  //T的计算式

	delete []a;
	delete []b;
	return (T);   //返回计算的值

}
