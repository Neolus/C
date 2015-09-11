/*本文件实现梯度法求解极小值算法*/
#include <math.h>
#include <stdio.h>


/*****函数声明******/
double* grad(double (*f)(double,double),double *p,double a,double b,double tol,FILE *fp);  //梯度函数求极值
void solveS(double x,double y,double *s);  //求解搜索向量
double gema(double ga,double *s,double *t);//gama对应数学表达式
double golden(double (*f)(double,double *,double *),double a,double b,double tol,double *s,double *p,FILE *fp); //黄金搜素解单变量极值
double f(double x,double y); //待求解数学函数
double fx(double x,double y);//偏x
double fy(double x,double y);//偏y


void main()
{
	double p[2]={15,-4}; //搜索起点
	double A,B,tol,res;
	int i;
	double *D=new double [2];
	A=-100;
	B=100;
	tol=1e-6;  //实验精度

	FILE *fp;
	fp=fopen("result.txt","w+");

	D=grad(f,p,A,B,tol,fp); //调用梯度函数求极值


	for(i=0;i<2;i++)
	{
		printf("%0.8f\n",D[i]);
	}

	res=sqrt(f(15,-4)); //求解最短距离
	printf("res is %0.8f\n",res);


	fclose(fp);
	getchar();

}


/***定义梯度函数求解极值函数**********/
double* grad(double (*f)(double,double),double *p,double a,double b,double tol,FILE *fp) //f数学公式，p搜索起点的向量，a、b用于求解黄金分割时的范围、tol实验精度、fp指向文本
{
	double s[2],sa,ta,r;
	double hmin;
	int i;
	solveS(p[0],p[1],s);  //求解搜索方向向量
	hmin=golden(gema,a,b,tol,s,p,fp); //求解gama极小值

	for(i=0;i<2;i++)
	{
		p[i]=p[i]+hmin*s[i];  //计算新的搜索点
		printf("%0.8f\t",p[i]);
		fprintf(fp,"%0.8f\t",p[i]);	
	}

	r=sqrt(f(p[0],p[1])); //求出到定点的距离
	printf("%0.8f\n",r);
	fprintf(fp,"%0.8f\n",r);


	sa=sqrt(s[0]*s[0]+s[1]*s[1]); 
	ta=hmin*sa; //计算变化的距离



	if(fabs(ta)<10*tol)  return p;  //如果变化距离小于精度，结束运算

	 p=grad(f,p,a,b,tol,fp); //否则继续搜索。

	 return p;

}


/***定义求解搜索方向函数Sk*********/
void solveS(double x,double y,double *s) //在(x,y)处求解，s为存放搜索向量
{
	double a[2],A;
	a[0]=fx(x,y); //偏x值
	a[1]=fy(x,y);  //偏y值
	A=sqrt(a[0]*a[0]+a[1]*a[1]);

	s[0]=-a[0]/A;   //归一化
	s[1]=-a[1]/A;
}


/******定义黄金分割函数*************/
double golden(double (*f)(double,double *,double *),double a,double b,double tol,double *s,double *p,FILE *fp) //f为数学函数，i为对应题目0-3对应a-d，a为左端点，b为右端点，tol为精度，fp指向文本
{
	double r;
	double a1,b1,c,d,length;
	double tc,td,z;
	r=0.5*(-1+sqrt(5.));
	length=b-a; 
	c=a+(1-r)*length;  //计算ck
	d=b-(1-r)*length;  //计算dk
	tc=f(c,s,p); //计算两点对应的函数值
	td=f(d,s,p);

	if(tc<td)  //判断下一个ak，bk的取值
	{
		a1=a;
		b1=d;
	}
	else
	{
		a1=c;
		b1=b;
	}


	if(fabs(a1-b1)>tol)  //如果没有满足精度，继续细分
	{
		z=golden(f,a1,b1,tol,s,p,fp);
	}

	else
	{
		z=0.5*(a1+b1);  //取最后两点的中点为极值点

	}


	return z;

}


/***需要求解的数学函数**********/

double f(double x,double y)
{
	double s;
	s=(x-2)*(x-2)+(y-3)*(y-3)+(x*x+y*y-1)*(x*x+y*y-1);
	return s;
}
/****x的偏导*******/
double fx(double x,double y)
{
	double s;
	s=2*(x-2)+4*x*(x*x+y*y-1);
	return s;
}
/***y的偏导******/
double fy(double x,double y)
{
	double s;
	s=2*(y-3)+4*y*(x*x+y*y-1);
	return s;
}

/**定义求解gama变换表达式*******/
double gema(double ga,double *s,double *t) //在ga处求值，s搜索方向向量，t现在的搜索点
{
	double x,y,res;
	x=t[0]+ga*s[0]; //变换坐标
	y=t[1]+ga*s[1];

	res=f(x,y);  //求解距离
	return res;
}
