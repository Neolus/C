/*���ļ�ʵ�ַ����Է��̵Ĳ�����ⷨ*/

#include <math.h>                         //������ѧ����
#include <stdio.h>                        //�����������
#include <float.h>                        //��Ӧ��FLT_MIN�ĺ���

double fixpt(double (*g) (double),double p0,double tol, int max);     //���������������㺯��
double g(double x);												   //�������������������ʵ�ʺ���g��x��

void main()                                                      //������
{   

	 double z;
	 z=fixpt(g,1.2,1e-12,1000);   //�������ã�gΪ���庯����1.2Ϊ����������ĳ�ʼֵ��1e12Ϊ������;��������ж�ֵ��1000Ϊ����������max
     printf("p is %0.12f",z);                 //����������㷨������ֵ,%0.12f��ʾ���ֵС��λ������12λ
	 getchar();                         //�������д�
	 getchar();
	 getchar();
}


 double fixpt(double (*g) (double),double p0,double tol,int max)  //���庯���������㷨����fixpt�����������и����������ͣ�double (*g) (double)Ϊ����ָ�룬p0Ϊ�����ʼ�㣬tolΪ����������ж�ֵ��maxΪ�������
{
	 double res,err, rel,eps=FLT_MIN;                                //������Ҫ�õ��ı������壬FLT_MINΪfloat��С��
	 double *p=new double[max];                                     //����һ��ָ�룬�����洢����g��x����x�ĵ�ַ
  //   double *p=new double[max];
	   p[0]=p0;                                             //��ʼ��p��0��ʹ��Ϊ����������ĳ�ʼֵ
		int i;
		for(i=0;i<max-1;i++)                                  //����forѭ�������ж�μ���
		{
		p[i+1]=g(p[i]);                                       //�������㷨��ʽ
		err=fabs(p[i+1]-p[i]);								//�������err�ļ���
		rel=err/(fabs(p[i+1])+eps);						   //������rel�ļ��㣬��err/abs(p[i+1]),epsΪfloat��С����������֤��ĸ��Ϊ��
     	 printf("p[%d] is %0.12f\n",i,p[i]);     //���ÿ�ε�p[i],����۲�
		if((err<tol)||(rel<tol)) break;                     //�������͵����������Ԥ��ֵʱ��ֹѭ��
		}
		
		if(i==max-1)                                      //�����ѭ�����㵽Ԥ��������ʱ��û����ֹ���㣬���maximum number of iterations exceed
		{
			printf("maximum number of iterations exceed\n");             //"\n"����
		}
		res=p[i];
		
		delete[]p;
		return res;                     //�����ķ���ֵ;

}


double g(double x)                       //���������ʵ����ѧ����g��x��
{
	double gx;
	gx=pow(x,x-cos(x));                        //g(x)�ľ�������ʽ
	return gx;                           //���غ���������
}

