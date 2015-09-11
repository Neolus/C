/*���ļ�ʵ��쳲�����������*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/***��������**********/
float fibona(float (*f)(float,int),int i,float a,float b,int n,FILE *fp);  //쳲���������
float findn(float (*f)(int),float a,float b,float tol);  //Ѱ����Ҫ��������N
float F(int n);  //���쳲�������
float f(float x,int i); //������ѧ����
float fa(float x); //a��d����ѧ��ʽ
float fb(float x);
float fc(float x);
float fd(float x);


void main()
{
	int i,N;
	float tol=1e-6;
	float res,ff;


	float A[4]={-2.4,0.8,0.5,1};  //������˵�
	float B[4]={-1.6,1.6,2.5,5}; //�����Ҷ˵�

	FILE *fp;
	fp=fopen("result.txt","w+");

	//һ���Լ���4��
	for(i=0;i<4;i++)
	{
		printf("the answer of %c\n",97+i);
		N=findn(F,A[i],B[i],tol); //���N
		res=fibona(f,i,A[i],B[i],N,fp); //����쳲��������������
		ff=f(res,i);

		printf("%f\t%f\n",res,ff); //��������е�ͺ���ֵ
		fprintf(fp,"%f\t%f\n",res,ff);//д���ı�
	}
	fclose(fp);//�ر��ı�
	getchar();

}


/****����쳲�������������***********/
float fibona(float (*f)(float,int),int i,float a,float b,int n,FILE *fp) //fΪ��ѧ������i��Ӧ��Ŀ�ţ�a��˵㣬b�Ҷ˵㣬nΪ����쳲��������Ķ�Ӧ��N��fpָ���ı�
{
	float c,d;
	int j;
	float r,e=0.01,z;

	for(j=n;j>2;j--)//ѭ��������е�����
	{  
		
		r=F(j-1)/F(j);
		if(j==3) c=a+(r-e)*(b-a); //j=3�������c
		else c=a+(1-r)*(b-a); //���c
	    d=a+r*(b-a); //���d

	  	printf("%f\t%f\t%f\t%f\n",a,c,d,b);
		fprintf(fp,"%f\t%f\t%f\t%f\n",a,c,d,b); 

	  if(f(c,i)>f(d,i))  //�ж���һ�������ȡֵ
	  {
		  a=c;
	  }
	  else
	  {
		  b=d;
	  }
	}

	printf("%f\t%f\n",a,b);//�����������
	fprintf(fp,"%f\t%f\n",a,b);

	z=(a+b)/2;  //���е�
	return z; //�����е�ֵ
}



/**�������N����*************/
float findn(float (*f)(int),float a,float b,float tol)
{
	float y;
	int i,n;

	y=(b-a)/tol;

	for(i=0;;i++)//����ѭ�����N
	{
	   if(f(i)>=y)  //��F(i)�ﵽҪ��ʱ����������
	   {
		   n=i;
		   break;
	   }
	}
	return n; //����n
}


/********�������쳲�����������*******/
float F(int n)
{
	//�����õݹ�������쳲������������ٴ����Ĳ���Ҫ����
	int *s=new int [n+1];
	s[0]=0;
	if(n==0) 
	{
		delete []s;
		return 0;
	}
	s[1]=1;
    if(n==1) 
	{
		delete []s;
		return 1;
	}
	else 
	{
	for(int i=2;i<=n;++i)
	{
		s[i]=s[i-1]+s[i-2];
	}
	    int t=s[n];
		delete []s;
		return t;
	}
	
}


/*****������ѧ��ʽ����*********/
float f(float x,int i)   //��x����ֵ��iΪ��Ӧ��Ŀ0-3��Ӧa-d
{
	float y;
	if(i==0) y=fa(x);
    if(i==1) y=fb(x);
	if(i==2) y=fc(x);
	if(i==3) y=fd(x);
	return y;
}

/***a����ѧ����*******/
float fa(float x)
{
  float y;

  y=exp(x)+2*x+x*x/2;
  return y;
}

/***b����ѧ����*******/
float fb(float x)
{
  float y;
  y=-sin(x)-x+x*x/2;
  return y;
}

/***c����ѧ����*******/
float fc(float x)
{
  float y;
  y=x*x/2-4*x-x*cos(x);
  return y;
}

/***d����ѧ����*******/
float fd(float x)
{
  float y;
  y=pow(x,3)-5*x*x+23;
  return y;
}

