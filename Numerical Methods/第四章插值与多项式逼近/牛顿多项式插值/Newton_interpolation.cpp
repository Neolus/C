/*本文件实现牛顿多项式插值算法*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>         //结果写入文本，头函数

float Newinter(float*x,float *y,float c,int n);  //函数声明，Newinter为牛顿插值函数

void main()
{

	int N=6; //插值点的个数
	float X[6]={1,2,3,4,5,6};  //插值点的横坐标
	float Y[6]={66,66,65,64,63,63}; //插值点的纵坐标
	float step,z,y,y_mean,L,y0;
	int k,max;
	   FILE*fp;//定义指向文件的指针变量fp
		if((fp=fopen("point3.txt","w"))==NULL)//打开输出文件并使fp指向该文件
		{
			printf("cannot open the file\n");//如果打开出错，这输出打开失败
			exit(0);//终止程序
		}


		y0=0;
		step=0.0001;   //步长，x轴上样本点的距离
		L=X[N-1]-X[0];  //求出最远两点的距离
		max=int((L/step));   //计算出所有样本点的个数


		for(k=0;k<=max;k++)   //循环，计算出每点的对应的拉格朗日多项式的值的和
			{
			   z=X[0]+k*step;
			   printf("%f\t",z);
	   			fprintf(fp,"%f\t",z);   //将横坐标输入文本
			   y=Newinter(X,Y,z,6);
			   printf("%f\n",y);
	   			fprintf(fp,"%f\n ",y);  //将纵坐标输入文本
			   y0=y0+y;     //叠加求出和
			}

	fclose(fp);//关闭fp。
//	 printf("%f\n",y);
	y_mean=y0/(max+1);  //求出平均值
	printf("%f",y_mean);


	getchar();
}

//定义牛顿多项式插值函数
float Newinter(float*x,float *y,float c,int n)   //*x为样本点X坐标，*y为样本点Y坐标，c为变量x，n为点的总个数
{
	float **a;     //a为差商表系数
	float *p=new float [n+1];
	float temp=1;     //temp为中间变量
	float P=0;
	int i,j;
	a=new float *[n];   //指定二维指针大小
		for(i=0;i<n;i++)
		{
		a[i]=new float [n];
		}

		for (i=0;i<n;i++)   //初始化二维指针，全0矩阵
	      {
		    for(j=0;j<n;j++)
			{
			a[i][j]=0;
			}
		}

	for (i=0;i<n;i++)     //计算差商系数
		{
			a[i][0]=y[i];  //第一列直接得出
	        for(j=1;j<=i;j++)
			{
				if (i==0) break;
				a[i][j]=(a[i][j-1]-a[i-1][j-1])/(x[i]-x[i-j]);   
		   }
	}

	/*
	 FILE*fp1;//定义指向文件的指针变量fp
		if((fp1=fopen("cofficent.txt","w"))==NULL)//打开输出文件并使fp1指向该文件
		{
			printf("cannot open the file\n");//如果打开出错，这输出打开失败
			exit(0);//终止程序
		}

     for (i=0;i<n;i++)
	      {
		    for(j=0;j<n;j++)
			{
			printf("%f\t",a[i][j]);     
			fprintf(fp1,"%f\t",a[i][j]);  //将差商矩阵，写入文本
			
			}
				printf("\n");
				fprintf(fp1,"\n");
		}
	
	 fclose(fp1);//关闭fp。
	 */
	
	for (i=0;i<n;i++)   //利用循环，计算牛顿多项式的具体对应的数值
	  {
		temp=1; //初始化
		for(j=0;j<i;j++)
		{
			if (i==0) break;
		    temp=temp*(c-x[j]);   //乘积项
		}
		P=P+a[i][i]*temp;  //P为牛顿多项式的带入x的值
		  
    	}
	return (P);
/*   //如果想要用每一项牛顿多项式计算的程序，不推荐，参数设置极其复杂
	  p[0]=a[0][0];
	for (i=0;i<n-1;i++)
	{
		for(j=0;j<=i;j++)
		{
			if (i==0) break;
		temp=temp*(c-x[j]);
		}

	p[i+1]=p[i]+a[i+1][i+1]*temp;
	temp=1;
	}
	return (p[5]);
*/

	for(i=0;i<n;i++)
		{
		delete []a[i];
		}
	delete []a;
	delete []p;
}

