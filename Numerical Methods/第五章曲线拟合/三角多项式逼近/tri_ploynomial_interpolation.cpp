/*���ļ�ʵ�����Ƕ���ʽ��ֵ�㷨*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>         //���д���ı���ͷ����
#define pi 3.1415927 //����pi
 float tpcof(float *x,float *y,float z,int M,int N);  //����������tpcof���Ƕ���ʽ����

void main()
{
   const int n=24;  //nΪ���ݵ�ĸ���
   float X[n]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24}; //ʱ��
   float Y[n]={58,58,58,58,57,57,57,58,60,64,67,68,66,66,65,64,63,63,62,61,60,60,59,58}; //�¶�

   int i,max1;
   float step,x,x1,step1;  
 
   step=0.1; //x�Ĳ���0.1
   max1=(X[n-1]-X[0])/step; //���������ѭ���Ĵ���

   step1=(2*pi)/(23); //���Ƕ���ʽ��-pi��pi�ĵ�x[k]

   float *t=new float [max1+1];
   float *X1=new float [max1+1];

   FILE *fp;//����ָ���ļ���ָ�����fp
		if((fp=fopen("tri.txt","w"))==NULL)//������ļ���ʹfpָ����ļ�
		 {
		printf("cannot open the file\n");//����򿪳����������ʧ��
		exit(0);//��ֹ����
		 }

		 for (i=1;i<=n;i++)
		 {
		 	X1[i]=-pi+i*step1; //-pi��piȡ�Ⱦ��
		 
		 }

/******ѭ���������Ƕ���ʽ����������x=1��24ʱ��֮����¶�*********/
   for (i=0;i<=max1;i++)
	   {
		    x=X[0]+i*step;  //�����е�ʱ��x
			x1=-pi+i*step*step1; //�������Ƕ���ʽϵ��aj��bj��-pi��pi�ĵȼ��ĵ�
			
           t[i]=tpcof(X1,Y,x1,7,n); //�������Ƕ���ʽ����

		   printf("%f\t%f\n",x,t[i]);
           fprintf(fp,"%f\t%f\n",x,t[i]);//��float�ͱ���x��t[i]]�����fpָ����ļ��С�
	   }
   fclose(fp); //�ر��ı�

   delete []t;
   delete []X1;
   getchar();
}



/********�������Ƕ���ʽ����****************/
float tpcof(float *x,float *y,float z,int M,int N) //xΪ-pi��pi�ĵȾ�㣬yΪ��Ӧ����¶ȣ�zΪĳ������ʱ�̣�MΪ���Ƕ���ʽ�Ľ�����NΪ�����ĸ���
{
	N=N-1;  //����ʱ��Nȡ������1
	float *a=new float [M+1]; //����a[j]
	float *b=new float [M+1]; //����b[j]

	float s1=0,s2=0,s3=0;
	int j,k;
	float T;


	 for(k=1;k<=N;k++)
		 {
		  s1+=y[k];
		 }
	 a[0]=s1*2/N;       //��������a[0]
	 printf("%f\n",a[0]);

	for (j=1;j<=M;j++)   //ѭ������a[j],b[j]
	{
		s1=0;  //��ʼ���м����
		s2=0;
	  for(k=1;k<=N;k++)   //�����
	  {
	  s1=s1+y[k]*cos(j*x[k]);
	  s2=s2+y[k]*sin(j*x[k]);
	  }
	  a[j]=s1*2/N; //����a[j]
	  b[j]=s2*2/N;   //����b[j]
	  printf("%f\t%f\n",a[j],b[j]);

	  s3=s3+a[j]*cos(j*z)+b[j]*sin(j*z);   //T�еĺ���������,Ϊzʱ�̵��¶�
	}
	T=a[0]/2+s3;  //T�ļ���ʽ

	delete []a;
	delete []b;
	return (T);   //���ؼ����ֵ

}
