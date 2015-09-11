/*���ļ�ʵ���������ն���ʽ�ƽ��㷨*/

#include <stdio.h>
#include <stdlib.h>         //���д���ı���ͷ����
   
double lagrange(double *x,double *y,double z,int n);   //����������lagrangeΪ�������ն���ʽ��ֵ����

void main()
{

	 const int N=6;
	 int k,max;
	double X[N]={1,2,3,4,5,6};    //�����Ա�������
	double Y[N]={66,66,65,64,63,63};   //�������������
	double step,z,y,y_mean,L,y0;   
	y0=0;
	step=0.001;   //������x����������ľ���
	L=X[N-1]-X[0];  //�����Զ����ľ���
	max=int((L/step));   //���������������ĸ���
	
		   FILE*fp;//����ָ���ļ���ָ�����fp
		if((fp=fopen("point3.txt","w"))==NULL)//������ļ���ʹfpָ����ļ�
		{
			printf("cannot open the file\n");//����򿪳����������ʧ��
			exit(0);//��ֹ����
		}

	for(k=0;k<=max;k++)   //ѭ���������ÿ��Ķ�Ӧ���������ն���ʽ��ֵ�ĺ�
	{
	   z=X[0]+k*step;
	   	fprintf(fp,"%f\t",z);   //�������������ı�
	   y=lagrange(X,Y,z,6);
	   	fprintf(fp,"%f\n ",y);  //�������������ı�
	   y0=y0+y;     //���������
	}
	fclose(fp);//�ر�fp��
	 printf("%f\n",y);
	y_mean=y0/(max+1);  //���ƽ��ֵ
	printf("%f",y_mean);

	getchar();
}

//���庯�����������ղ�ֵ����ʽ
double lagrange(double *x,double *y,double z,int n)  // *xΪ���������������飬*yΪ��Ӧ��ֵ���飬zΪ����δ֪����nΪ��ĸ���
{
	int i,j;
	double *L=new double[n];   //�����������ն���ʽϵ��
	double P,a,b;
	P=0;
	for(i=0;i<n;i++)   //����ÿһ��ϵ��
	{ 
	     a=1;   //��ʼ���м����
		 b=1;
	  for(j=0;j<n;j++) //forѭ������������˻���
	  {  
		  if (i==j) continue;
		  a=a*(z-x[j]);     
	      b=b*(x[i]-x[j]);
	  }
	  L[i]=a/b; 
	}
	printf("%f\t",z);

	for(i=0;i<n;i++)  //ѭ�������zֵ�����������ն���ʽ�ĺ���ֵ
	{
	    P+=y[i]*L[i];   
	}
	printf("%f\n",P);

	delete []L;

	return (P);      //�������յļ�����
}