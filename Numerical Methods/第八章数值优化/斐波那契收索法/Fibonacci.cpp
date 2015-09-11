/*本文件实现斐波那契搜索法*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/***函数声明**********/
float fibona(float (*f)(float,int),int i,float a,float b,int n,FILE *fp);  //斐波那契函数
float findn(float (*f)(int),float a,float b,float tol);  //寻找需要参与计算的N
float F(int n);  //求解斐波那契数
float f(float x,int i); //所有数学函数
float fa(float x); //a到d的数学公式
float fb(float x);
float fc(float x);
float fd(float x);


void main()
{
	int i,N;
	float tol=1e-6;
	float res,ff;


	float A[4]={-2.4,0.8,0.5,1};  //搜索左端点
	float B[4]={-1.6,1.6,2.5,5}; //搜索右端点

	FILE *fp;
	fp=fopen("result.txt","w+");

	//一次性计算4题
	for(i=0;i<4;i++)
	{
		printf("the answer of %c\n",97+i);
		N=findn(F,A[i],B[i],tol); //求解N
		res=fibona(f,i,A[i],B[i],N,fp); //调用斐波那契函数，求解
		ff=f(res,i);

		printf("%f\t%f\n",res,ff); //输出最后的中点和函数值
		fprintf(fp,"%f\t%f\n",res,ff);//写入文本
	}
	fclose(fp);//关闭文本
	getchar();

}


/****定义斐波那契方法函数***********/
float fibona(float (*f)(float,int),int i,float a,float b,int n,FILE *fp) //f为数学函数，i对应题目号，a左端点，b右端点，n为最大的斐波那契数的对应的N，fp指向文本
{
	float c,d;
	int j;
	float r,e=0.01,z;

	for(j=n;j>2;j--)//循环求解所有的区间
	{  
		
		r=F(j-1)/F(j);
		if(j==3) c=a+(r-e)*(b-a); //j=3单独求解c
		else c=a+(1-r)*(b-a); //求解c
	    d=a+r*(b-a); //求解d

	  	printf("%f\t%f\t%f\t%f\n",a,c,d,b);
		fprintf(fp,"%f\t%f\t%f\t%f\n",a,c,d,b); 

	  if(f(c,i)>f(d,i))  //判断下一个区间的取值
	  {
		  a=c;
	  }
	  else
	  {
		  b=d;
	  }
	}

	printf("%f\t%f\n",a,b);//输出最后的区间
	fprintf(fp,"%f\t%f\n",a,b);

	z=(a+b)/2;  //求中点
	return z; //返回中点值
}



/**定义求解N函数*************/
float findn(float (*f)(int),float a,float b,float tol)
{
	float y;
	int i,n;

	y=(b-a)/tol;

	for(i=0;;i++)//利用循环求解N
	{
	   if(f(i)>=y)  //当F(i)达到要求时，结束运算
	   {
		   n=i;
		   break;
	   }
	}
	return n; //返回n
}


/********定义求解斐波那契数函数*******/
float F(int n)
{
	//不采用递归调用求解斐波那契数，减少大量的不必要计算
	int *s=new int [n+1];
	s[0]=0;
	if(n==0) 
	{
		delete []s;
		return 0;
	}
	s[1]=1;
    if(n==1) 
	{
		delete []s;
		return 1;
	}
	else 
	{
	for(int i=2;i<=n;++i)
	{
		s[i]=s[i-1]+s[i-2];
	}
	    int t=s[n];
		delete []s;
		return t;
	}
	
}


/*****定义数学公式函数*********/
float f(float x,int i)   //在x点求值，i为对应题目0-3对应a-d
{
	float y;
	if(i==0) y=fa(x);
    if(i==1) y=fb(x);
	if(i==2) y=fc(x);
	if(i==3) y=fd(x);
	return y;
}

/***a题数学函数*******/
float fa(float x)
{
  float y;

  y=exp(x)+2*x+x*x/2;
  return y;
}

/***b题数学函数*******/
float fb(float x)
{
  float y;
  y=-sin(x)-x+x*x/2;
  return y;
}

/***c题数学函数*******/
float fc(float x)
{
  float y;
  y=x*x/2-4*x-x*cos(x);
  return y;
}

/***d题数学函数*******/
float fd(float x)
{
  float y;
  y=pow(x,3)-5*x*x+23;
  return y;
}

