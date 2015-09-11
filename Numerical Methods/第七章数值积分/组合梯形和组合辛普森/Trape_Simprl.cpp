/*本文件实现了组合体现公式和组合辛普森公式求解积分的两个算法*/
#include <math.h>
#include<stdio.h>
#include<float.h>

# define pi 3.14159265

//函数声明
double difflim2(int j,double x,double tol,int max1); //difflim，求解二阶导数
double difflim4(int j,double x,double tol,int max1); //difflim，求解二阶导数
double trape(int j,double *x,double h,int M);  //trape组合梯形公式
double simprl(int j,double *x,double h,int M); //simprl为组合辛普森公式
double compute(double a,double b,int M,double *x);   //compute计算组合梯形需要的点
int solveM2(double a,double b,double dif2,double tol);  //solveM求解满足精度要求的M值
int solveM4(double a,double b,double dif2,double tol);  //solveM求解满足精度要求的M值



void main()
{
	int M1,M2=20,i,j;
	double h,res,dif;
	double difmax=0;
	double *X1=new double [M2+1];

	//0-6对应a到e数学函数的，积分上下限，A为下限，B为上限
	double A[6]={-1,0,0.25,0,0,0};
	double B[6]={1,1,4,4,2,pi};


	/******组合梯形公式计算********/
	for(j=0;j<6;j++)  // 利用循环实现6个题的计算，j+1对应题号
	{
		printf("the answer of %c is\n",97+j);
		compute(A[j],B[j],M2,X1);  //将区间分为M2份
	    difmax=0;
		for(i=0;i<=M2;i++)  //在每一个点求解2阶导数
		{ 
			dif=fabs(difflim2(j+1,X1[i],1e-5,100));
			if(dif>difmax) difmax=dif;  //找出二阶导数的最大值
		}
		M1=solveM2(A[j],B[j],difmax,1e-9);  //利用求解的二阶导数最大值，结合误差分析，求解满足实验精度要求的分断数M
		printf("the max of dif2 and M are %f\t%d\n",difmax,M1);

	   double *X=new double [M1+1];
	   h=compute(A[j],B[j],M1,X);  //将区间按M分段
       res=trape(j+1,X,h,M1);  //利用组合梯形公式求解积分
		printf("step and result are %f\t%0.10f\n\n",h,res);
	  delete []X;
	}

	/***********组合辛普森计算************************/
	printf("composite simpson\n\n");
	for(j=0;j<6;j++)
	{
		printf("the answer of %c is\n",97+j);
		compute(A[j],B[j],M2,X1);  //将区间分为M2份
	    difmax=0;
		for(i=0;i<=M2;i++)  //在每一个点求解4阶导数
		{ 
			dif=fabs(difflim4(j+1,X1[i],1e-5,100));
			if(dif>difmax) difmax=dif;  //找出四阶导数的最大值
		}
		M1=solveM4(A[j],B[j],difmax,1e-9);  //利用求解的四阶导数最大值，结合误差分析，求解满足实验精度要求的分断数M
		printf("the max of dif2 and M are %f\t%d\n",difmax,M1);

	   double *X2=new double [2*M1+1];
	   h=compute(A[j],B[j],2*M1,X2);  //将区间按M分段
       res=simprl(j+1,X2,h,M1);  //利用组合辛普森公式求解积分
		printf("step and result are %f\t%0.10f\n\n",h,res);
		delete []X2;
	}
	
	//释放上面所有的new指针

	delete []X1;

	getchar();
	
}



/****定义极限法求解二阶导数函数****************/
double difflim2(int j,double x,double tol,int max1) //*f为数学函数，x表示在x点求解导数，tol用来判定误差值，max1为循环计算的最大次数
{
	int k;
	double h=0.1,err,err1,rel,p;
	double eps=FLT_MIN; //最小浮点数
	double *D=new double[max1]; //用来存放计算序列结果
	double f(int i,double x);
	double g ;
	g=f(j,x);
	D[0]=(f(j,(x+pow(10.,0)*h))-f(j,x-pow(10.,0)*h))/(2*h*pow(10.,0)); //计算k=0时的导数近似值


	for(k=1;k<max1;k++) //循环计算k>0后的结果
	{
		if(k==1) //D[1]单独计算
		{
		    D[k]=(f(j,x+pow(10.,-k)*h)-2*f(j,x)+f(j,x-pow(10.,-k)*h))/(pow(h*pow(10.,-k),2)); //数学计算公式

			err=fabs(D[k]-D[k-1]);  //与上一项绝对误差
		    rel=err/(D[k]+eps); //与上一项相对误差误差

		}

		else
		{
			 err1=err;
			 D[k]=(f(j,x+pow(10.,-k)*h)-2*f(j,x)+f(j,x-pow(10.,-k)*h))/(pow(h*pow(10.,-k),2));  //数学计算公式
			 err=fabs(D[k]-D[k-1]);  //与上一项绝对误差
		     rel=err/(D[k]+eps);  //与上一项相对误差误差
		   if(err>=err1) break; //如果相对误差开始增大，则跳出循环结束计算
		}

		p=D[k];  //每一次的结果保存
	
		if(rel<tol) break;  //如果相对误差小于指定值，跳出循环，结束计算

	}
	delete []D;
	return (p);  // 返回最后的结算结果

}




