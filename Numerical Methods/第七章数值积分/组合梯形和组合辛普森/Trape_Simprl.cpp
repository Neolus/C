/*���ļ�ʵ����������ֹ�ʽ���������ɭ��ʽ�����ֵ������㷨*/
#include <math.h>
#include<stdio.h>
#include<float.h>

# define pi 3.14159265

//��������
double difflim2(int j,double x,double tol,int max1); //difflim�������׵���
double difflim4(int j,double x,double tol,int max1); //difflim�������׵���
double trape(int j,double *x,double h,int M);  //trape������ι�ʽ
double simprl(int j,double *x,double h,int M); //simprlΪ�������ɭ��ʽ
double compute(double a,double b,int M,double *x);   //compute�������������Ҫ�ĵ�
int solveM2(double a,double b,double dif2,double tol);  //solveM������㾫��Ҫ���Mֵ
int solveM4(double a,double b,double dif2,double tol);  //solveM������㾫��Ҫ���Mֵ



void main()
{
	int M1,M2=20,i,j;
	double h,res,dif;
	double difmax=0;
	double *X1=new double [M2+1];

	//0-6��Ӧa��e��ѧ�����ģ����������ޣ�AΪ���ޣ�BΪ����
	double A[6]={-1,0,0.25,0,0,0};
	double B[6]={1,1,4,4,2,pi};


	/******������ι�ʽ����********/
	for(j=0;j<6;j++)  // ����ѭ��ʵ��6����ļ��㣬j+1��Ӧ���
	{
		printf("the answer of %c is\n",97+j);
		compute(A[j],B[j],M2,X1);  //�������ΪM2��
	    difmax=0;
		for(i=0;i<=M2;i++)  //��ÿһ�������2�׵���
		{ 
			dif=fabs(difflim2(j+1,X1[i],1e-5,100));
			if(dif>difmax) difmax=dif;  //�ҳ����׵��������ֵ
		}
		M1=solveM2(A[j],B[j],difmax,1e-9);  //�������Ķ��׵������ֵ��������������������ʵ�龫��Ҫ��ķֶ���M
		printf("the max of dif2 and M are %f\t%d\n",difmax,M1);

	   double *X=new double [M1+1];
	   h=compute(A[j],B[j],M1,X);  //�����䰴M�ֶ�
       res=trape(j+1,X,h,M1);  //����������ι�ʽ������
		printf("step and result are %f\t%0.10f\n\n",h,res);
	  delete []X;
	}

	/***********�������ɭ����************************/
	printf("composite simpson\n\n");
	for(j=0;j<6;j++)
	{
		printf("the answer of %c is\n",97+j);
		compute(A[j],B[j],M2,X1);  //�������ΪM2��
	    difmax=0;
		for(i=0;i<=M2;i++)  //��ÿһ�������4�׵���
		{ 
			dif=fabs(difflim4(j+1,X1[i],1e-5,100));
			if(dif>difmax) difmax=dif;  //�ҳ��Ľ׵��������ֵ
		}
		M1=solveM4(A[j],B[j],difmax,1e-9);  //���������Ľ׵������ֵ��������������������ʵ�龫��Ҫ��ķֶ���M
		printf("the max of dif2 and M are %f\t%d\n",difmax,M1);

	   double *X2=new double [2*M1+1];
	   h=compute(A[j],B[j],2*M1,X2);  //�����䰴M�ֶ�
       res=simprl(j+1,X2,h,M1);  //�����������ɭ��ʽ������
		printf("step and result are %f\t%0.10f\n\n",h,res);
		delete []X2;
	}
	
	//�ͷ��������е�newָ��

	delete []X1;

	getchar();
	
}



