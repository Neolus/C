/*���ļ�ʵ�������Է�����ĸ�˹�����¶������㷨*/

#include <stdio.h>
#include <math.h>
#include <float.h>   //��Ӧ��С������
#include <stdlib.h>         //���д���ı���ͷ����
#define N 50

void main()
{
float Seidel(float**a,float*b,float *p,float tol,int n,int max);   //����������seidelΪ��˹�����¶�������⺯��
	int i,j;
	float **A;    //�����άָ�룬�������ϵ������A
	float *B=new float[N]; //һάָ�룬��ŷ����ұߵ�����
	float *P=new float[N];  //��ʼ�²�ֵ
	A=new float *[N];    //ָ����ά����ָ���С
	  for(i=0;i<N;i++)
	   {
	   A[i]=new float[N];
	   }


	for(i=0;i<N;i++)   //��ʼ��B
	{
		B[i]=5;
		P[i]=1;  //��ʼ�²�ֵȫΪ1
	 for(j=0;j<N;j++)   //��ʼ��ϵ������A
	 {
	   if((j==i-1)&(i>0))  A[i][j]=-2;
	   else if(j==i) A[i][j]=12;
	   else if (j==i+1) A[i][j]=-2;
	   else A[i][j]=0;
	 }
	}


  Seidel(A,B,P,1e-6,N,20);  //�������¶�������ⷽ����

  delete []P;
  delete []B;
 for(i=0;i<N;i++)
   {
	  delete [] A[i];
   }
 delete []A;

getchar();
}

float Seidel(float**a,float*b,float *p,float tol,int n,int max)  //����������SeidelΪ��˹�����¶�������⣬aΪϵ������bΪ�����ұߵ���������pΪ��ʼ�²�ֵ��tolΪʵ�龫�ȣ�nΪ������ά����maxΪ���������� 
{
	int i,j,k;
	float temp=0,max1,max2;  //�����м����
	float *x=new float[n];    //x������ŷ�����Ľ�
	float *err=new float[n];  //errΪ�������
	float *rel=new float[n];  //relΪ������
	float xpre,eps=FLT_MIN;;  //eps��С������
	for(i=0;i<n;i++)
	{
	x[i]=p[i];
	}
	FILE *fp;//����ָ���ļ���ָ�����fp
	if((fp=fopen("X.txt","w"))==NULL)//������ļ���ʹfpָ����ļ�
     {
	printf("cannot open the file\n");//����򿪳����������ʧ��
    exit(0);//��ֹ����
     }


	for(k=0;k<max;k++)
	{
		printf("K is %d\n",k);   //���k�۲��������
		for(i=0;i<n;i++)
			{
				xpre=x[i];   //��ʱ���
				for(j=0;j<(n&i+1);j++)
				{
				if(i==j) continue;
				temp+=a[i][j]*x[i];
				}
			  x[i]=(b[i]-temp)/a[i][i];  //����ÿһ�ε�x
			  err[i]=fabs(xpre-x[i]);   //����������
			  rel[i]=err[i]/fabs(x[i]+eps);   //����������
			  temp=0;     //�м��������
				printf("x[%d]=%f  ",i,x[i]);    //���ÿһ�ε�x��err��rel
				printf("err[%d]=%f  ",i,err[i]);
				printf("rel[%d]=%f\n",i,rel[i]);
			}
		    printf("\n");
		   max1=err[0];
		   max2=rel[0];
			 for(i=0;i<n;i++)   //�ҵ������������������
				{
				   if(max1<err[i+1])  max1=err[i+1];
				   if(max2<rel[i+1])  max2=rel[i+1];
				 }
				 if(max1<tol||max2<tol) break;	  //�����������������������С��ʵ�龫�ȣ�����ѭ������������
	}

	for(i=0;i<n;i++)
	{
	fprintf(fp,"%f\n",x[i]);     //�����ս������ָ���ļ�
	}

	fclose(fp);   //�ر��ı�
	delete []x;
	delete []err;
	delete []rel;

	return 0;   //�޲�����Ҫ����
}