/****定义极限法求解四阶导数函数****************/
double difflim4(int j,double x,double tol,int max1) //i对应题目号（1对应a），x表示在x点求解导数，tol用来判定误差值，max1为循环计算的最大次数
{
	int k;
	double h=0.1,err,err1,rel,p;
	double eps=FLT_MIN; //最小浮点数
	double *D=new double[max1]; //用来存放计算序列结果
	double f(int i,double x); //数学函数

	D[0]=(f(j,x+pow(10.,0)*h)-2*f(j,x)+f(j,x-pow(10.,0)*h))/pow(h,4); //计算k=0时的导数近似值


	for(k=1;k<max1;k++) //循环计算k>0后的结果
	{
		if(k==1) //D[1]单独计算
		{
		    D[k]=(f(j,x+2*pow(10.,-k)*h)-4*f(j,x+pow(10.,-k)*h)+6*f(j,x)-4*f(j,x-pow(10.,-k)*h)+f(j,x-2*pow(10.,-k)*h))/(pow(h*pow(10.,-k),4)); //数学计算公式

			err=fabs(D[k]-D[k-1]);  //与上一项绝对误差
		    rel=err/(D[k]+eps); //与上一项相对误差误差

		}

		else
		{
			 err1=err;
			 D[k]=(f(j,x+2*pow(10.,-k)*h)-4*f(j,x+pow(10.,-k)*h)+6*f(j,x)-4*f(j,x-pow(10.,-k)*h)+f(j,x-2*pow(10.,-k)*h))/(pow(h*pow(10.,-k),4)); //数学计算公式
			 err=fabs(D[k]-D[k-1]);  //与上一项绝对误差
		     rel=err/(D[k]+eps);  //与上一项相对误差误差
		   if(err>=err1) break; //如果相对误差开始增大，则跳出循环结束计算
		}

		p=D[k];  //每一次的结果保存
	
		if(rel<tol) break;  //如果相对误差小于指定值，跳出循环，结束计算

	}
	delete []D;
	return (p);  // 返回最后的结算结果

}



/******定义组合梯形公式求解积分*********/
double trape(int j,double *x,double h,int M)  //j对应题目号（1对应a）*x为输入数组包括积分上下限，h为步长，M为分段数
{
	double y=0;
	int i;
	double f(int i,double x); //数学函数

	for(i=1;i<M;i++)  //对除去首尾两点的函数值求和
	{
	  y+=f(j,x[i]);
	}

	y=h*((f(j,x[0])+f(j,x[M]))/2+y);  //加上首尾函数值，并求解最终的积分结果
	return y;  //返回最后的函数值
}

/******定义计算所有分断点的横坐标的函数****************/
double compute(double a,double b,int M,double *x)  //a为分段起点，b为分段终点，M为分段数，*x用来存放所有的点的X坐标
{
	int i;
	double step;
	step=fabs(a-b)/M;  //计算步长
	for(i=0;i<=M;i++)
	{
	   x[i]=a+i*step;  //计算所有点的坐标
	}
	return step;  //只返回步长

}

/*****定义求解满足实验精度M的函数*************/
int solveM2(double a,double b,double dif2,double tol)  //a为积分下限，b为积分上限，dif2为二阶导数的最大值，tol为实验要求的精度
{
	double len;
	double re;
	int M;

	len=b-a;  //区间长度
	re=len*sqrt(len*dif2/(12*tol));   //计算M
	M=int(re)+1;  //取整+1

	return M;  //返回M
}


int solveM4(double a,double b,double dif4,double tol)  //a为积分下限，b为积分上限，dif2为二阶导数的最大值，tol为实验要求的精度
{
	double len;
	double re;
	int M;

	len=b-a;  //区间长度
	re=pow((pow(len,5)*dif4/(180*16*tol)),0.25);   //计算M
	printf("%f\n",(pow(len,5)*dif4/(180*16*tol)));
	printf("%f\n",re);
	M=int(re)+1;  //取整+1

	return M;  //返回M
}



/******定义组合辛普森求解积分*********/
double simprl(int j,double *x,double h,int M)  //j对应题目号（1对应a），*x为输入数组包括积分上下限，h为步长，M为分段数的一半
{
	double f(int i,double x);
	double y=0;
	int i;

	for(i=1;i<2*M;i++)  //对除去首尾两点的函数值求和
	{
		if(i%2==0)   y+=2*f(j,x[i]);
		else
		{ y+=4*f(j,x[i]);}
	}

	y=h/3*(f(j,x[0])+f(j,x[2*M])+y);  //加上首尾函数值，并求解最终的积分结果
	return y;  //返回最后的函数值
}



/********定义需要参与计算的题目对应函数***********/
double f(int i,double x)  //i对应题目号（1对应a）,x对应点求解函数
{
	//函数声明，a-f对应题目的数学公式
	double fa(double x);
	double fb(double x);
	double fc(double x);
	double fd(double x);
	double fe(double x);
	double ff(double x);
	double y=0;
	//对应关系如下1-6分别对应a-f
	if(i==1)  y=fa(x);
	if(i==2)  y=fb(x);
	if(i==3)  y=fc(x);
	if(i==4)  y=fd(x);
	if(i==5)  y=fe(x);
	if(i==6)  y=ff(x);

	return y;  //返回最后的y
}


/*****a题数学函数********/
double fa(double x)
{
	double y;
	y=1/(1+x*x);

	return y;
}

/*****b题数学函数********/
double fb(double x)
{
	double y;
	y=2+sin(2*sqrt(x));
	return y;
}


/*****c题数学函数********/
double fc(double x)
{
	double y;
	y=1/sqrt(x);
	return y;
}


/*****d题数学函数********/
double fd(double x)
{
	double y;
	y=x*x*exp(-x);
	return y;
}


/*****e题数学函数********/
double fe(double x)
{
	double y;
	y=2*x*cos(x);
	return y;
}

/*****f题数学函数********/
double ff(double x)
{
	double y;
	y=sin(2*x)*exp(-x);
	return y;
}

