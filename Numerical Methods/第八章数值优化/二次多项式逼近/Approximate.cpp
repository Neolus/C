#include <stdio.h>
#include <math.h>

/******函数声明*************/
double inith(double a,double b);  //初始化h
double findpoint(double (*f)(double,int),int i,double p0,double h,double tol,FILE *fp); //二次逼近函数
double hmin(double (*f)(double,int),int i,double p0,double p1,double p2,double h); //计算hmin
double f(double x,int i); //所有数学函数
double fa(double x); //a到d的数学公式
double fb(double x);
double fc(double x);
double fd(double x);




void main()
{
	int i;
	double tol=1e-6;
	double res,ff,h,p0;


	double A[4]={-2.4,0.8,0.5,1};  //搜索左端点
	double B[4]={-1.6,1.6,2.5,5}; //搜索右端点

	FILE *fp;  //指向文本
	fp=fopen("result.txt","w+");

	//计算4个题目
	for(i=0;i<4;i++)
	{
		printf("the anser of question %c\n",97+i);
		h=inith(A[i],B[i]); //初始化h
		p0=(A[i]+B[i])/2;  //计算区间中点
		res=findpoint(f,i,p0,h,tol,fp);  //调用寻找点函数求解近似值p
		ff=f(res,i);  //计算f(p)
		printf("%0.7f\t%0.7f\n",res,ff);
		fprintf(fp,"%0.7f\t%0.7f\n",res,ff); 
	}

	fclose(fp); //关闭文本
	getchar();



}

/*****定义初始化h函数**********/
double inith(double a,double b) //a为左端点，b为右端点
{
	double h;
	if(a+1<b)  h=1;  //根据a、b情况初始化h
	else h=0.5;
	return h;
}


/****定义二次逼近函数*********/
double findpoint(double (*f)(double,int),int i,double p0,double h,double tol,FILE *fp) //f数学函数，i对应题号，p0搜寻起点，h步长，tol精度，fp指向文本
{
	double p1,p2;
	double f0,f1,f2;
	double m;

	m=f(p0+0.00001,i)-f(p0-0.00001,i);  //计算p0点的导数的符号

	if(m>0)  h=-fabs(h); //决定h的正负
	else h=fabs(h);


	p1=p0+h;
	p2=p0+2*h;

	f0=f(p0,i); //三点处的函数值
	f1=f(p1,i);
	f2=f(p2,i);

	printf("P are %0.7f\t%0.7f\t%0.7f\n",p0,p1,p2);
	printf("f are %0.7f\t%0.7f\t%0.7f\n",f0,f1,f2);

	fprintf(fp,"%0.7f\t%0.7f\t%0.7f\n",p0,p1,p2);

	if((f0>f1)&&(f1>f2))  //f(p0)最大
	    {
		  h=2*h;  //步长加倍
		 p0=findpoint(f,i,p0,h,tol,fp);  //继续寻找3点
	    }
	if(f0<f1)  //f(p0)最小
		{
			h=h/2;  //步长减半
		   p0=findpoint(f,i,p0,h,tol,fp);  //继续寻找3点
	    }
	else   //满足条件的三个点
	{    
	  h=hmin(f,i,p0,p1,p2,h);  //计算hmin
	  p0=p0+h;  //改变p0
	    if(fabs(h)<tol) //达到精度要求
	  {   printf("h is <tol %0.7f\n",h);
		  return p0;  //返回最后的p0
	  }
	  p0=findpoint(f,i,p0,h,tol,fp);  //没有达到精度，继续寻找点
	}

	return p0;
}


/****定义hmin的计算函数*******/
double hmin(double (*f)(double,int),int i,double p0,double p1,double p2,double h)
{
	h=h*(4*f(p1,i)-3*f(p0,i)-f(p2,i))/(4*f(p1,i)-2*f(p0,i)-2*f(p2,i));
	return h;

}


/*****定义数学公式函数*********/
double f(double x,int i)   //在x点求值，i为对应题目0-3对应a-d
{
	double y;
	if(i==0) y=fa(x);
    if(i==1) y=fb(x);
	if(i==2) y=fc(x);
	if(i==3) y=fd(x);
	return y;
}

/***a题数学函数*******/
double fa(double x)
{
  double y;

  y=exp(x)+2*x+x*x/2;
  return y;
}

/***b题数学函数*******/
double fb(double x)
{
  double y;
  y=-sin(x)-x+x*x/2;
  return y;
}

/***c题数学函数*******/
double fc(double x)
{
  double y;
  y=x*x/2-4*x-x*cos(x);
  return y;
}

/***d题数学函数*******/
double fd(double x)
{
  double y;
  y=pow(x,3)-5*x*x+23;
  return y;
}


