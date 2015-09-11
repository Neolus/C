/*本文件实现内德-米德方法*/
#include <math.h>
#include <stdio.h>
#include <float.h>


double eps=FLT_MIN;

/***函数声明********/
void order(double (*f)(double,double,double,double,int),int k,double B[4],double W[4],double H[4],double L[4],double M[4]);//将输入的5个点排序
double *neder(double (*f)(double,double,double,double,int),int k,double *B,double *W,double *H,double *L,double *M,double tol,FILE *fp);//内德—米德方法
void copy(double A[4],double C[4]); //将C的值复制到A中。C为一个坐标点
double f(double x,double y,double z,double u,int i); //数学公式
double fa(double x,double y,double z); //a-c题的数学公式
double fb(double x,double y,double z,double u);
double fc(double x,double y,double z,double u);



void main()
{
	double A[4][4]={{1,1,1,0},{0,1,0,0},{1,0,1,0},{0,0,1,0}}; //A题的起始点，用一个一维数组来存放一个点的坐标
	double B[5][4]={{1,1,1,0.8},{1,0.8,1,1},{0.8,1,0.9,1},{1,0.9,0.8,1},{0.9,0.8,0.9,1.1}}; //B题的起始点
	double C[5][4]={{0.7,0.6,0.7,0.8},{0.8,0.7,1.0,0.9},{0.65,0.8,0.9,0.5},{1.0,0.8,0.7,0.9},{0.6,0.9,0.7,0.7}}; //C题的起始点

	FILE *fp; //fp指向文本
	fp=fopen("result.txt","w+");

	neder(f,1,B[0],B[1],B[2],B[3],B[4],1e-8,fp);//调研内德尔-米德函数，求解b题，求解其他题需要稍微修改参数

	int i,j;
	for(i=0;i<5;i++)  //输出最后的满足要求的5个点
	{
		for(j=0;j<4;j++)
		{
		printf("%0.8f\t",B[i][j]);  
		fprintf(fp,"%0.8f\t",B[i][j]);  //写入文本
		}
		printf("\n");
		fprintf(fp,"\n");
	
	}

	fclose(fp);//关闭文本
	getchar();

}



/****定义依照函数值大小排序函数**********/
void order(double (*f)(double,double,double,double,int),int k,double *B,double *W,double *H,double *L,double *M) //f为数学函数，k对应题目号，B、W、H、L、M为需要排序的点
{

	double y[5],tmax[4],tmin[4],th[4],tl[4],tm[4];
	double min,max,high,low;
	int i,nm,nn,nh,nl;

	//计算5个点的函数值
	y[0]=f(B[0],B[1],B[2],B[3],k);
	y[1]=f(W[0],W[1],W[2],W[3],k);
	y[2]=f(H[0],H[1],H[2],H[3],k);
	y[3]=f(L[0],L[1],L[2],L[3],k);
	y[4]=f(M[0],M[1],M[2],M[3],k);

	min=y[0];
	max=y[0];


	for(i=0;i<5;i++)
	{
		if(y[i]>=max)  //找出最大点，并交换坐标
		{
			max=y[i];
			if(i==0) copy(tmax,B);  
			if(i==1) copy(tmax,W);
		    if(i==2) copy(tmax,H);
		    if(i==3) copy(tmax,L);
			if(i==4) copy(tmax,M);
			nm=i;
		}
		if(y[i]<=min)    //找出最小点，并交换坐标
			{
				min=y[i];
				if(i==0) copy(tmin,B);
				if(i==1) copy(tmin,W);
				if(i==2) copy(tmin,H);
				if(i==3) copy(tmin,L);
				if(i==4) copy(tmin,M);
				nn=i;
		    }
	}
	high=min;
	low=max;

	for(i=0;i<5;i++)
	{
		if(i==nn||i==nm) continue; //跳过最大、最小点
		if((y[i]<=max)&(y[i]>=min)&(y[i]>high)) //找出次大点，并交换坐标
		{
			high=y[i];
			if(i==0) copy(th,B);
			if(i==1) copy(th,W);
			if(i==2) copy(th,H);
			if(i==3) copy(th,L);
            if(i==4) copy(th,M);
			nh=i;

		}
			if((y[i]<=max)&(y[i]>=min)&(y[i]<low)) //找出次小点，并交换坐标
		{
			low=y[i];
			if(i==0) copy(tl,B);
			if(i==1) copy(tl,W);
			if(i==2) copy(tl,H);
			if(i==3) copy(tl,L);
            if(i==4) copy(tl,M);
			nl=i;
		}
	}
	for(i=0;i<5;i++) //寻找中间点，并交换坐标
	{
		if(i==nn||i==nm||i==nl||i==nh) continue;
		{
			if(i==0) copy(tm,B);
			if(i==1) copy(tm,W);
			if(i==2) copy(tm,H);
			if(i==3) copy(tm,L);
            if(i==4) copy(tm,M);
		}



	}


	copy(B,tmin);  //函数值最小点
	copy(W,tmax);  //函数值最大点
	copy(L,tl);  //函数值次小点
	copy(H,th);  //函数值次大点
	copy(M,tm);  //函数值中间点

}


