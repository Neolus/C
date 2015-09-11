/*本文件实现采用中心差分求解微分的算法*/

#include <math.h>  //数学函数头文件
#include <float.h> //对应最小浮点数
#include <stdio.h>
#include <stdlib.h> //fprint函数

//函数声明
float diffcen(float (*f)(float),float x,float tol,int max1); //diffcen为极限法求导数函数
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



	//调用中心差分法求解导数函数
    z1=diffcen(fa,a,1e-6,100);
	z2=diffcen(fb,b,1e-6,100);
	z3=diffcen(fc,c,1e-6,100);
	z4=diffcen(fd,d,1e-6,100);
	z5=diffcen(fe,e,1e-6,100);

//	printf("%0.13f\n",z5);
	printf("%0.13f\n%0.13f\n%0.13f\n%0.13f\n%0.13f",z1,z2,z3,z4,z5);  //输出每题的导数近似值，0.13表示输出结果显示小数点后13位
	getchar();

	
}

/****定义中心差分法求解导数函数****************/
float diffcen(float (*f)(float),float x,float tol,int max1) //*f为数学函数，x表示在x点求解导数，tol用来判定误差值，max1为循环计算的最大次数
{
	int k;
	float h=0.1,err,err1,rel,p;
	float eps=FLT_MIN; //最小浮点数
	float *D=new float[max1]; //用来存放计算序列结果
		FILE*fp;//定义指向文件的指针变量fp
		fp=fopen("result.txt","w+");


/*	if((fp=fopen("result.txt","w"))==NULL)//打开输出文件并使fp指向该文件
	{
		printf("cannot open the file\n");//如果打开出错，这输出打开失败
		exit(0);//终止程序
	}
	*/



	D[0]=(-f(x+2*h)+8*f(x+h)-8*f(x-h)+f(x-2*h))/(12*h); //计算k=0时的导数近似值
	printf("%f\n",D[0]); //输出D[0]
	fprintf(fp,"%f\n",D[0]); //写入文本

	for(k=1;k<max1;k++) //循环计算k>0后的结果
	{
		if(k==1) //D[1]单独计算
		{
			h=h/pow(10.,k);
		    D[k]=(-f(x+2*h)+8*f(x+h)-8*f(x-h)+f(x-2*h))/(12*h); //数学计算公式
			

			err=fabs(D[k]-D[k-1]);  //与上一项绝对误差
		    rel=err/(D[k]+eps); //与上一项相对误差误差

			printf("%d\t%f\t%f\n",1,D[k],rel);  //输出计算次数，计算结果和相对误差
	        fprintf(fp,"%d\t%f\t%f\n",1,D[k],rel);  //写入文本

		}

		else
		{
			 h=h/pow(10.,k);
			 err1=err;
			 D[k]=(-f(x+2*h)+8*f(x+h)-8*f(x-h)+f(x-2*h))/(12*h);  //数学计算公式
			 err=fabs(D[k]-D[k-1]);  //与上一项绝对误差
		     rel=err/(D[k]+eps);  //与上一项相对误差误差
			printf("%d\t%f\t%f\n",k,D[k],rel);  //输出计算次数，计算结果和相对误差
	        fprintf(fp,"%d\t%f\t%f\n",k,D[k],rel);  //写入文本

		   if(err>=err1) break; //如果相对误差开始增大，则跳出循环结束计算
		}
	
		p=D[k];  //每一次的结果保存
		if(rel<tol) break;  //如果相对误差小于指定值，跳出循环，结束计算
		
	}
	fprintf(fp,"%0.13f",p);
	fclose(fp);//关闭fp。

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


