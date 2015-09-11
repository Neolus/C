/*���ļ�ʵ�����Ʒ���⵼�����㷨*/

#include <math.h>  //��ѧ����ͷ�ļ�
#include <float.h> //��Ӧ��С������
#include <stdio.h>
#include <stdlib.h> //fprint����

//��������
float diffex(float (*f)(float),float x,float delta,float tol,int max1); //diffexΪ����΢�ַ���������
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


	//��������΢�ַ���⵼������
   z1=diffex(fa,a,1e-5,1e-6,100);
	z2=diffex(fb,b,1e-5,1e-6,100);
	z3=diffex(fc,c,1e-5,1e-6,100);
	z4=diffex(fd,d,1e-5,1e-6,100);
	z5=diffex(fe,e,1e-5,1e-6,100);


//	printf("%f",z5);
	printf("%f0.13\n%0.13f\n%0.13f",z1,z2,z3,z4,z5);  //���ÿ��ĵ�������ֵ��0.13��ʾ��������ʾС�����13λ
	getchar();
}

/****��������΢�ַ���⵼������****************/
float diffex(float (*f)(float),float x,float delta,float tol,int max1) //*fΪ��ѧ������x��ʾ��x����⵼����delta��tol�����ж����ֵ��max1Ϊѭ�������������
{
	int j,k;
	float h=0.1,err,err_p,rel,rel_p,p;
	float eps=FLT_MIN; //��С������
	float **D; //������ż������н��
		D=new float *[max1]; 
		for(k=0;k<max1;k++)
		{
		D[k]=new float [max1];
		}

		FILE*fp;//����ָ���ļ���ָ�����fp�����ڽ�����д���ı�
		fp=fopen("c.txt","w+");


	for(j=0;j<max1;j++)
	  {
	   for(k=0;k<=j;k++) //ѭ�����㵽D[k][k]��Ľ��
		{
		if(k==0) //�����һ��
			{
	    		D[j][0]=(f(x+powf(2,-j)*h)-f(x-powf(2,-j)*h))/(powf(2,-j+1)*h);
			}
		else //����������
			{
			    D[j][k]=D[j][k-1]+(D[j][k-1]-D[j-1][k-1])/(powf(4,k)-1);
			}
		}
	
	   if(j>0)
	   	{
			printf("%d\t",j); //�������
			fprintf(fp,"%d\t",j); //д������
			if(j==1) //��һ��
			{
			err=fabs(D[j][j]-D[j-1][j-1]);  //����������
			rel=err/fabs(D[j][j]); //����������
			printf("%f\t%f\t%0.7f\n",D[j][j],err,rel);
			fprintf(fp,"%f\t%f\t%0.7f\n",D[j][j],err,rel);

			}

			if(j>1) //������
			{
			rel_p=rel;
			err=fabs(D[j][j]-D[j-1][j-1]);  //����������
			rel=err/fabs(D[j][j]); //����������
			printf("%f\t%f\t%0.7f\n",D[j][j],err,rel);
			fprintf(fp,"%f\t%f\t%0.7f\n",D[j][j],err,rel);
			if(rel>rel_p) break; //��������ʼ����������
			}
		 if(err<delta||rel<tol)  break; //����������������������Ԥ��ֵ��������
	     p=D[j][j];
	    }

	}
    fprintf(fp,"%f\t%0.13f",D[0][0],p); //д��D[0][0],�������13λС��
	fclose(fp);//�ر�fp��

	for(k=0;k<max1;k++)
		{
		delete []D[k];
		}
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