/****内德-米德方法函数***********/
double *neder(double (*f)(double,double,double,double,int),int k,double *B,double *W,double *H,double *L,double *M,double tol,FILE *fp)  //f为数学函数，k对应题目号，B、W、H、L、M为5点，tol为实验精度，fp指向文本
{
	order(f,k,B,W,H,L,M);  //先将输入的5个点排序

	double R[4],E[4],MM[4],C1[4],C2[4];
	double yr,ye,yb,yw,yh,yl,ym,yc1,yc2;
	int i;

	//如果最好点B和最坏点W之间的坐标值之差达到实验精度要求，返回B点
	if((fabs(W[0]-B[0])<tol)&&(fabs(W[1]-B[1])<tol)&&(fabs(W[2]-B[2])<tol)&&(fabs(W[3]-B[3])<tol))
	{return B;}




	for(i=0;i<4;i++) 
	{
		MM[i]=(B[i]+H[i]+L[i]+M[i])/4; //计算4边形的中心
		R[i]=2*MM[i]-W[i];  //R点
		E[i]=2*R[i]-MM[i];  //拓展点E
	}

	//计算各点函数值
	yr=f(R[0],R[1],R[2],R[3],k);
	ye=f(E[0],E[1],E[2],E[3],k);
	yb=f(B[0],B[1],B[2],B[3],k);
	yw=f(W[0],W[1],W[2],W[3],k);
	yh=f(H[0],H[1],H[2],H[3],k);
	yl=f(L[0],L[1],L[2],L[3],k);
	ym=f(M[0],M[1],M[2],M[3],k);	


	printf("%0.8f\t%0.8f\t%0.8f\t%0.8f\t%0.8f\n",B[0],B[1],B[2],B[3],yb);
	fprintf(fp,"%0.8f\t%0.8f\t%0.8f\t%0.8f\t%0.8f\n",B[0],B[1],B[2],B[3],yb);


	if(yr<yw) //如果R点函数值小于W点
	{
		if(ye<yr)//如果E点函数值小于R点
		{
			copy(W,E);
		}
		else copy(W,R);
	}
	else //如果R点函数值不小于W点
	{
		for(i=0;i<4;i++)  //收缩点
		{
			C1[i]=(W[i]+MM[i])/2;
			C2[i]=(R[i]+MM[i])/2;
		}
		yc1=f(C1[0],C1[1],C1[2],C1[3],k);
		yc2=f(C2[0],C2[1],C2[2],C2[3],k);

      if((yw>yc1)||(yw>yc2))
		  {
			if(yc1>yc2) copy(C1,C2);
			copy(W,C1);
		  }
	  else{  //收缩点的函数值比W点大
		  for(i=0;i<4;i++) //所有点向B收缩
			  {
				  L[i]=(L[i]+B[i])/2;
				  M[i]=(M[i]+B[i])/2;
				  H[i]=(H[i]+B[i])/2;			  
				  W[i]=(W[i]+B[i])/2;
			  }

	      }

	}

	B=neder(f,k,B,W,H,L,M,tol,fp);  //继续递归调用
	return B; //返回B点坐标
}


/****定义复制坐标函数********/
void copy(double *A,double*C) //将C坐标复制到A中
{
	int i;
	for(i=0;i<4;i++)
	{
		A[i]=C[i];
	}
}



/***定义数学函数***********/
double f(double x,double y,double z,double u,int i) //在（x,y,z,u）初求值，i对应题目号
{
	double s=0;
	if(i==0) s=fa(x,y,z);
	if(i==1) s=fb(x,y,z,u);
	if(i==2) s=fc(x,y,z,u);
	return s;
}


/***a题数学公式****/
double fa(double x,double y,double z)
{
	double s;
	s=2*x*x+2*y*y+z*z-2*x*y+y*z-7*y-7*z;
	return s;
}

/***b题数学公式****/
double fb(double x,double y,double z,double u)
{
	double s;
	s=2*(x*x+y*y+z*z+u*u)-x*(y+z-u)+y*z-3*x-8*y-5*z-9*u;
	return s;
}

/***c题数学公式****/
double fc(double x,double y,double z,double u)
{
	double s;
	s=x*y*z*u+1/(x+eps)+1/(y+eps)+1/(z+eps)+1/(u+eps);
	return s;
}