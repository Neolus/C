/*���ļ�ʵ�ֽ�����Է��̵Ķ��ַ�*/

#include <stdio.h>         //�����������
#include <math.h>         //������ѧ����
#include <float.h>      //��Ӧ��FLT_MIN�ĺ���

double Bisection (double a0  ,double b0,double tol,int max);    //�������������ַ�����

void main ()              //������
{

	double a0  , b0,root;                                      //����ĳЩ����
	printf ("Please input area []=" );                          //�����ʾ������ַ��������˵�
	scanf("%lf %lf",&a0,&b0);                                   //���������˵�ֵ���������a0��b0

	root=Bisection(a0,b0,1e-8,1000);                          //���ö��ַ�������a0��b0��ʾ���ַ��������˵㡣1e-10Ϊ���������ж�ֵ��1000Ϊ����������
//	printf ("The root is %0.10f",root);                        //������ĸ�����%0.10f������10λС��
	getchar();                                            //�������д���
	getchar();
}



double Bisection (double a0,double b0,double tol,int max)      //���ַ���������ָ������������a0��b0��ʾ���ַ��������˵㣬tolΪ���������ж�ֵ��maxΪ����������
{
	double f(double x);        //����������f��x��Ϊ��Ҫ����ʵ���������ѧ����                      
	int i;
	double *a=new double;          //����a b c����ָ�룬������Ŷ˵�ֵ��cΪa b�е㡣
	double *b=new double;           
	double *c=new double;
	double m=f(c[0]);                     //m�������f��c����ֵ������ʼ��
	a[0]=a0;                              //������a����ֵ
	b[0]=b0;                                //������b����ֵ
	if (f(a[0])*f(b[0])>0)              //�ж���������������˵�ĺ���ֵͬ�ţ�������޽���ʾ��
	
	{
	 printf ("There is no root in this area ");
	}
	else{                                //�˵㺯��ֵ��ţ���ִ�ж��ַ��㷨
	    for (i=0;i<=max;i++)             //forѭ����μ���
	     {
		  c[i]=(a[i]+b[i])/2;            //ÿ�μ����е�ֵ
			if(f(a[i])*f(c[i])>0)        //����е�ֵ��a�ĺ���ֵͬ��
			{
				a[i+1]=c[i];           //��a����һ��Ϊ��ǰ��cֵ
				b[i+1]=b[i];           //b�򱣳ֲ���
				m=f(c[i]);            //���е�ĺ���ֵ�����m
			}
			else b[i+1]=c[i],a[i+1]=a[i];   // ����е���˵�a�����b����һ��Ϊ��ǰ��c��a�򱣳ֲ���
			printf (" c[%d] is %0.10f\n ",i,c[i]);   //���ÿһ��c
			printf (" f(c[%d]) is %0.10f \n",i,m);      //���ÿһ���е�ĺ���ֵ������۲�
		    if (fabs(m)<tol) break;                     //���е�ĺ���ֵ����Ԥ�辫��ʱ��ֹͣѭ������ֹ����
			
	      }
		  printf ("The root is %0.10f",c[i-1]);                        //������ĸ�����%0.10f������10λС��
          return c[i-1];                     //���أ��е�ֵ
	     }


}

double f(double x)                           //��������������ѧ����
{       float eps=FLT_MIN;                     //eps��С������
		double f,p=300;                  //���������pΪÿ��֧���Ľ��300
		f=(p/(x/12+eps))*(pow((1+x/12),240)-1);           //ʵ����ѧ����
		f=f-500000;
		return f;                     //���غ���ֵ
}

