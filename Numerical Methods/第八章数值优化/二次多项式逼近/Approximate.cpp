#include <stdio.h>
#include <math.h>

/******��������*************/
double inith(double a,double b);  //��ʼ��h
double findpoint(double (*f)(double,int),int i,double p0,double h,double tol,FILE *fp); //���αƽ�����
double hmin(double (*f)(double,int),int i,double p0,double p1,double p2,double h); //����hmin
double f(double x,int i); //������ѧ����
double fa(double x); //a��d����ѧ��ʽ
double fb(double x);
double fc(double x);
double fd(double x);




void main()
{
	int i;
	double tol=1e-6;
	double res,ff,h,p0;


	double A[4]={-2.4,0.8,0.5,1};  //������˵�
	double B[4]={-1.6,1.6,2.5,5}; //�����Ҷ˵�

	FILE *fp;  //ָ���ı�
	fp=fopen("result.txt","w+");

	//����4����Ŀ
	for(i=0;i<4;i++)
	{
		printf("the anser of question %c\n",97+i);
		h=inith(A[i],B[i]); //��ʼ��h
		p0=(A[i]+B[i])/2;  //���������е�
		res=findpoint(f,i,p0,h,tol,fp);  //����Ѱ�ҵ㺯��������ֵp
		ff=f(res,i);  //����f(p)
		printf("%0.7f\t%0.7f\n",res,ff);
		fprintf(fp,"%0.7f\t%0.7f\n",res,ff); 
	}

	fclose(fp); //�ر��ı�
	getchar();



}

/*****�����ʼ��h����**********/
double inith(double a,double b) //aΪ��˵㣬bΪ�Ҷ˵�
{
	double h;
	if(a+1<b)  h=1;  //����a��b�����ʼ��h
	else h=0.5;
	return h;
}


/****������αƽ�����*********/
double findpoint(double (*f)(double,int),int i,double p0,double h,double tol,FILE *fp) //f��ѧ������i��Ӧ��ţ�p0��Ѱ��㣬h������tol���ȣ�fpָ���ı�
{
	double p1,p2;
	double f0,f1,f2;
	double m;

	m=f(p0+0.00001,i)-f(p0-0.00001,i);  //����p0��ĵ����ķ���

	if(m>0)  h=-fabs(h); //����h������
	else h=fabs(h);


	p1=p0+h;
	p2=p0+2*h;

	f0=f(p0,i); //���㴦�ĺ���ֵ
	f1=f(p1,i);
	f2=f(p2,i);

	printf("P are %0.7f\t%0.7f\t%0.7f\n",p0,p1,p2);
	printf("f are %0.7f\t%0.7f\t%0.7f\n",f0,f1,f2);

	fprintf(fp,"%0.7f\t%0.7f\t%0.7f\n",p0,p1,p2);

	if((f0>f1)&&(f1>f2))  //f(p0)���
	    {
		  h=2*h;  //�����ӱ�
		 p0=findpoint(f,i,p0,h,tol,fp);  //����Ѱ��3��
	    }
	if(f0<f1)  //f(p0)��С
		{
			h=h/2;  //��������
		   p0=findpoint(f,i,p0,h,tol,fp);  //����Ѱ��3��
	    }
	else   //����������������
	{    
	  h=hmin(f,i,p0,p1,p2,h);  //����hmin
	  p0=p0+h;  //�ı�p0
	    if(fabs(h)<tol) //�ﵽ����Ҫ��
	  {   printf("h is <tol %0.7f\n",h);
		  return p0;  //��������p0
	  }
	  p0=findpoint(f,i,p0,h,tol,fp);  //û�дﵽ���ȣ�����Ѱ�ҵ�
	}

	return p0;
}


/****����hmin�ļ��㺯��*******/
double hmin(double (*f)(double,int),int i,double p0,double p1,double p2,double h)
{
	h=h*(4*f(p1,i)-3*f(p0,i)-f(p2,i))/(4*f(p1,i)-2*f(p0,i)-2*f(p2,i));
	return h;

}


/*****������ѧ��ʽ����*********/
double f(double x,int i)   //��x����ֵ��iΪ��Ӧ��Ŀ0-3��Ӧa-d
{
	double y;
	if(i==0) y=fa(x);
    if(i==1) y=fb(x);
	if(i==2) y=fc(x);
	if(i==3) y=fd(x);
	return y;
}

/***a����ѧ����*******/
double fa(double x)
{
  double y;

  y=exp(x)+2*x+x*x/2;
  return y;
}

/***b����ѧ����*******/
double fb(double x)
{
  double y;
  y=-sin(x)-x+x*x/2;
  return y;
}

/***c����ѧ����*******/
double fc(double x)
{
  double y;
  y=x*x/2-4*x-x*cos(x);
  return y;
}

/***d����ѧ����*******/
double fd(double x)
{
  double y;
  y=pow(x,3)-5*x*x+23;
  return y;
}


