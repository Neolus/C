/*本文件实现了最小二乘拟合曲线算法*/
#include <stdio.h>

float A,B;    //定义全局变量A、B，分别为y=Ax+B中的系数
float lsline(float *x,float *y,int N);      //函数声明，lsline为最小二乘法线性拟合函数

void main()
{
	int i,n; 
	printf("please input the number of digits\n n= "); //提示输入点的个数
	scanf("%d",&n);           //输入点数，存入n
	float *xk=new float [n];   //定义一维指针，xk存放输入数据的横坐标
	float *yk=new float [n];   //定义一维指针，yk存放输入数据的纵坐标
	printf("please input X[k]\n");
	for(i=0;i<n;i++)
	{
	scanf("%f",&xk[i]);  //输入数据的横坐标
	}
	printf("please input Y[k]\n");
	for(i=0;i<n;i++)
	{
	scanf("%f",&yk[i]);   //输入数据的纵坐标
	}
	for(i=0;i<n;i++)
	{
	printf("%f\t%f\n",xk[i],yk[i]);  //输出显示横纵坐标
	}
	lsline(xk,yk,n);   //调用最小二乘函数

	printf("A is %f\nB is %f",A,B);   //输出显示最终计算的值A、B

	delete []xk;
	delete []yk;
	getchar();
	getchar();
	getchar();   //保持cmd窗口
}


/*********定义最小二乘线性函数*************************/
float lsline(float *x,float *y,int N)   //函数名lsline，*x为输入点的横坐标，*y为纵坐标，n为输入的点的个数
{
	int i;
	float sx,sx2,sy,sxy;    //定义变量参与计算
	sx=0;
	sx2=0;
	sy=0;
	sxy=0;
	for(i=0;i<N;i++)  //循环求和式
	{
	sx2=sx2+x[i]*x[i];   //sx2为x^2的和
	sx=sx+x[i];    //sx为x的和
	sy=sy+y[i];    //sy为y的和
	sxy=sxy+x[i]*y[i];   //sxy为xy的和
	}


	A=(N*sxy-sx*sy)/(N*sx2-sx*sx);   //由最小二乘公式计算出A
	B=(sy-sx*A)/N;  //计算出B

	return 0;  //不需要返回值

}