/*���ļ�ʵ���˷����Է�������ţ��-����ɭ�㷨*/

#include <math.h>                //������ѧ����
#include <stdio.h>            //�����������
#include <float.h>            //��Ӧ��FLT_MIN�ĺ���

double eps=FLT_MIN;
int b,M;                //����ȫ�ֱ��� b�������Ϊ1��2��3,MΪ��Ҫ���Ľ����˴���Ӧ5��3��2

//��������
double fm(double x);    //��ѧ����
double df(double x);   //��ѧ������һ�׵���
double Newton (double p0,double tol,int max,double (*fm)(double),double (*df)(double)); //��������NewtonΪţ��-����ɭ�㷨

void main()            //������
{ 

	double z;                             //�������
	printf("Please input the number of title \n ");            //�����Ŀѡ��
	scanf("%d",&b);                                        //��Ÿ�ֵ��b
	printf("Please input the order M \n");                 //����������Ҫ��
	scanf("%d",&M);

	z=Newton(1,1e-7,1000,fm,df); //����ţ��-����ɭ�������
	printf("z is %0.8f",z);
	getchar();
	getchar();

}


//����ţ��-����ɭ���� p0��ʼ���Ƶ㣬tol��max���ļ��������fm����ָ��ָ����ѧ������dfΪ��һ�׵���
double Newton (double p0,double tol,int max,double (*fm)(double),double (*df)(double)) 
{

	int i;
	double err,rel;
	double pk,pkpre;
	pkpre=p0;
	for (i=0;i<max;i++)
	{
		pk=pkpre-M*fm(pkpre)/(df(pkpre)+eps); //ţ��-����ɭ������ʽ
		err=fabs(pk-pkpre);
		rel=err/(fabs(pk)+eps);
		pkpre=pk;
		printf ("p[%d] is %0.9f\n",i,pk);

	}
	return pk;

}

//fm��Ҫ������������
double fm(double x)
{
	
	double fx,f1,f2,f3;

	if (b==1)
	{
		fx=pow(x-2,5);
	}
	if (b==2)
	{
		fx=sin(pow(x,3));
	}
	if(b==3)
	{
	fx=(x-1)*log(x);
	}
	return fx;
}

//һ�׵������õ�������
double df(double x)
{
	double f(double x);
	double d,dx=1e-5;

  // df=5*pow(x-2,4);
    d=(f(x+dx)-f(x))/dx;
	return d;
}