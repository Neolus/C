/*本文件实现了线性方程组的高斯—赛德尔迭代算法*/

#include <stdio.h>
#include <math.h>
#include <float.h>   //对应最小浮点数
#include <stdlib.h>         //结果写入文本，头函数
#define N 50

void main()
{
float Seidel(float**a,float*b,float *p,float tol,int n,int max);   //函数声明，seidel为高斯—赛德尔迭代求解函数
	int i,j;
	float **A;    //定义二维指针，用来存放系数矩阵A
	float *B=new float[N]; //一维指针，存放方程右边的向量
	float *P=new float[N];  //初始猜测值
	A=new float *[N];    //指定二维数组指针大小
	  for(i=0;i<N;i++)
	   {
	   A[i]=new float[N];
	   }


	for(i=0;i<N;i++)   //初始化B
	{
		B[i]=5;
		P[i]=1;  //初始猜测值全为1
	 for(j=0;j<N;j++)   //初始化系数矩阵A
	 {
	   if((j==i-1)&(i>0))  A[i][j]=-2;
	   else if(j==i) A[i][j]=12;
	   else if (j==i+1) A[i][j]=-2;
	   else A[i][j]=0;
	 }
	}


  Seidel(A,B,P,1e-6,N,20);  //调用赛德尔函数求解方程组

  delete []P;
  delete []B;
 for(i=0;i<N;i++)
   {
	  delete [] A[i];
   }
 delete []A;

getchar();
}

float Seidel(float**a,float*b,float *p,float tol,int n,int max)  //函数声明，Seidel为高斯—赛德尔迭代求解，a为系数矩阵，b为方程右边的列向量。p为初始猜测值，tol为实验精度，n为方程组维数，max为最大迭代次数 
{
	int i,j,k;
	float temp=0,max1,max2;  //三个中间变量
	float *x=new float[n];    //x用来存放方程组的解
	float *err=new float[n];  //err为绝对误差
	float *rel=new float[n];  //rel为相对误差
	float xpre,eps=FLT_MIN;;  //eps最小浮点数
	for(i=0;i<n;i++)
	{
	x[i]=p[i];
	}
	FILE *fp;//定义指向文件的指针变量fp
	if((fp=fopen("X.txt","w"))==NULL)//打开输出文件并使fp指向该文件
     {
	printf("cannot open the file\n");//如果打开出错，这输出打开失败
    exit(0);//终止程序
     }


	for(k=0;k<max;k++)
	{
		printf("K is %d\n",k);   //输出k观测迭代次数
		for(i=0;i<n;i++)
			{
				xpre=x[i];   //临时存放
				for(j=0;j<(n&i+1);j++)
				{
				if(i==j) continue;
				temp+=a[i][j]*x[i];
				}
			  x[i]=(b[i]-temp)/a[i][i];  //计算每一次的x
			  err[i]=fabs(xpre-x[i]);   //计算绝对误差
			  rel[i]=err[i]/fabs(x[i]+eps);   //计算相对误差
			  temp=0;     //中间变量归零
				printf("x[%d]=%f  ",i,x[i]);    //输出每一次的x，err，rel
				printf("err[%d]=%f  ",i,err[i]);
				printf("rel[%d]=%f\n",i,rel[i]);
			}
		    printf("\n");
		   max1=err[0];
		   max2=rel[0];
			 for(i=0;i<n;i++)   //找到最大绝对误差，最大相对误差
				{
				   if(max1<err[i+1])  max1=err[i+1];
				   if(max2<rel[i+1])  max2=rel[i+1];
				 }
				 if(max1<tol||max2<tol) break;	  //当最大绝对误差或者最大相对误差小于实验精度，跳出循环，结束计算
	}

	for(i=0;i<n;i++)
	{
	fprintf(fp,"%f\n",x[i]);     //将最终结果输入指定文件
	}

	fclose(fp);   //关闭文本
	delete []x;
	delete []err;
	delete []rel;

	return 0;   //无参数需要返回
}
