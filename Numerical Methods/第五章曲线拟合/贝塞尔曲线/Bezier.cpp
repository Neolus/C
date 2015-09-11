/*本文件实现贝塞尔曲线的拟合算法*/


#include <math.h>  //数学函数头文件
#include <stdio.h>  //输入输出头文件
#include <stdlib.h>         //结果写入文本，头函数

float bezier(float *a,float t,int n);  //函数声明，bezier函数为贝塞尔插值函数

void main()
{

	/*****初始化需要的数组及参数********/
	const  int n1=4; //第一段，4个点
	float X1[n1]={0,1,1,3};
	float Y1[n1]={0,2,1,0};
	const  int n2=5;  //第二段，5个点
	float X2[n2]={3,4,5,6,7};
	float Y2[n2]={0,-1,-2,1,0};
	const int n3=4;   //第三段，4个点
	float X3[n3]={7,4,2,0};
	float Y3[n3]={0,-3,-1,0};


	FILE*fp;//定义指向文件的指针变量fp
		if((fp=fopen("XY1.txt","w"))==NULL)//打开输出文件并使fp指向该文件
		{
			printf("cannot open the file\n");//如果打开出错，这输出打开失败
			exit(0);//终止程序
		}
	FILE*fp1;//定义指向文件的指针变量fp
		if((fp1=fopen("XY2.txt","w"))==NULL)//打开输出文件并使fp指向该文件
		{
			printf("cannot open the file\n");//如果打开出错，这输出打开失败
			exit(0);//终止程序
		}
    FILE*fp2;//定义指向文件的指针变量fp
		if((fp2=fopen("XY3.txt","w"))==NULL)//打开输出文件并使fp指向该文件
		{
			printf("cannot open the file\n");//如果打开出错，这输出打开失败
			exit(0);//终止程序
		}


	int i, max1;
	float T=0;
	float step=0.01;
	max1=1/step; //计算循环次数
	float x,y;
 

	/******循环计算t【0,1】**********/
	for(i=0;i<=max1;i++)
	{
		/****第一段曲线******/
		T=i*step;
		x=bezier(X1,T,n1);  //调用贝塞尔函数，计算t从0到1的所有对应的x
		y=bezier(Y1,T,n1);   //调用贝塞尔函数，计算t从0到1的所有对应的x
	    printf("%f\t%f\n",x,y);  //输出x，y
		fprintf(fp,"%f\t%f\n",x,y); //输入文本fp，用来绘图


		/****第二段曲线******/
	    x=bezier(X2,T,n2);  
		y=bezier(Y2,T,n2);
	    printf("%f\t%f\n",x,y);
		fprintf(fp1,"%f\t%f\n",x,y);


		/****第三段曲线******/
	    x=bezier(X3,T,n3); 
		y=bezier(Y3,T,n3);
	    printf("%f\t%f\n",x,y);
		fprintf(fp2,"%f\t%f\n",x,y);

	}

  fclose(fp);//关闭fp。
  fclose(fp1);
  fclose(fp2);

	getchar();


}



/*****定义函贝塞尔插值函数*********/
float bezier(float *a,float t,int n)  //a为输入的控制点数据，t为0到1的一个值，与x对应，n为输入点的个数
{
	n=n-1;  //最高阶为点数减1
	float Bi(float t,int i,int n); //函数声明，Bi为具体i、n对应的伯恩斯坦多项式的值

	float s=0; // 初始化求和项
	int i;

	for (i=0;i<=n;i++)
	{
		s=s+Bi(t,i,n)*a[i]; //贝塞尔曲线公式
	}

	return (s);  //返回最后的计算结果

}


/***定义伯恩斯坦多项式*******/
float Bi(float t,int i,int n)  //t为具体的0到1的值，n为阶数，i为i个多项式
{

	float facterial(int n);  //函数声明 facterial为阶乘函数
	float B;  
	float cni;
		 cni=facterial(n)/(facterial(i)*facterial(n-i)); //计算二项式系数
		 B=cni*pow(t,i)*pow(1-t,n-i);  //计算伯恩斯坦多项式的值
		return (B);  //返回计算值
} 


/***定义阶乘函数，用来算伯恩斯坦多项式*******/
float facterial(int n) // 为n的阶乘
{
	int i;
	float f=1;  //乘积项初始化为1

	if(n==0) f=1; //0的阶乘为1
	else
	{
		for(i=1;i<=n;i++)  //计算非0的阶乘
		{
			f=f*i;
	
		}
	}
	return (f); //返回阶乘值
}