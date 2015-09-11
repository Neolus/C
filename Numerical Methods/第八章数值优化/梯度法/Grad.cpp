/*���ļ�ʵ���ݶȷ���⼫Сֵ�㷨*/
#include <math.h>
#include <stdio.h>


/*****��������******/
double* grad(double (*f)(double,double),double *p,double a,double b,double tol,FILE *fp);  //�ݶȺ�����ֵ
void solveS(double x,double y,double *s);  //�����������
double gema(double ga,double *s,double *t);//gama��Ӧ��ѧ���ʽ
double golden(double (*f)(double,double *,double *),double a,double b,double tol,double *s,double *p,FILE *fp); //�ƽ����ؽⵥ������ֵ
double f(double x,double y); //�������ѧ����
double fx(double x,double y);//ƫx
double fy(double x,double y);//ƫy


void main()
{
	double p[2]={15,-4}; //�������
	double A,B,tol,res;
	int i;
	double *D=new double [2];
	A=-100;
	B=100;
	tol=1e-6;  //ʵ�龫��

	FILE *fp;
	fp=fopen("result.txt","w+");

	D=grad(f,p,A,B,tol,fp); //�����ݶȺ�����ֵ


	for(i=0;i<2;i++)
	{
		printf("%0.8f\n",D[i]);
	}

	res=sqrt(f(15,-4)); //�����̾���
	printf("res is %0.8f\n",res);


	fclose(fp);
	getchar();

}


/***�����ݶȺ�����⼫ֵ����**********/
double* grad(double (*f)(double,double),double *p,double a,double b,double tol,FILE *fp) //f��ѧ��ʽ��p��������������a��b�������ƽ�ָ�ʱ�ķ�Χ��tolʵ�龫�ȡ�fpָ���ı�
{
	double s[2],sa,ta,r;
	double hmin;
	int i;
	solveS(p[0],p[1],s);  //���������������
	hmin=golden(gema,a,b,tol,s,p,fp); //���gama��Сֵ

	for(i=0;i<2;i++)
	{
		p[i]=p[i]+hmin*s[i];  //�����µ�������
		printf("%0.8f\t",p[i]);
		fprintf(fp,"%0.8f\t",p[i]);	
	}

	r=sqrt(f(p[0],p[1])); //���������ľ���
	printf("%0.8f\n",r);
	fprintf(fp,"%0.8f\n",r);


	sa=sqrt(s[0]*s[0]+s[1]*s[1]); 
	ta=hmin*sa; //����仯�ľ���



	if(fabs(ta)<10*tol)  return p;  //����仯����С�ھ��ȣ���������

	 p=grad(f,p,a,b,tol,fp); //�������������

	 return p;

}


/***�����������������Sk*********/
void solveS(double x,double y,double *s) //��(x,y)����⣬sΪ�����������
{
	double a[2],A;
	a[0]=fx(x,y); //ƫxֵ
	a[1]=fy(x,y);  //ƫyֵ
	A=sqrt(a[0]*a[0]+a[1]*a[1]);

	s[0]=-a[0]/A;   //��һ��
	s[1]=-a[1]/A;
}


/******����ƽ�ָ��*************/
double golden(double (*f)(double,double *,double *),double a,double b,double tol,double *s,double *p,FILE *fp) //fΪ��ѧ������iΪ��Ӧ��Ŀ0-3��Ӧa-d��aΪ��˵㣬bΪ�Ҷ˵㣬tolΪ���ȣ�fpָ���ı�
{
	double r;
	double a1,b1,c,d,length;
	double tc,td,z;
	r=0.5*(-1+sqrt(5.));
	length=b-a; 
	c=a+(1-r)*length;  //����ck
	d=b-(1-r)*length;  //����dk
	tc=f(c,s,p); //���������Ӧ�ĺ���ֵ
	td=f(d,s,p);

	if(tc<td)  //�ж���һ��ak��bk��ȡֵ
	{
		a1=a;
		b1=d;
	}
	else
	{
		a1=c;
		b1=b;
	}


	if(fabs(a1-b1)>tol)  //���û�����㾫�ȣ�����ϸ��
	{
		z=golden(f,a1,b1,tol,s,p,fp);
	}

	else
	{
		z=0.5*(a1+b1);  //ȡ���������е�Ϊ��ֵ��

	}


	return z;

}


/***��Ҫ������ѧ����**********/

double f(double x,double y)
{
	double s;
	s=(x-2)*(x-2)+(y-3)*(y-3)+(x*x+y*y-1)*(x*x+y*y-1);
	return s;
}
/****x��ƫ��*******/
double fx(double x,double y)
{
	double s;
	s=2*(x-2)+4*x*(x*x+y*y-1);
	return s;
}
/***y��ƫ��******/
double fy(double x,double y)
{
	double s;
	s=2*(y-3)+4*y*(x*x+y*y-1);
	return s;
}

/**�������gama�任���ʽ*******/
double gema(double ga,double *s,double *t) //��ga����ֵ��s��������������t���ڵ�������
{
	double x,y,res;
	x=t[0]+ga*s[0]; //�任����
	y=t[1]+ga*s[1];

	res=f(x,y);  //������
	return res;
}
