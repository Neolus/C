/*���ļ�ʵ����ֵ�Ż��еĻƽ�������*/

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

/*****��������*********/
float golden(float (*f)(float,int),int i,float a,float b,float tol,FILE*fp);  //�ƽ�ָ����
float f(float x,int i); //������ѧ����
float fa(float x); //a��d����ѧ��ʽ
float fb(float x);
float fc(float x);
float fd(float x);


void main()
{
	int i;
	float A[4]={-2.4,0.8,0.5,1};  //������˵�
	float B[4]={-1.6,1.6,2.5,5}; //�����Ҷ˵�
	float res,ff;

     FILE *fp;//����ָ���ļ���ָ�����fp
	 fp=fopen("result.txt","w+");

	 //����4����Ŀ
	for(i=0;i<4;i++)
	{
		printf("the answer of %c\n",97+i);
		res=golden(f,i,A[i],B[i],1e-6,fp);  //���ûƽ�ָ��
		ff=f(res,i); //���㼫ֵ
		printf("%0.7f\t%0.7f\n",res,ff); 
		fprintf(fp,"%0.7f\t%0.7f\n",res,ff);  //����д���ı�
	}

	fclose(fp);//�ر�fp��
	getchar();
}


/******����ƽ�ָ��*************/
float golden(float (*f)(float,int),int i,float a,float b,float tol,FILE *fp) //fΪ��ѧ������iΪ��Ӧ��Ŀ0-3��Ӧa-d��aΪ��˵㣬bΪ�Ҷ˵㣬tolΪ���ȣ�fpָ���ı�
{
	float r;
	float a1,b1,c,d,length;
	float tc,td,z;
	r=0.5*(-1+sqrt(5.));
	length=b-a; 
	c=a+(1-r)*length;  //����ck
	d=b-(1-r)*length;  //����dk
	tc=f(c,i); //���������Ӧ�ĺ���ֵ
	td=f(d,i);

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


	printf("%0.7f\t%0.7f\t%0.7f\t%0.7f\n",a,c,d,b);
	fprintf(fp,"%0.7f\t%0.7f\t%0.7f\t%0.7f\n",a,c,d,b);  //����д���ı�

	if(fabs(a1-b1)>tol)  //���û�����㾫�ȣ�����ϸ��
	{
		z=golden(f,i,a1,b1,tol,fp);
	}

	else
	{
		z=0.5*(a1+b1);  //ȡ���������е�Ϊ��ֵ��
		printf("%0.7f\t%0.7f\n",a1,b1);
		fprintf(fp,"%0.7f\t%0.7f\n",a1,b1);
	}

	return z;

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

