/*本文件实现自适应积分*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define pi 3.14159265359


/******函数声明*************/
	double adpt(double (*f)(double,int),int i,double a,double b,double tol,FILE *fp); //自适应积分函数
	double simprl(double (*f)(double,int),int i,double a,double b); //辛普森积分函数
	double f(double x,int i);  //数学函数
	double fa(double x); //a-f的数学表达式
	double fb(double x);
	double fc(double x);
	double fd(double x);
	double fe(double x);
	double ff(double x);

void main()
{

	double A[7]={0,0,0.04,0,1/(2*pi),0};  //积分下限
	double B[7]={3,3,1,2,2,2};  //积分上限，与A一一对应

	double res;
	int k;

	FILE*fp;//定义指向文件的指针变量fp
	fp=fopen("result.txt","w+");

	for(k=0;k<6;k++)  //循环一次计算6个题
	{
		printf("the answer of %c\n",97+k);
		fprintf(fp,"the answer of %c\n",97+k);
		res=adpt(f,k+1,A[k],B[k],1e-5,fp);  //调用自适应积分函数计算
		printf("%f\n",res);  //输出结果
	    fprintf(fp,"%0.8f\n",res);  //写入文本
	}

	fclose(fp);//关闭fp。
	getchar();


}


/********定义自适应积分函数****************************/
double adpt(double (*f)(double,int),int i,double a,double b,double tol,FILE *fp) //*f数学公式，i对应的题号，a积分下限，b积分上限，tol区间上的容差，*fp指向文本
{

	double c,h,a1,b1,a2,b2,eps,err;
	double s,s1,s2,temp=0,t1;
	double v,v1,v2;
	c=(a+b)/2;  //中点
	h=(b-a)/2;  //步长
	a1=a;  //区间分为两段
	b1=c;
	a2=c;
	b2=b;

    s=simprl(f,i,a,b);  //计算整个区间的积分
	s1=simprl(f,i,a1,b1);  //子区间1的积分
	s2=simprl(f,i,a2,b2);  //子区间2的积分
	err=fabs(s-(s1+s2))/10;  //计算整体积分和分段积分的误差

	if(err<tol)   //误差小于容差，结束运算，返回两个分区间积分之和
	{
		t1=s1+s2;
	    printf("%f\t%f\t%0.12f\t%0.12f\t%0.9f\n",a,b,err,tol,t1);  
	    fprintf(fp,"%f\t%f\t%0.12f\t%0.12f\t%0.9f\n",a,b,err,tol,t1);
		temp=temp+t1;
		return (t1);
	}
	else  //如果没有达到要求
	{
		eps=tol/2;  //容差减半
		v1=adpt(f,i,a1,b1,eps,fp);  //在两个子区间在进行子适应积分
		v2=adpt(f,i,a2,b2,eps,fp);
		v=v1+v2;   
		return v;  //返回两者之和
	}

}


/****定义辛普森积分函数********************/
double simprl(double (*f)(double,int),int i,double a,double b)  //*f数学公式，i对应题号，a为积分下限，b为积分上限
{

	double c,h;
	double s;
	c=(a+b)/2;  //中点
	h=(b-a)/2;  //步长
	s=h/3*(f(a,i)+4*f(c,i)+f(b,i));  //辛普森积分计算公式

	return s;
}



/***定义要求解的数学函数**************/
double f(double x,int i)   //在x点求值，i代表第几个题的数学公式
{
	double y=0;

	if(i==1) y=fa(x);
	if(i==2) y=fb(x);
	if(i==3) y=fc(x);
	if(i==4) y=fd(x);
	if(i==5) y=fe(x);
	if(i==6) y=ff(x);
	return y;
}

/*****a题数学函数****************/
double fa(double x)
{
	double y;
	y=sin(2*x)/(1+pow(x,5));
	return y;
}

/*****b题数学函数****************/
double fb(double x)
{
	double y;
	y=sin(4*x)*exp(-2*x);
	return y;
}


/*****c题数学函数****************/
double fc(double x)
{
	double y;
	y=1/sqrt(x);
	return y;
}

/*****d题数学函数****************/
double fd(double x)
{
	double y;
	y=1/(x*x+0.1);
	return y;
}

/*****e题数学函数****************/
double fe(double x)
{
	double y;
	y=sin(1/x);
	return y;

}

/*****f题数学函数****************/
double ff(double x)
{
	double y;
	y=2*sqrt(x)-x*x;
	return y;
}


