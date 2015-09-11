/*���ļ�ʵ�ֲ������Ĳ�����΢�ֵ��㷨*/

#include <math.h>  //��ѧ����ͷ�ļ�
#include <float.h> //��Ӧ��С������
#include <stdio.h>
#include <stdlib.h> //fprint����

//��������
float diffcen(float (*f)(float),float x,float tol,int max1); //diffcenΪ���޷���������
float fa(float x);  //faΪa�����ѧ����
float fb(float x);  //fbΪb�����ѧ����
float fc(float x);  //fcΪc�����ѧ����
float fd(float x);  //fdΪd�����ѧ����
float fe(float x);  //feΪe�����ѧ����
	
/*******������**********************/
void main()
{

	float z1,z2,z3,z4,z5;
	//a��b��c��e��fΪ��Ӧ��Ŀ����⵼����λ��
	float a=1/sqrt(3.);
	float b=(1+sqrt(5.))/3;
	float c=1/sqrt(2.);
	float d=(1-sqrt(5.))/2;
	float e=0.0001;



	//�������Ĳ�ַ���⵼������
    z1=diffcen(fa,a,1e-6,100);
	z2=diffcen(fb,b,1e-6,100);
	z3=diffcen(fc,c,1e-6,100);
	z4=diffcen(fd,d,1e-6,100);
	z5=diffcen(fe,e,1e-6,100);

//	printf("%0.13f\n",z5);
	printf("%0.13f\n%0.13f\n%0.13f\n%0.13f\n%0.13f",z1,z2,z3,z4,z5);  //���ÿ��ĵ�������ֵ��0.13��ʾ��������ʾС�����13λ
	getchar();

	
}

/****�������Ĳ�ַ���⵼������****************/
float diffcen(float (*f)(float),float x,float tol,int max1) //*fΪ��ѧ������x��ʾ��x����⵼����tol�����ж����ֵ��max1Ϊѭ�������������
{
	int k;
	float h=0.1,err,err1,rel,p;
	float eps=FLT_MIN; //��С������
	float *D=new float[max1]; //������ż������н��
		FILE*fp;//����ָ���ļ���ָ�����fp
		fp=fopen("result.txt","w+");


/*	if((fp=fopen("result.txt","w"))==NULL)//������ļ���ʹfpָ����ļ�
	{
		printf("cannot open the file\n");//����򿪳����������ʧ��
		exit(0);//��ֹ����
	}
	*/



	D[0]=(-f(x+2*h)+8*f(x+h)-8*f(x-h)+f(x-2*h))/(12*h); //����k=0ʱ�ĵ�������ֵ
	printf("%f\n",D[0]); //���D[0]
	fprintf(fp,"%f\n",D[0]); //д���ı�

	for(k=1;k<max1;k++) //ѭ������k>0��Ľ��
	{
		if(k==1) //D[1]��������
		{
			h=h/pow(10.,k);
		    D[k]=(-f(x+2*h)+8*f(x+h)-8*f(x-h)+f(x-2*h))/(12*h); //��ѧ���㹫ʽ
			

			err=fabs(D[k]-D[k-1]);  //����һ��������
		    rel=err/(D[k]+eps); //����һ�����������

			printf("%d\t%f\t%f\n",1,D[k],rel);  //��������������������������
	        fprintf(fp,"%d\t%f\t%f\n",1,D[k],rel);  //д���ı�

		}

		else
		{
			 h=h/pow(10.,k);
			 err1=err;
			 D[k]=(-f(x+2*h)+8*f(x+h)-8*f(x-h)+f(x-2*h))/(12*h);  //��ѧ���㹫ʽ
			 err=fabs(D[k]-D[k-1]);  //����һ��������
		     rel=err/(D[k]+eps);  //����һ�����������
			printf("%d\t%f\t%f\n",k,D[k],rel);  //��������������������������
	        fprintf(fp,"%d\t%f\t%f\n",k,D[k],rel);  //д���ı�

		   if(err>=err1) break; //��������ʼ����������ѭ����������
		}
	
		p=D[k];  //ÿһ�εĽ������
		if(rel<tol) break;  //���������С��ָ��ֵ������ѭ������������
		
	}
	fprintf(fp,"%0.13f",p);
	fclose(fp);//�ر�fp��

	delete []D;
	return (p);  // �������Ľ�����

}
	
/******��Ŀ�е�a����ѧ����*************/
float fa(float x)
{
  float y;
  y=pow(x,5)*(pow(x,28)*(60*pow(x,12)-32)+233)-47*pow(x,2)-77;
  return (y);
}

/******��Ŀ�е�b����ѧ����*************/
float fb(float x)
{
  float y;
  y=tan(cos((sqrt(5.)+sin(x))/(1+pow(x,2))));
  return (y);
}

/******��Ŀ�е�c����ѧ����*************/
float fc(float x)
{
  float y;
  y=sin(cos(1/x));
  return (y);
}


/******��Ŀ�е�d����ѧ����*************/
float fd(float x)
{
  float y;
  y=sin(pow(x,3)-7*pow(x,2)+6*x+8);
  return y;
}

/******��Ŀ�е�e����ѧ����*************/
float fe(float x)
{
	 float y;
	 y=pow(x,pow(x,x));
	 return (y);

}


