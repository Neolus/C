/*���ļ�ʵ�ֱ��������ߵ�����㷨*/


#include <math.h>  //��ѧ����ͷ�ļ�
#include <stdio.h>  //�������ͷ�ļ�
#include <stdlib.h>         //���д���ı���ͷ����

float bezier(float *a,float t,int n);  //����������bezier����Ϊ��������ֵ����

void main()
{

	/*****��ʼ����Ҫ�����鼰����********/
	const  int n1=4; //��һ�Σ�4����
	float X1[n1]={0,1,1,3};
	float Y1[n1]={0,2,1,0};
	const  int n2=5;  //�ڶ��Σ�5����
	float X2[n2]={3,4,5,6,7};
	float Y2[n2]={0,-1,-2,1,0};
	const int n3=4;   //�����Σ�4����
	float X3[n3]={7,4,2,0};
	float Y3[n3]={0,-3,-1,0};


	FILE*fp;//����ָ���ļ���ָ�����fp
		if((fp=fopen("XY1.txt","w"))==NULL)//������ļ���ʹfpָ����ļ�
		{
			printf("cannot open the file\n");//����򿪳����������ʧ��
			exit(0);//��ֹ����
		}
	FILE*fp1;//����ָ���ļ���ָ�����fp
		if((fp1=fopen("XY2.txt","w"))==NULL)//������ļ���ʹfpָ����ļ�
		{
			printf("cannot open the file\n");//����򿪳����������ʧ��
			exit(0);//��ֹ����
		}
    FILE*fp2;//����ָ���ļ���ָ�����fp
		if((fp2=fopen("XY3.txt","w"))==NULL)//������ļ���ʹfpָ����ļ�
		{
			printf("cannot open the file\n");//����򿪳����������ʧ��
			exit(0);//��ֹ����
		}


	int i, max1;
	float T=0;
	float step=0.01;
	max1=1/step; //����ѭ������
	float x,y;
 

	/******ѭ������t��0,1��**********/
	for(i=0;i<=max1;i++)
	{
		/****��һ������******/
		T=i*step;
		x=bezier(X1,T,n1);  //���ñ���������������t��0��1�����ж�Ӧ��x
		y=bezier(Y1,T,n1);   //���ñ���������������t��0��1�����ж�Ӧ��x
	    printf("%f\t%f\n",x,y);  //���x��y
		fprintf(fp,"%f\t%f\n",x,y); //�����ı�fp��������ͼ


		/****�ڶ�������******/
	    x=bezier(X2,T,n2);  
		y=bezier(Y2,T,n2);
	    printf("%f\t%f\n",x,y);
		fprintf(fp1,"%f\t%f\n",x,y);


		/****����������******/
	    x=bezier(X3,T,n3); 
		y=bezier(Y3,T,n3);
	    printf("%f\t%f\n",x,y);
		fprintf(fp2,"%f\t%f\n",x,y);

	}

  fclose(fp);//�ر�fp��
  fclose(fp1);
  fclose(fp2);

	getchar();


}



/*****���庯��������ֵ����*********/
float bezier(float *a,float t,int n)  //aΪ����Ŀ��Ƶ����ݣ�tΪ0��1��һ��ֵ����x��Ӧ��nΪ�����ĸ���
{
	n=n-1;  //��߽�Ϊ������1
	float Bi(float t,int i,int n); //����������BiΪ����i��n��Ӧ�Ĳ���˹̹����ʽ��ֵ

	float s=0; // ��ʼ�������
	int i;

	for (i=0;i<=n;i++)
	{
		s=s+Bi(t,i,n)*a[i]; //���������߹�ʽ
	}

	return (s);  //�������ļ�����

}


/***���岮��˹̹����ʽ*******/
float Bi(float t,int i,int n)  //tΪ�����0��1��ֵ��nΪ������iΪi������ʽ
{

	float facterial(int n);  //�������� facterialΪ�׳˺���
	float B;  
	float cni;
		 cni=facterial(n)/(facterial(i)*facterial(n-i)); //�������ʽϵ��
		 B=cni*pow(t,i)*pow(1-t,n-i);  //���㲮��˹̹����ʽ��ֵ
		return (B);  //���ؼ���ֵ
} 


/***����׳˺����������㲮��˹̹����ʽ*******/
float facterial(int n) // Ϊn�Ľ׳�
{
	int i;
	float f=1;  //�˻����ʼ��Ϊ1

	if(n==0) f=1; //0�Ľ׳�Ϊ1
	else
	{
		for(i=1;i<=n;i++)  //�����0�Ľ׳�
		{
			f=f*i;
	
		}
	}
	return (f); //���ؽ׳�ֵ
}