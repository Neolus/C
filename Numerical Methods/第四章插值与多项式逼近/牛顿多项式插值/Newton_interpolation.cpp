/*���ļ�ʵ��ţ�ٶ���ʽ��ֵ�㷨*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>         //���д���ı���ͷ����

float Newinter(float*x,float *y,float c,int n);  //����������NewinterΪţ�ٲ�ֵ����

void main()
{

	int N=6; //��ֵ��ĸ���
	float X[6]={1,2,3,4,5,6};  //��ֵ��ĺ�����
	float Y[6]={66,66,65,64,63,63}; //��ֵ���������
	float step,z,y,y_mean,L,y0;
	int k,max;
	   FILE*fp;//����ָ���ļ���ָ�����fp
		if((fp=fopen("point3.txt","w"))==NULL)//������ļ���ʹfpָ����ļ�
		{
			printf("cannot open the file\n");//����򿪳����������ʧ��
			exit(0);//��ֹ����
		}


		y0=0;
		step=0.0001;   //������x����������ľ���
		L=X[N-1]-X[0];  //�����Զ����ľ���
		max=int((L/step));   //���������������ĸ���


		for(k=0;k<=max;k++)   //ѭ���������ÿ��Ķ�Ӧ���������ն���ʽ��ֵ�ĺ�
			{
			   z=X[0]+k*step;
			   printf("%f\t",z);
	   			fprintf(fp,"%f\t",z);   //�������������ı�
			   y=Newinter(X,Y,z,6);
			   printf("%f\n",y);
	   			fprintf(fp,"%f\n ",y);  //�������������ı�
			   y0=y0+y;     //���������
			}

	fclose(fp);//�ر�fp��
//	 printf("%f\n",y);
	y_mean=y0/(max+1);  //���ƽ��ֵ
	printf("%f",y_mean);


	getchar();
}

//����ţ�ٶ���ʽ��ֵ����
float Newinter(float*x,float *y,float c,int n)   //*xΪ������X���꣬*yΪ������Y���꣬cΪ����x��nΪ����ܸ���
{
	float **a;     //aΪ���̱�ϵ��
	float *p=new float [n+1];
	float temp=1;     //tempΪ�м����
	float P=0;
	int i,j;
	a=new float *[n];   //ָ����άָ���С
		for(i=0;i<n;i++)
		{
		a[i]=new float [n];
		}

		for (i=0;i<n;i++)   //��ʼ����άָ�룬ȫ0����
	      {
		    for(j=0;j<n;j++)
			{
			a[i][j]=0;
			}
		}

	for (i=0;i<n;i++)     //�������ϵ��
		{
			a[i][0]=y[i];  //��һ��ֱ�ӵó�
	        for(j=1;j<=i;j++)
			{
				if (i==0) break;
				a[i][j]=(a[i][j-1]-a[i-1][j-1])/(x[i]-x[i-j]);   
		   }
	}

	/*
	 FILE*fp1;//����ָ���ļ���ָ�����fp
		if((fp1=fopen("cofficent.txt","w"))==NULL)//������ļ���ʹfp1ָ����ļ�
		{
			printf("cannot open the file\n");//����򿪳����������ʧ��
			exit(0);//��ֹ����
		}

     for (i=0;i<n;i++)
	      {
		    for(j=0;j<n;j++)
			{
			printf("%f\t",a[i][j]);     
			fprintf(fp1,"%f\t",a[i][j]);  //�����̾���д���ı�
			
			}
				printf("\n");
				fprintf(fp1,"\n");
		}
	
	 fclose(fp1);//�ر�fp��
	 */
	
	for (i=0;i<n;i++)   //����ѭ��������ţ�ٶ���ʽ�ľ����Ӧ����ֵ
	  {
		temp=1; //��ʼ��
		for(j=0;j<i;j++)
		{
			if (i==0) break;
		    temp=temp*(c-x[j]);   //�˻���
		}
		P=P+a[i][i]*temp;  //PΪţ�ٶ���ʽ�Ĵ���x��ֵ
		  
    	}
	return (P);
/*   //�����Ҫ��ÿһ��ţ�ٶ���ʽ����ĳ��򣬲��Ƽ����������ü��临��
	  p[0]=a[0][0];
	for (i=0;i<n-1;i++)
	{
		for(j=0;j<=i;j++)
		{
			if (i==0) break;
		temp=temp*(c-x[j]);
		}

	p[i+1]=p[i]+a[i+1][i+1]*temp;
	temp=1;
	}
	return (p[5]);
*/

	for(i=0;i<n;i++)
		{
		delete []a[i];
		}
	delete []a;
	delete []p;
}

