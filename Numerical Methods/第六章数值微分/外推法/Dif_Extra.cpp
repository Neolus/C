/*本文件实现外推法求解导数的算法*/

#include <math.h>  //数学函数头文件
#include <float.h> //对应最小浮点数
#include <stdio.h>
#include <stdlib.h> //fprint函数

//函数声明
float diffex(float (*f)(float),float x,float delta,float tol,int max1); //diffex为外推微分法求导数函数
float fa(float x);  //fa为a题的数学函数
float fb(float x);  //fb为b题的数学函数
float fc(float x);  //fc为c题的数学函数
float fd(float x);  //fd为d题的数学函数
float fe(float x);  //fe为e题的数学函数


	
/*******主函数**********************/
void main()
{

	float z1,z2,z3,z4,z5;
	//a、b、c、e、f为对应题目中求解导数的位置
	float a=1/sqrt(3.);
	float b=(1+sqrt(5.))/3;
	float c=1/sqrt(2.);
	float d=(1-sqrt(5.))/2;
	float e=0.0001;


	//调用外推微分法求解导数函数
   z1=diffex(fa,a,1e-5,1e-6,100);
	z2=diffex(fb,b,1e-5,1e-6,100);
	z3=diffex(fc,c,1e-5,1e-6,100);
	z4=diffex(fd,d,1e-5,1e-6,100);
	z5=diffex(fe,e,1e-5,1e-6,100);


//	printf("%f",z5);
	printf("%f0.13\n%0.13f\n%0.13f",z1,z2,z3,z4,z5);  //输出每题的导数近似值，0.13表示输出结果显示小数点后13位
	getchar();
}

/****定义外推微分法求解导数函数****************/
float diffex(float (*f)(float),float x,float delta,float tol,int max1) //*f为数学函数，x表示在x点求解导数，delta、tol用来判定误差值，max1为循环计算的最大次数
{
	int j,k;
	float h=0.1,err,err_p,rel,rel_p,p;
	float eps=FLT_MIN; //最小浮点数
	float **D; //用来存放计算序列结果
		D=new float *[max1]; 
		for(k=0;k<max1;k++)
		{
		D[k]=new float [max1];
		}

		FILE*fp;//定义指向文件的指针变量fp，用于将数据写入文本
		fp=fopen("c.txt","w+");


	for(j=0;j<max1;j++)
	  {
	   for(k=0;k<=j;k++) //循环计算到D[k][k]后的结果
		{
		if(k==0) //计算第一列
			{
	    		D[j][0]=(f(x+powf(2,-j)*h)-f(x-powf(2,-j)*h))/(powf(2,-j+1)*h);
			}
		else //计算其他列
			{
			    D[j][k]=D[j][k-1]+(D[j][k-1]-D[j-1][k-1])/(powf(4,k)-1);
			}
		}
	
	   if(j>0)
	   	{
			printf("%d\t",j); //输出行数
			fprintf(fp,"%d\t",j); //写入行数
			if(j==1) //第一行
			{
			err=fabs(D[j][j]-D[j-1][j-1]);  //计算绝对误差
			rel=err/fabs(D[j][j]); //计算相对误差
			printf("%f\t%f\t%0.7f\n",D[j][j],err,rel);
			fprintf(fp,"%f\t%f\t%0.7f\n",D[j][j],err,rel);

			}

			if(j>1) //其他行
			{
			rel_p=rel;
			err=fabs(D[j][j]-D[j-1][j-1]);  //计算绝对误差
			rel=err/fabs(D[j][j]); //计算相对误差
			printf("%f\t%f\t%0.7f\n",D[j][j],err,rel);
			fprintf(fp,"%f\t%f\t%0.7f\n",D[j][j],err,rel);
			if(rel>rel_p) break; //如果相对误差开始变大结束运算
			}
		 if(err<delta||rel<tol)  break; //如果绝对误差或者相对误差低于预设值结束运算
	     p=D[j][j];
	    }

	}
    fprintf(fp,"%f\t%0.13f",D[0][0],p); //写入D[0][0],和最后结果13位小数
	fclose(fp);//关闭fp。

	for(k=0;k<max1;k++)
		{
		delete []D[k];
		}
	delete []D;

	return (p);  // 返回最后的结算结果

}
	
/******题目中的a题数学函数*************/
float fa(float x)
{
  float y;
  y=pow(x,5)*(pow(x,28)*(60*pow(x,12)-32)+233)-47*pow(x,2)-77;
  return (y);
}

/******题目中的b题数学函数*************/
float fb(float x)
{
  float y;
  y=tan(cos((sqrt(5.)+sin(x))/(1+pow(x,2))));
  return (y);
}

/******题目中的c题数学函数*************/
float fc(float x)
{
  float y;
  y=sin(cos(1/x));
  return (y);
}
/******题目中的d题数学函数*************/
float fd(float x)
{
  float y;
  y=sin(pow(x,3)-7*pow(x,2)+6*x+8);
  return y;
}

/******题目中的e题数学函数*************/
float fe(float x)
{
	 float y;
	 y=pow(x,pow(x,x));
	 return (y);
   
}
