/*���ļ�ʵ��ţ�ٶ���ʽ��⵼�����㷨*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


/*****��������*******/
float diffnew(float *x,float *y,float t,int n);  //diffnew����Ϊţ��΢���󵼺���
float Compute(float (*f)(float),float a,float b,int n,float *x,float *y);  //Compute����Ϊ����㼰���Ӧ�ĺ���f��ֵ
 float f1(float x);  //f1Ϊ��ѧ����


void main()
{

	float x0,xn,step,t1,z;
	int i;
	int N=20; //ȡ��ĸ���
	float *X=new float[N]; //��ŷֶϵ��ֵ
	float *Y=new float[N];  //��ŵ��Ӧ����ѧ����ֵ

	FILE*fp;//����ָ���ļ���ָ�����fp
    fp=fopen("20.txt","w+");  //�����ı�

	x0=0.1; //��ʼ��
	xn=2;   //�յ�
	step=(xn-x0)/(N-1); //����
	Compute(f1,x0,xn,N,X,Y); //���ú��������������X��Y
	
	//�����ÿ�����Ӧ�ĵ���ֵ
	for(i=0;i<N;i++)
	{
	  t1=x0+i*step;
	  z=diffnew(X,Y,t1,N); //����ţ��΢�ֺ���
	  printf("%0.9f\t%0.9f\n",t1,z);  //�������ֵ�����Ӧ�㣬
	  fprintf(fp,"%0.9f\t%0.9f\n",t1,z);  //�����������Ӧֵд���ı�
	}
	fclose(fp); //�ر��ı�
	delete []X;
	delete []Y;
	getchar();
}


/*******����ţ��΢�ֺ���****************/
float diffnew(float *x,float *y,float t,int n)  //x�������顢yΪx��Ӧ�ĺ���ֵ��t��ʾ��t����⵼����nΪ��ĸ���
{
	int i,j,k;
	float dif,temp,s;

	float *A=new float[n];  //A��Ŷ���ʽϵ��
	for(i=0;i<n;i++)
	{
	  A[i]=y[i]; //����ʼֵ
	}

	
	for(i=1;i<n;i++) //����ѭ�����������ʽϵ��
	{
	  for(j=n-1;j>=i;j--)
	  {
		  A[j]=(A[j]-A[j-1])/(x[j]-x[j-i]);
	  }

	}

	dif=A[1];//difΪ���ĵ���ֵ

	for(i=2;i<n;i++)  //ѭ�����������ĵ���ֵ
	{
		s=0; //��ͱ�������ʼֵ
		for(k=0;k<i;k++)
			{
			temp=1; //���˱�������ʼֵ
			for(j=0;j<i;j++)
				{
				  if(j==k) continue;
				  temp*=t-x[j];
				}
			s=s+temp;
			}
		dif=dif+A[i]*s; //����
	}
	delete []A;
	return (dif); //���ص���ֵ
}





/*****����������麯��************/
float Compute(float (*f)(float),float a,float b,int n,float *x,float *y)  //fΪ��Ҫ�������ѧ������aΪ���������㣬bΪ��������յ㣬nΪȡ�������x������ź����꣬y�������������
{
	int i;
	float step;

	step=fabs(a-b)/(n-1);//����
	for(i=0;i<n;i++)
	{
		x[i]=a+i*step;  //���������
		y[i]=f(x[i]);  //����������

	}
	return 0;

}
/*****��������������ѧ����*****/
float f1(float x)
{
	float y1;
	y1=log(x); //��������
	return (y1);


}