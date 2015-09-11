/*本文件实现龙贝格积分*/
//计算量较大，耗时间
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define pi 3.14159265359
//函数声明
double rom(int i,int n,double a,double b,double tol,FILE*fp);  //rom为龙贝格函数

void main()
{

	double res,tole=1e-10;  //tole为实验精度
	double A[2]={0,0};  //积分下限
	double B[2]={2,1}; //积分上限
	

	FILE*fp1;//定义指向文件的指针变量fp
	fp1=fopen("result.txt","w+");

	printf("the question a\n");
	fprintf(fp1,"the question a\n");
	res=rom(1,25,A[0],B[0],tole,fp1);  //调用函数求解a题
	printf("%0.10f\n",res);
	fprintf(fp1,"%0.10f\n",res);  //计算结果写入文本

	printf("the question b\n");
	res=rom(2,25,A[0],B[1],tole,fp1);   //调用函数求解a题
	printf("%0.10f\n",res);
	fprintf(fp1,"%0.10f\n",res);  //计算结果写入文本

	fclose(fp1);  //关闭fp
	getchar();


}



//定义龙贝格函数
double rom(int i,int n,double a,double b,double tol,FILE *fp)  //i对应题目号，n为求解矩阵的维度，a为积分下限，a为积分上限，tol为实验精度，*fp为用来指向FILE文件
{
		double romber(int i,int J,int K,double a,double b);  //Romber为计算龙贝格积分里面的集体项
		double f(int i,double x);  //数学函数，i对应题号
		double RJ=0,RJpre,err;
		int j;

			for(j=0;j<=n;j++)  //循环，从低项向上运算
			{
				if(j==0)
				{
				  RJ=romber(i,j,j,a,b);   //计算R(0,0)
				  printf("%d\t%0.11f\t",j,RJ);
				   fprintf(fp,"%d\t%0.11f\t",j,RJ); //写入文本
				}
				 
			   if(j>0)
			   {
				    RJpre=RJ;
				   RJ=romber(i,j,j,a,b);  //计算R(J,J)
				    printf("%d\t%0.11f\t",j,RJ);
				   err=fabs(RJ-RJpre);  //绝对误差，R(J,J)-R(J+1,J+1)
				    fprintf(fp,"%d\t%0.11f\t",j,RJ);  //写入文本
				   if(err<tol)  break; //如果绝对误差小于精度要求，终止运算
			   
			   }
			   printf("\n");
			   fprintf(fp,"\n");
		  }
        
        return RJ;  //返回最后的R(J,J)



}

/**********定义递归梯形积分计算公式*********/
double suctrap(int i,int j,double a,double b)
{
	double f(int i,double x);  //f为数学函数
	double T1,T,step,temp=0;
	int k,M;
	M=pow(2.,j-1);
	step=(b-a)/pow(2.,j);

	if (j==0)    //计算第0项
		{
			T=step/2*(f(i,a)+f(i,b));
	    }
	else
	{
		double *x=new double[2*M+1];
		for(k=0;k<=2*M;k++)  //将区间分为2M份
		{
				x[k]=a+step*k;
		}

		for(k=1;k<=M;k++)
		{
			temp+=f(i,x[2*k-1]);  //所有函数值求和
		}

		T1=suctrap(i,j-1,a,b);  //递归调用
		T=T1/2+step*temp;  //梯形公式最后的结果
		temp=0;//中间变量归零
		delete []x;  //释放一维指针
	}
	return T;  

}


/*********定义龙贝格积分的单独一项的计算公式****************************/
double romber(int i,int J,int K,double a,double b) //i对应题号，J、K为计算R(J,K)项，a为积分下限，b为积分上限
{

    double suctrap(int i,int j,double a,double b);  //梯形公式函数
	double f(int i,double x);  

	double R,R1,R11;

	if(K==0)  //计算第一列，为梯形公式的计算的结果
	{
		R=suctrap(i,J,a,b); 
	}
	else  //其他列，递归调用
	{
		R1=romber(i,J,K-1,a,b);
		R11=romber(i,J-1,K-1,a,b);
		R=R1+(R1-R11)/(pow(4.,K)-1);
	}

	return R;  //返回计算结果


}


/********定义需要参与计算的题目对应函数***********/
double f(int i,double x)  //i对应题目号（1对应a）,x对应点求解函数
{
	//函数声明，a-f对应题目的数学公式
	double fa(double x);
	double fb(double x);

	double y=0;
	//对应关系如下1-6分别对应a-f
	if(i==1)  y=fa(x);
	if(i==2)  y=fb(x);


	return y;  //返回最后的y
}


/*****a题数学函数********/
double fa(double x)
{
	double y;
	y=sqrt(4*x-x*x);

	return y;
}

/*****b题数学函数********/
double fb(double x)
{
	double y;
	y=4/(1+x*x);
	return y;
}




