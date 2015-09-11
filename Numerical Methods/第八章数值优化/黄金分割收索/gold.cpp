/*本文件实现数值优化中的黄金收索法*/

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

/*****函数声明*********/
float golden(float (*f)(float,int),int i,float a,float b,float tol,FILE*fp);  //黄金分割法函数
float f(float x,int i); //所有数学函数
float fa(float x); //a到d的数学公式
float fb(float x);
float fc(float x);
float fd(float x);


void main()
{
	int i;
	float A[4]={-2.4,0.8,0.5,1};  //搜索左端点
	float B[4]={-1.6,1.6,2.5,5}; //搜索右端点
	float res,ff;

     FILE *fp;//定义指向文件的指针变量fp
	 fp=fopen("result.txt","w+");

	 //计算4个题目
	for(i=0;i<4;i++)
	{
		printf("the answer of %c\n",97+i);
		res=golden(f,i,A[i],B[i],1e-6,fp);  //调用黄金分割函数
		ff=f(res,i); //计算极值
		printf("%0.7f\t%0.7f\n",res,ff); 
		fprintf(fp,"%0.7f\t%0.7f\n",res,ff);  //数据写入文本
	}

	fclose(fp);//关闭fp。
	getchar();
}


/******定义黄金分割函数*************/
float golden(float (*f)(float,int),int i,float a,float b,float tol,FILE *fp) //f为数学函数，i为对应题目0-3对应a-d，a为左端点，b为右端点，tol为精度，fp指向文本
{
	float r;
	float a1,b1,c,d,length;
	float tc,td,z;
	r=0.5*(-1+sqrt(5.));
	length=b-a; 
	c=a+(1-r)*length;  //计算ck
	d=b-(1-r)*length;  //计算dk
	tc=f(c,i); //计算两点对应的函数值
	td=f(d,i);

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


	printf("%0.7f\t%0.7f\t%0.7f\t%0.7f\n",a,c,d,b);
	fprintf(fp,"%0.7f\t%0.7f\t%0.7f\t%0.7f\n",a,c,d,b);  //数据写入文本

	if(fabs(a1-b1)>tol)  //如果没有满足精度，继续细分
	{
		z=golden(f,i,a1,b1,tol,fp);
	}

	else
	{
		z=0.5*(a1+b1);  //取最后两点的中点为极值点
		printf("%0.7f\t%0.7f\n",a1,b1);
		fprintf(fp,"%0.7f\t%0.7f\n",a1,b1);
	}

	return z;

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