/****���弫�޷������׵�������****************/
double difflim2(int j,double x,double tol,int max1) //*fΪ��ѧ������x��ʾ��x����⵼����tol�����ж����ֵ��max1Ϊѭ�������������
{
	int k;
	double h=0.1,err,err1,rel,p;
	double eps=FLT_MIN; //��С������
	double *D=new double[max1]; //������ż������н��
	double f(int i,double x);
	double g ;
	g=f(j,x);
	D[0]=(f(j,(x+pow(10.,0)*h))-f(j,x-pow(10.,0)*h))/(2*h*pow(10.,0)); //����k=0ʱ�ĵ�������ֵ


	for(k=1;k<max1;k++) //ѭ������k>0��Ľ��
	{
		if(k==1) //D[1]��������
		{
		    D[k]=(f(j,x+pow(10.,-k)*h)-2*f(j,x)+f(j,x-pow(10.,-k)*h))/(pow(h*pow(10.,-k),2)); //��ѧ���㹫ʽ

			err=fabs(D[k]-D[k-1]);  //����һ��������
		    rel=err/(D[k]+eps); //����һ�����������

		}

		else
		{
			 err1=err;
			 D[k]=(f(j,x+pow(10.,-k)*h)-2*f(j,x)+f(j,x-pow(10.,-k)*h))/(pow(h*pow(10.,-k),2));  //��ѧ���㹫ʽ
			 err=fabs(D[k]-D[k-1]);  //����һ��������
		     rel=err/(D[k]+eps);  //����һ�����������
		   if(err>=err1) break; //��������ʼ����������ѭ����������
		}

		p=D[k];  //ÿһ�εĽ������
	
		if(rel<tol) break;  //���������С��ָ��ֵ������ѭ������������

	}
	delete []D;
	return (p);  // �������Ľ�����

}




/****���弫�޷�����Ľ׵�������****************/
double difflim4(int j,double x,double tol,int max1) //i��Ӧ��Ŀ�ţ�1��Ӧa����x��ʾ��x����⵼����tol�����ж����ֵ��max1Ϊѭ�������������
{
	int k;
	double h=0.1,err,err1,rel,p;
	double eps=FLT_MIN; //��С������
	double *D=new double[max1]; //������ż������н��
	double f(int i,double x); //��ѧ����

	D[0]=(f(j,x+pow(10.,0)*h)-2*f(j,x)+f(j,x-pow(10.,0)*h))/pow(h,4); //����k=0ʱ�ĵ�������ֵ


	for(k=1;k<max1;k++) //ѭ������k>0��Ľ��
	{
		if(k==1) //D[1]��������
		{
		    D[k]=(f(j,x+2*pow(10.,-k)*h)-4*f(j,x+pow(10.,-k)*h)+6*f(j,x)-4*f(j,x-pow(10.,-k)*h)+f(j,x-2*pow(10.,-k)*h))/(pow(h*pow(10.,-k),4)); //��ѧ���㹫ʽ

			err=fabs(D[k]-D[k-1]);  //����һ��������
		    rel=err/(D[k]+eps); //����һ�����������

		}

		else
		{
			 err1=err;
			 D[k]=(f(j,x+2*pow(10.,-k)*h)-4*f(j,x+pow(10.,-k)*h)+6*f(j,x)-4*f(j,x-pow(10.,-k)*h)+f(j,x-2*pow(10.,-k)*h))/(pow(h*pow(10.,-k),4)); //��ѧ���㹫ʽ
			 err=fabs(D[k]-D[k-1]);  //����һ��������
		     rel=err/(D[k]+eps);  //����һ�����������
		   if(err>=err1) break; //��������ʼ����������ѭ����������
		}

		p=D[k];  //ÿһ�εĽ������
	
		if(rel<tol) break;  //���������С��ָ��ֵ������ѭ������������

	}
	delete []D;
	return (p);  // �������Ľ�����

}



/******����������ι�ʽ������*********/
double trape(int j,double *x,double h,int M)  //j��Ӧ��Ŀ�ţ�1��Ӧa��*xΪ��������������������ޣ�hΪ������MΪ�ֶ���
{
	double y=0;
	int i;
	double f(int i,double x); //��ѧ����

	for(i=1;i<M;i++)  //�Գ�ȥ��β����ĺ���ֵ���
	{
	  y+=f(j,x[i]);
	}

	y=h*((f(j,x[0])+f(j,x[M]))/2+y);  //������β����ֵ����������յĻ��ֽ��
	return y;  //�������ĺ���ֵ
}

