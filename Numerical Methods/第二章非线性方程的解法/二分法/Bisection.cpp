/*本文件实现解非线性方程的二分法*/

#include <stdio.h>         //输入输出函数
#include <math.h>         //常用数学函数
#include <float.h>      //对应于FLT_MIN的函数

double Bisection (double a0  ,double b0,double tol,int max);    //函数声明，二分法函数

void main ()              //主函数
{

	double a0  , b0,root;                                      //定义某些变量
	printf ("Please input area []=" );                          //输出提示输入二分法的两个端点
	scanf("%lf %lf",&a0,&b0);                                   //输入两个端点值，并存放在a0、b0

	root=Bisection(a0,b0,1e-8,1000);                          //调用二分法函数，a0，b0表示二分法的两个端点。1e-10为误差及相对误差判断值，1000为运算最大次数
//	printf ("The root is %0.10f",root);                        //输出最后的根，“%0.10f”保留10位小数
	getchar();                                            //保持运行窗口
	getchar();
}



double Bisection (double a0,double b0,double tol,int max)      //二分法函数，并指明各个参数，a0，b0表示二分法的两个端点，tol为误差及相对误差判断值，max为计算最大次数
{
	double f(double x);        //函数声明，f（x）为需要参与实际运算的数学函数                      
	int i;
	double *a=new double;          //定义a b c三个指针，用来存放端点值。c为a b中点。
	double *b=new double;           
	double *c=new double;
	double m=f(c[0]);                     //m用来存放f（c）的值，并初始化
	a[0]=a0;                              //对数组a赋初值
	b[0]=b0;                                //对数组b赋初值
	if (f(a[0])*f(b[0])>0)              //判断如果给定的两个端点的函数值同号，则输出无解提示。
	
	{
	 printf ("There is no root in this area ");
	}
	else{                                //端点函数值异号，则执行二分法算法
	    for (i=0;i<=max;i++)             //for循环多次计算
	     {
		  c[i]=(a[i]+b[i])/2;            //每次计算中点值
			if(f(a[i])*f(c[i])>0)        //如果中点值与a的函数值同号
			{
				a[i+1]=c[i];           //则a的下一项为当前的c值
				b[i+1]=b[i];           //b则保持不变
				m=f(c[i]);            //将中点的函数值存放在m
			}
			else b[i+1]=c[i],a[i+1]=a[i];   // 如果中点与端点a异号则b的下一项为当前的c，a则保持不变
			printf (" c[%d] is %0.10f\n ",i,c[i]);   //输出每一项c
			printf (" f(c[%d]) is %0.10f \n",i,m);      //输出每一项中点的函数值，方便观察
		    if (fabs(m)<tol) break;                     //当中点的函数值低于预设精度时，停止循环，终止计算
			
	      }
		  printf ("The root is %0.10f",c[i-1]);                        //输出最后的根，“%0.10f”保留10位小数
          return c[i-1];                     //返回，中点值
	     }


}

double f(double x)                           //定义参与运算的数学函数
{       float eps=FLT_MIN;                     //eps最小浮点数
		double f,p=300;                  //定义变量，p为每月支付的金额300
		f=(p/(x/12+eps))*(pow((1+x/12),240)-1);           //实际数学函数
		f=f-500000;
		return f;                     //返回函数值
}

