/*本文件实现微分方程的龙格-库塔-费尔伯格法*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


/*****函数声明******/
void RKF(double (*f)(double,double),double yk,double x0,double xn,double h,double tol,FILE *fp); //RKF龙格-库塔-费尔伯格法
double fa(double tk,double yk); //fa第一个题目微分方程
double fb(double tk,double yk); //fb第二个题目微分方程

void main()
{
	double y0=0;//初始条件
	double A[2],B[2],step,tol; //A存放两题的左端点，B为右端点

	step=0.1;
	tol=1e-7;  //误差容限
	A[0]=0;  
	B[0]=3;
	
	A[1]=0;
	B[1]=1;
	
		
	FILE*fp;//定义指向文件的指针变量fp
	fp=fopen("A.txt","w+");

	RKF(fa,y0,A[0],B[0],step,tol,fp); //调用RK函数求解第一题微分方程
	fprintf(fp,"The answer of question B\n");
	RKF(fb,y0,A[1],B[1],step,tol,fp); //调用RK函数求解第二题微分方程

	fclose(fp); //关闭文本
	getchar();
}



/*****定义龙格-库塔-费尔伯格法求解微分方程函数***********/
void RKF(double (*f)(double,double),double yk,double x0,double xn,double h,double tol,FILE *fp)//f需要求解的微分方程，yk初始条件，x0微分起点，xn微分终点，h步长,fp指向文本
{
	int i=0,j,m;
	double t1;

	//龙格-库塔-费尔伯格法中需要的常系数
	double a[5]={0.25,0.375,12./13,1.,0.5};
	double b[5][5]={{0.25},{3./32,9./32},{1932./2197,-7200./2197,7296./2197},{439./216,-8.,3680./513,-845./4104},{-8./27,2.,-3544./2565,1859./4104,-11./40}};
	double wy[5]={25./216,0,1408./2565,2197./4101,-0.2};
	double wz[6]={16./135,0,6656./12825,28561./56430,-9./50,2./55};


	double sumy,sumz,y[6],x[6],zk,s,err,hmin,yk0;
	double hmax;
	double k[6];

	hmin=h/64; //自适应最小步长限制
	hmax=h*64; //自适应最大步长限制

	while(true)
	{
		sumy=0;
		sumz=0;

		//计算k0-k5
     	k[0]=h*f(x0,yk);
/*		k[1]=h*f(t1+a[0]*h,yk+b[0][0]*k[0]);
		k[2]=h*f(t1+a[1]*h,yk+b[1][0]*k[0]+b[1][1]*k[1]);
		k[3]=h*f(t1+a[2]*h,yk+b[2][0]*k[0]+b[2][1]*k[1]+b[2][2]*k[2]);
		k[4]=h*f(t1+a[3]*h,yk+b[3][0]*k[0]+b[3][1]*k[1]+b[3][2]*k[2]+b[3][3]*k[3]);
		k[5]=h*f(t1+a[4]*h,yk+b[4][0]*k[0]+b[4][1]*k[1]+b[4][2]*k[2]+b[4][3]*k[3]+b[4][4]*k[4]);
   */
		for(j=1;j<6;j++)
		{
			x[j]=x0+a[j-1]*h;
			y[j]=yk;
			for(m=0;m<j;m++)
			{
				y[j]+=b[j-1][m]*k[m];
			}
			k[j]=h*f(x[j],y[j]);
		}

     //计算粗略的yk+1
		for(j=0;j<5;j++) 
		{
			if (j==1) continue;
			sumy=sumy+wy[j]*k[j]; //k乘以权重并求和
		}
		yk0=yk+sumy;

		//计算比较精确的yk+1即zk+1
		for(j=0;j<6;j++) 
		{
			if (j==1) continue;
			sumz=sumz+wz[j]*k[j]; //k乘以权重并求和
		}
		zk=yk+sumz; //计算yk+1

		err=fabs(zk-yk0); //两者误差

		if((err<tol)||(h<2*hmin))  //如果误差达到精度或者步长到达最小步长时计算下一个点
		{
	      t1=x0+h; //每一次tk
		  
		  if((x0+hmin)>(xn+1e-7)) break; //计算接近边界点时，停止计算
	
		  yk=zk; //采用精确的解为该点的值
		  x0=t1; //下一个计算点
		  
		  if(t1>xn) t1=xn; //超过边界后，取边界点
		
		  printf("%0.8f\t%0.11f\t%0.8f\t%0.8f\n",t1,yk,err,h);
	      fprintf(fp,"%0.8f\t%0.11f\t%0.8f\t%0.8f\n",t1,yk,err,h); 

		}

		//依据误差来缩放步长
		s=0.84*pow(tol*h/err,0.25); 
		if((s<0.75)&&(h>=2*hmin)) h=h/2;
		if((s>1.5)&&(2*h<=hmax)) h=2*h;
	}
}


/****第一个微分方程*******/
double fa(double tk,double yk)
{
	double y;
	y=9*tk*exp(3*tk);
	return y;
}

/****第二个微分方程*******/
double fb(double tk,double yk)
{
	double y;
	y=2*atan(tk);
	return y;
}

