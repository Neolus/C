/*���ļ�ʵ������Ӧ����*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define pi 3.14159265359


/******��������*************/
	double adpt(double (*f)(double,int),int i,double a,double b,double tol,FILE *fp); //����Ӧ���ֺ���
	double simprl(double (*f)(double,int),int i,double a,double b); //����ɭ���ֺ���
	double f(double x,int i);  //��ѧ����
	double fa(double x); //a-f����ѧ���ʽ
	double fb(double x);
	double fc(double x);
	double fd(double x);
	double fe(double x);
	double ff(double x);

void main()
{

	double A[7]={0,0,0.04,0,1/(2*pi),0};  //��������
	double B[7]={3,3,1,2,2,2};  //�������ޣ���Aһһ��Ӧ

	double res;
	int k;

	FILE*fp;//����ָ���ļ���ָ�����fp
	fp=fopen("result.txt","w+");

	for(k=0;k<6;k++)  //ѭ��һ�μ���6����
	{
		printf("the answer of %c\n",97+k);
		fprintf(fp,"the answer of %c\n",97+k);
		res=adpt(f,k+1,A[k],B[k],1e-5,fp);  //��������Ӧ���ֺ�������
		printf("%f\n",res);  //������
	    fprintf(fp,"%0.8f\n",res);  //д���ı�
	}

	fclose(fp);//�ر�fp��
	getchar();


}


/********��������Ӧ���ֺ���****************************/
double adpt(double (*f)(double,int),int i,double a,double b,double tol,FILE *fp) //*f��ѧ��ʽ��i��Ӧ����ţ�a�������ޣ�b�������ޣ�tol�����ϵ��ݲ*fpָ���ı�
{

	double c,h,a1,b1,a2,b2,eps,err;
	double s,s1,s2,temp=0,t1;
	double v,v1,v2;
	c=(a+b)/2;  //�е�
	h=(b-a)/2;  //����
	a1=a;  //�����Ϊ����
	b1=c;
	a2=c;
	b2=b;

    s=simprl(f,i,a,b);  //������������Ļ���
	s1=simprl(f,i,a1,b1);  //������1�Ļ���
	s2=simprl(f,i,a2,b2);  //������2�Ļ���
	err=fabs(s-(s1+s2))/10;  //����������ֺͷֶλ��ֵ����

	if(err<tol)   //���С���ݲ�������㣬�����������������֮��
	{
		t1=s1+s2;
	    printf("%f\t%f\t%0.12f\t%0.12f\t%0.9f\n",a,b,err,tol,t1);  
	    fprintf(fp,"%f\t%f\t%0.12f\t%0.12f\t%0.9f\n",a,b,err,tol,t1);
		temp=temp+t1;
		return (t1);
	}
	else  //���û�дﵽҪ��
	{
		eps=tol/2;  //�ݲ����
		v1=adpt(f,i,a1,b1,eps,fp);  //�������������ڽ�������Ӧ����
		v2=adpt(f,i,a2,b2,eps,fp);
		v=v1+v2;   
		return v;  //��������֮��
	}

}


/****��������ɭ���ֺ���********************/
double simprl(double (*f)(double,int),int i,double a,double b)  //*f��ѧ��ʽ��i��Ӧ��ţ�aΪ�������ޣ�bΪ��������
{

	double c,h;
	double s;
	c=(a+b)/2;  //�е�
	h=(b-a)/2;  //����
	s=h/3*(f(a,i)+4*f(c,i)+f(b,i));  //����ɭ���ּ��㹫ʽ

	return s;
}



/***����Ҫ������ѧ����**************/
double f(double x,int i)   //��x����ֵ��i����ڼ��������ѧ��ʽ
{
	double y=0;

	if(i==1) y=fa(x);
	if(i==2) y=fb(x);
	if(i==3) y=fc(x);
	if(i==4) y=fd(x);
	if(i==5) y=fe(x);
	if(i==6) y=ff(x);
	return y;
}

/*****a����ѧ����****************/
double fa(double x)
{
	double y;
	y=sin(2*x)/(1+pow(x,5));
	return y;
}

/*****b����ѧ����****************/
double fb(double x)
{
	double y;
	y=sin(4*x)*exp(-2*x);
	return y;
}


/*****c����ѧ����****************/
double fc(double x)
{
	double y;
	y=1/sqrt(x);
	return y;
}

/*****d����ѧ����****************/
double fd(double x)
{
	double y;
	y=1/(x*x+0.1);
	return y;
}

/*****e����ѧ����****************/
double fe(double x)
{
	double y;
	y=sin(1/x);
	return y;

}

/*****f����ѧ����****************/
double ff(double x)
{
	double y;
	y=2*sqrt(x)-x*x;
	return y;
}