/******����������зֶϵ�ĺ�����ĺ���****************/
double compute(double a,double b,int M,double *x)  //aΪ�ֶ���㣬bΪ�ֶ��յ㣬MΪ�ֶ�����*x����������еĵ��X����
{
	int i;
	double step;
	step=fabs(a-b)/M;  //���㲽��
	for(i=0;i<=M;i++)
	{
	   x[i]=a+i*step;  //�������е������
	}
	return step;  //ֻ���ز���

}

/*****�����������ʵ�龫��M�ĺ���*************/
int solveM2(double a,double b,double dif2,double tol)  //aΪ�������ޣ�bΪ�������ޣ�dif2Ϊ���׵��������ֵ��tolΪʵ��Ҫ��ľ���
{
	double len;
	double re;
	int M;

	len=b-a;  //���䳤��
	re=len*sqrt(len*dif2/(12*tol));   //����M
	M=int(re)+1;  //ȡ��+1

	return M;  //����M
}


int solveM4(double a,double b,double dif4,double tol)  //aΪ�������ޣ�bΪ�������ޣ�dif2Ϊ���׵��������ֵ��tolΪʵ��Ҫ��ľ���
{
	double len;
	double re;
	int M;

	len=b-a;  //���䳤��
	re=pow((pow(len,5)*dif4/(180*16*tol)),0.25);   //����M
	printf("%f\n",(pow(len,5)*dif4/(180*16*tol)));
	printf("%f\n",re);
	M=int(re)+1;  //ȡ��+1

	return M;  //����M
}



/******�����������ɭ������*********/
double simprl(int j,double *x,double h,int M)  //j��Ӧ��Ŀ�ţ�1��Ӧa����*xΪ��������������������ޣ�hΪ������MΪ�ֶ�����һ��
{
	double f(int i,double x);
	double y=0;
	int i;

	for(i=1;i<2*M;i++)  //�Գ�ȥ��β����ĺ���ֵ���
	{
		if(i%2==0)   y+=2*f(j,x[i]);
		else
		{ y+=4*f(j,x[i]);}
	}

	y=h/3*(f(j,x[0])+f(j,x[2*M])+y);  //������β����ֵ����������յĻ��ֽ��
	return y;  //�������ĺ���ֵ
}



/********������Ҫ����������Ŀ��Ӧ����***********/
double f(int i,double x)  //i��Ӧ��Ŀ�ţ�1��Ӧa��,x��Ӧ����⺯��
{
	//����������a-f��Ӧ��Ŀ����ѧ��ʽ
	double fa(double x);
	double fb(double x);
	double fc(double x);
	double fd(double x);
	double fe(double x);
	double ff(double x);
	double y=0;
	//��Ӧ��ϵ����1-6�ֱ��Ӧa-f
	if(i==1)  y=fa(x);
	if(i==2)  y=fb(x);
	if(i==3)  y=fc(x);
	if(i==4)  y=fd(x);
	if(i==5)  y=fe(x);
	if(i==6)  y=ff(x);

	return y;  //��������y
}


/*****a����ѧ����********/
double fa(double x)
{
	double y;
	y=1/(1+x*x);

	return y;
}

/*****b����ѧ����********/
double fb(double x)
{
	double y;
	y=2+sin(2*sqrt(x));
	return y;
}


/*****c����ѧ����********/
double fc(double x)
{
	double y;
	y=1/sqrt(x);
	return y;
}


/*****d����ѧ����********/
double fd(double x)
{
	double y;
	y=x*x*exp(-x);
	return y;
}


/*****e����ѧ����********/
double fe(double x)
{
	double y;
	y=2*x*cos(x);
	return y;
}

/*****f����ѧ����********/
double ff(double x)
{
	double y;
	y=sin(2*x)*exp(-x);
	return y;
}

