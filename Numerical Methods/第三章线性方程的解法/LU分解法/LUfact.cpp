/*本文件实现了采用LU分解法求解线性方程组的算法*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>         //结果写入文本，头函数

float lufact(float **a,float *b,int n);      //函数声明，lufact为LU分解函数

void main()
{

	float **A;           //定义二维指针，用来存放系数矩阵
//	int i,j,n=4;
	int i,j,n=3;
	A=new float *[n];    //初始化，指定二维数组指针大小
	  for(i=0;i<n;i++)
	   {
	   A[i]=new float[n];
	   }
	  float b[4][4]={{1,3,5,7},{2,-1,3,5},{0,0,2,5},{-2,-6,-3,1}};  //二维数组，其值为系数矩阵
	  float c[3][3]={{4,3,-1},{-2,-4,5},{1,2,6}};
	   for (i=0;i<n;i++)    //for循环，将系数矩阵的值，赋值给二维指针
           {
	         for(j=0;j<n;j++)
			 {
		//	   A[i][j]=b[i][j];   
			   A[i][j]=c[i][j];
			 }
	      }
	   float B[4]={1,2,3,4};    //方程AX=B，的B
	   float D[3]={1,2,3};
	//   lufact(A,B,4);    //调用LU分解函数,二维数组不能直接作为参数传入函数，故A用二维指针
	   lufact(A,D,3);

	   for(i=0;i<n;i++)
	   {
	      delete []A[i];
	   }
	   delete []A;
	   getchar();         //保持运行窗口

}




float lufact(float **a,float *b,int n)       //函数定义，a为系数矩阵，b为方程右边数据，即为增广矩阵最后一列，n为方程组的维数
{
float solve(float **m,float **u,float *b,int n);      //函数声明，solve为将LU分解后解X的函数
float exchange(float **a,float **I,float *b,int n);   //函数声明，exchange将系数矩阵a和矩阵b行变换
  float **m,**u,**I;     //定义二维指针
  int i,j,k;
  float r=0,s=0;      //定义两个中间变量
    m=new float *[n];    //指定二维数组指针大小
	  for(i=0;i<n;i++)   //m作为为下三角矩阵
	   {
	       m[i]=new float[n];
	   }
   u=new float *[n];    //指定二维数组指针大小
	  for(i=0;i<n;i++)   //u作为上三角矩阵
	   {
		 u[i]=new float[n];
	   }

      I=new float *[n];    //指定二维数组指针大小
	  for(i=0;i<n;i++)    //I用作单位矩阵，用来做行变换时的出等矩阵P，
	   {
		 I[i]=new float[n];
	   }

 for (i=0;i<n;i++)       //初始化m，u.I
  {
	for(j=0;j<n;j++)
	{
	    u[i][j]=0;       //u全置为0；
		if(i==j) 	
			{
				m[i][j]=1;     //m为单位矩阵
		       I[i][j]=1;     //I为单位矩阵
		   }
		else    
		{
			m[i][j]=0;
		    I[i][j]=0;
		}
	}
  }
    exchange(a,I,b,n);  //调用exchange函数，进行行变换

for(i=0;i<n;i++)     //for循环，进行LU分解，来求解上三角和下三角矩阵
{
	for(j=0;j<n;j++)
	{
	if(i==0)  u[i][j]=a[i][j];        //先计算u的第一行
	if(j==0)  m[i][j]=a[i][j]/u[0][0];   //计算m的第一列
	if(i!=0&&j!=0)
	{
		if(j<i) 
		{
			for(k=0;k<j;k++)
			{
				s=s+m[i][k]*u[k][j];     //s为中间变量，即为各项和
			}
			m[i][j]=(a[i][j]-s)/u[j][j];    //计算m的元素
			s=0;           //中间变量归零，下一次计算时必须从零开始
		}
		if(j>=i)
		{
		for(k=0;k<i;k++)
		{
			r=r+m[i][k]*u[k][j];    //r为中间变量，即为各项和
		}
		u[i][j]=a[i][j]-r;     //求解u的元素
		r=0;                //归零，下一次用r时，为计算下一个元素值了迭代必须是从零开始
		}
	}
	}

}

FILE*fp;//定义指向文件的指针变量fp
if((fp=fopen("mu.txt","w"))==NULL)//打开输出文件并使fp指向该文件
{
	printf("cannot open the file\n");//如果打开出错，这输出打开失败
    exit(0);//终止程序
}

      fprintf(fp,"the  matrix m\n");
       for (i=0;i<n;i++)      //for循环输出下三角矩阵m
           {
	         for(j=0;j<n;j++)
			 {
			 printf("m[%d][%d] %f ",i,j,m[i][j]);
			 fprintf(fp,"%f ",m[i][j]);//将float型变量A[i][j]输出到fp指向的文件中。
			 }
			 fprintf(fp,"\n");
	      }
	   fprintf(fp,"the  matrix u\n");
      for (i=0;i<n;i++)    //for循环输出上三角矩阵u
           {
	         for(j=0;j<n;j++)
			 {
			printf("u[%d][%d] %f ",i,j,u[i][j]);
			fprintf(fp,"%f ",u[i][j]);
			 }
			 printf("\n");
			 fprintf(fp,"\n");
	      }
	  fclose(fp);//关闭fp。
     solve(m,u,b,n);         //调用求解X的函数

 	  for(i=0;i<n;i++)   //m作为为下三角矩阵
	   {
	      delete []m[i];
		  delete []u[i];
		  delete []I[i];
	   }
	  delete []m;
	  delete []u;
	  delete[]I;

return 0;    //无具体值需要返回
}

float solve(float **m,float **u,float *b,int n)    //定义求解函数，m为下三角矩阵，u为上三角矩阵，b为增广矩阵最后一列，n为方程的维度
{
	int i,j;
	float t=0,temp=0;      //定义两个中间变量
	float *y=new float[n];   //定义一维指针，y用来存放解LY=B得到的Y
	float *x=new float[n];   //定义一维指针，x用来存放解UX=Y得到的X，此x即为所求问题最终结果
	
	y[0]=b[0]/m[0][0];   //计算y[0]
	for(i=1;i<n;i++)
	{
	  for(j=0;j<i;j++)
	   {
	    t=t+m[i][j]*y[j];   //中间变量，存放求和项
	   }
	  y[i]=b[i]-t;  //计算y
	  t=0;     //中间变量归零
	}

	x[n-1]=y[n-1]/u[n-1][n-1];  //计算x[n-1]
	for(i=n-2;i>=0;i--)
	{
		for(j=i+1;j<n;j++)
		{
		temp=temp+u[i][j]*x[j];   //中间变量，存放求和项
		}
	   x[i]=(y[i]-temp)/u[i][i];   //计算y
	   temp=0;          //中间变量归零
	}



	FILE*fp;//定义指向文件的指针变量fp
if((fp=fopen("XY.txt","w"))==NULL)//打开输出文件并使fp指向该文件
{
	printf("cannot open the file\n");//如果打开出错，这输出打开失败
    exit(0);//终止程序
}
	for(i=0;i<n;i++)
	{
	printf("y[%d] %f\t",i,y[i]);    // 输出Y
	fprintf(fp,"y[%d] %f\t",i,y[i]);
	printf("x[%d] %f\n",i,x[i]);    //输出X
	fprintf(fp,"x[%d] %f\n",i,x[i]); 
	}
	fclose(fp);//关闭fp。

	delete []x;
	delete []y;
	return 0;
}

float exchange(float **a,float **I,float *b,int n)  //定义行变换函数，a为初始系数矩阵，b为增广矩阵最后一列，I为单位矩阵，n为方程组维度
{
	int i,j,p;
	float c,d;
	float *b1=new float[n];       //定义一维指针，用来存放行变换之后的b
	for(j=0;j<n;j++)
	{
	   p=j;            //p用来记录列中的最大值所在的行数
		for(i=p;i<n-1;i++)
		{
		if(fabs(a[p][j])<fabs(a[i+1][j])) p=i+1;      //找到最大值所在的行数
		}
		for(i=0;i<n;i++)
     	{
	    c=a[j][i];       
		a[j][i]=a[p][i];     //进行行交换
		a[p][i]=c;
		d=I[j][i];
		I[j][i]=I[p][i];             //将单位矩阵的行同时变换，得到LU分解中的P矩阵
		I[p][i]=d;
     	}
	}

	for(i=0;i<n;i++)                
	{    b1[i]=0;
		for(j=0;j<n;j++)
		{
		b1[i]+=I[i][j]*b[j];	 //矩阵P*B，得到变化过后的矩阵b
		}
	}



		FILE*fp;//定义指向文件的指针变量fp
			if((fp=fopen("AB.txt","w"))==NULL)//打开输出文件并使fp指向该文件
			{
				printf("cannot open the file\n");//如果打开出错，这输出打开失败
				exit(0);//终止程序
			}


	for(i=0;i<n;i++)
	{
	b[i]=b1[i];             //将b1重新赋值给b,方便以后函数的调用
	 printf("b[%d] %f ",i,b[i]);    //输出行变换后的b
	 fprintf(fp,"b[%d] %f\n ",i,b[i]);
	}
	 for (i=0;i<n;i++)
        {
	      for(j=0;j<n;j++)
		  {
			  printf("%f  ",a[i][j]);   //输出行变换之后的a
			  fprintf(fp,"%f  ",a[i][j]); 
		  }
		  printf("\n");
		  fprintf(fp,"\n");
	     }
	fclose(fp);//关闭fp。
	delete []b1;
	return 0;
}