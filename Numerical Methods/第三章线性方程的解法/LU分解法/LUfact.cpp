/*���ļ�ʵ���˲���LU�ֽⷨ������Է�������㷨*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>         //���д���ı���ͷ����

float lufact(float **a,float *b,int n);      //����������lufactΪLU�ֽ⺯��

void main()
{

	float **A;           //�����άָ�룬�������ϵ������
//	int i,j,n=4;
	int i,j,n=3;
	A=new float *[n];    //��ʼ����ָ����ά����ָ���С
	  for(i=0;i<n;i++)
	   {
	   A[i]=new float[n];
	   }
	  float b[4][4]={{1,3,5,7},{2,-1,3,5},{0,0,2,5},{-2,-6,-3,1}};  //��ά���飬��ֵΪϵ������
	  float c[3][3]={{4,3,-1},{-2,-4,5},{1,2,6}};
	   for (i=0;i<n;i++)    //forѭ������ϵ�������ֵ����ֵ����άָ��
           {
	         for(j=0;j<n;j++)
			 {
		//	   A[i][j]=b[i][j];   
			   A[i][j]=c[i][j];
			 }
	      }
	   float B[4]={1,2,3,4};    //����AX=B����B
	   float D[3]={1,2,3};
	//   lufact(A,B,4);    //����LU�ֽ⺯��,��ά���鲻��ֱ����Ϊ�������뺯������A�ö�άָ��
	   lufact(A,D,3);

	   for(i=0;i<n;i++)
	   {
	      delete []A[i];
	   }
	   delete []A;
	   getchar();         //�������д���

}




float lufact(float **a,float *b,int n)       //�������壬aΪϵ������bΪ�����ұ����ݣ���Ϊ����������һ�У�nΪ�������ά��
{
float solve(float **m,float **u,float *b,int n);      //����������solveΪ��LU�ֽ���X�ĺ���
float exchange(float **a,float **I,float *b,int n);   //����������exchange��ϵ������a�;���b�б任
  float **m,**u,**I;     //�����άָ��
  int i,j,k;
  float r=0,s=0;      //���������м����
    m=new float *[n];    //ָ����ά����ָ���С
	  for(i=0;i<n;i++)   //m��ΪΪ�����Ǿ���
	   {
	       m[i]=new float[n];
	   }
   u=new float *[n];    //ָ����ά����ָ���С
	  for(i=0;i<n;i++)   //u��Ϊ�����Ǿ���
	   {
		 u[i]=new float[n];
	   }

      I=new float *[n];    //ָ����ά����ָ���С
	  for(i=0;i<n;i++)    //I������λ�����������б任ʱ�ĳ��Ⱦ���P��
	   {
		 I[i]=new float[n];
	   }

 for (i=0;i<n;i++)       //��ʼ��m��u.I
  {
	for(j=0;j<n;j++)
	{
	    u[i][j]=0;       //uȫ��Ϊ0��
		if(i==j) 	
			{
				m[i][j]=1;     //mΪ��λ����
		       I[i][j]=1;     //IΪ��λ����
		   }
		else    
		{
			m[i][j]=0;
		    I[i][j]=0;
		}
	}
  }
    exchange(a,I,b,n);  //����exchange�����������б任

for(i=0;i<n;i++)     //forѭ��������LU�ֽ⣬����������Ǻ������Ǿ���
{
	for(j=0;j<n;j++)
	{
	if(i==0)  u[i][j]=a[i][j];        //�ȼ���u�ĵ�һ��
	if(j==0)  m[i][j]=a[i][j]/u[0][0];   //����m�ĵ�һ��
	if(i!=0&&j!=0)
	{
		if(j<i) 
		{
			for(k=0;k<j;k++)
			{
				s=s+m[i][k]*u[k][j];     //sΪ�м��������Ϊ�����
			}
			m[i][j]=(a[i][j]-s)/u[j][j];    //����m��Ԫ��
			s=0;           //�м�������㣬��һ�μ���ʱ������㿪ʼ
		}
		if(j>=i)
		{
		for(k=0;k<i;k++)
		{
			r=r+m[i][k]*u[k][j];    //rΪ�м��������Ϊ�����
		}
		u[i][j]=a[i][j]-r;     //���u��Ԫ��
		r=0;                //���㣬��һ����rʱ��Ϊ������һ��Ԫ��ֵ�˵��������Ǵ��㿪ʼ
		}
	}
	}

}

FILE*fp;//����ָ���ļ���ָ�����fp
if((fp=fopen("mu.txt","w"))==NULL)//������ļ���ʹfpָ����ļ�
{
	printf("cannot open the file\n");//����򿪳����������ʧ��
    exit(0);//��ֹ����
}

      fprintf(fp,"the  matrix m\n");
       for (i=0;i<n;i++)      //forѭ����������Ǿ���m
           {
	         for(j=0;j<n;j++)
			 {
			 printf("m[%d][%d] %f ",i,j,m[i][j]);
			 fprintf(fp,"%f ",m[i][j]);//��float�ͱ���A[i][j]�����fpָ����ļ��С�
			 }
			 fprintf(fp,"\n");
	      }
	   fprintf(fp,"the  matrix u\n");
      for (i=0;i<n;i++)    //forѭ����������Ǿ���u
           {
	         for(j=0;j<n;j++)
			 {
			printf("u[%d][%d] %f ",i,j,u[i][j]);
			fprintf(fp,"%f ",u[i][j]);
			 }
			 printf("\n");
			 fprintf(fp,"\n");
	      }
	  fclose(fp);//�ر�fp��
     solve(m,u,b,n);         //�������X�ĺ���

 	  for(i=0;i<n;i++)   //m��ΪΪ�����Ǿ���
	   {
	      delete []m[i];
		  delete []u[i];
		  delete []I[i];
	   }
	  delete []m;
	  delete []u;
	  delete[]I;

return 0;    //�޾���ֵ��Ҫ����
}

float solve(float **m,float **u,float *b,int n)    //������⺯����mΪ�����Ǿ���uΪ�����Ǿ���bΪ����������һ�У�nΪ���̵�ά��
{
	int i,j;
	float t=0,temp=0;      //���������м����
	float *y=new float[n];   //����һάָ�룬y������Ž�LY=B�õ���Y
	float *x=new float[n];   //����һάָ�룬x������Ž�UX=Y�õ���X����x��Ϊ�����������ս��
	
	y[0]=b[0]/m[0][0];   //����y[0]
	for(i=1;i<n;i++)
	{
	  for(j=0;j<i;j++)
	   {
	    t=t+m[i][j]*y[j];   //�м��������������
	   }
	  y[i]=b[i]-t;  //����y
	  t=0;     //�м��������
	}

	x[n-1]=y[n-1]/u[n-1][n-1];  //����x[n-1]
	for(i=n-2;i>=0;i--)
	{
		for(j=i+1;j<n;j++)
		{
		temp=temp+u[i][j]*x[j];   //�м��������������
		}
	   x[i]=(y[i]-temp)/u[i][i];   //����y
	   temp=0;          //�м��������
	}



	FILE*fp;//����ָ���ļ���ָ�����fp
if((fp=fopen("XY.txt","w"))==NULL)//������ļ���ʹfpָ����ļ�
{
	printf("cannot open the file\n");//����򿪳����������ʧ��
    exit(0);//��ֹ����
}
	for(i=0;i<n;i++)
	{
	printf("y[%d] %f\t",i,y[i]);    // ���Y
	fprintf(fp,"y[%d] %f\t",i,y[i]);
	printf("x[%d] %f\n",i,x[i]);    //���X
	fprintf(fp,"x[%d] %f\n",i,x[i]); 
	}
	fclose(fp);//�ر�fp��

	delete []x;
	delete []y;
	return 0;
}

float exchange(float **a,float **I,float *b,int n)  //�����б任������aΪ��ʼϵ������bΪ����������һ�У�IΪ��λ����nΪ������ά��
{
	int i,j,p;
	float c,d;
	float *b1=new float[n];       //����һάָ�룬��������б任֮���b
	for(j=0;j<n;j++)
	{
	   p=j;            //p������¼���е����ֵ���ڵ�����
		for(i=p;i<n-1;i++)
		{
		if(fabs(a[p][j])<fabs(a[i+1][j])) p=i+1;      //�ҵ����ֵ���ڵ�����
		}
		for(i=0;i<n;i++)
     	{
	    c=a[j][i];       
		a[j][i]=a[p][i];     //�����н���
		a[p][i]=c;
		d=I[j][i];
		I[j][i]=I[p][i];             //����λ�������ͬʱ�任���õ�LU�ֽ��е�P����
		I[p][i]=d;
     	}
	}

	for(i=0;i<n;i++)                
	{    b1[i]=0;
		for(j=0;j<n;j++)
		{
		b1[i]+=I[i][j]*b[j];	 //����P*B���õ��仯����ľ���b
		}
	}



		FILE*fp;//����ָ���ļ���ָ�����fp
			if((fp=fopen("AB.txt","w"))==NULL)//������ļ���ʹfpָ����ļ�
			{
				printf("cannot open the file\n");//����򿪳����������ʧ��
				exit(0);//��ֹ����
			}


	for(i=0;i<n;i++)
	{
	b[i]=b1[i];             //��b1���¸�ֵ��b,�����Ժ����ĵ���
	 printf("b[%d] %f ",i,b[i]);    //����б任���b
	 fprintf(fp,"b[%d] %f\n ",i,b[i]);
	}
	 for (i=0;i<n;i++)
        {
	      for(j=0;j<n;j++)
		  {
			  printf("%f  ",a[i][j]);   //����б任֮���a
			  fprintf(fp,"%f  ",a[i][j]); 
		  }
		  printf("\n");
		  fprintf(fp,"\n");
	     }
	fclose(fp);//�ر�fp��
	delete []b1;
	return 0;
}