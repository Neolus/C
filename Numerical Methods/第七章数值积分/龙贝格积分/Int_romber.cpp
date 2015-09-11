/*���ļ�ʵ�����������*/
//�������ϴ󣬺�ʱ��
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define pi 3.14159265359
//��������
double rom(int i,int n,double a,double b,double tol,FILE*fp);  //romΪ��������

void main()
{

	double res,tole=1e-10;  //toleΪʵ�龫��
	double A[2]={0,0};  //��������
	double B[2]={2,1}; //��������
	

	FILE*fp1;//����ָ���ļ���ָ�����fp
	fp1=fopen("result.txt","w+");

	printf("the question a\n");
	fprintf(fp1,"the question a\n");
	res=rom(1,25,A[0],B[0],tole,fp1);  //���ú������a��
	printf("%0.10f\n",res);
	fprintf(fp1,"%0.10f\n",res);  //������д���ı�

	printf("the question b\n");
	res=rom(2,25,A[0],B[1],tole,fp1);   //���ú������a��
	printf("%0.10f\n",res);
	fprintf(fp1,"%0.10f\n",res);  //������д���ı�

	fclose(fp1);  //�ر�fp
	getchar();


}



//������������
double rom(int i,int n,double a,double b,double tol,FILE *fp)  //i��Ӧ��Ŀ�ţ�nΪ�������ά�ȣ�aΪ�������ޣ�aΪ�������ޣ�tolΪʵ�龫�ȣ�*fpΪ����ָ��FILE�ļ�
{
		double romber(int i,int J,int K,double a,double b);  //RomberΪ�����������������ļ�����
		double f(int i,double x);  //��ѧ������i��Ӧ���
		double RJ=0,RJpre,err;
		int j;

			for(j=0;j<=n;j++)  //ѭ�����ӵ�����������
			{
				if(j==0)
				{
				  RJ=romber(i,j,j,a,b);   //����R(0,0)
				  printf("%d\t%0.11f\t",j,RJ);
				   fprintf(fp,"%d\t%0.11f\t",j,RJ); //д���ı�
				}
				 
			   if(j>0)
			   {
				    RJpre=RJ;
				   RJ=romber(i,j,j,a,b);  //����R(J,J)
				    printf("%d\t%0.11f\t",j,RJ);
				   err=fabs(RJ-RJpre);  //������R(J,J)-R(J+1,J+1)
				    fprintf(fp,"%d\t%0.11f\t",j,RJ);  //д���ı�
				   if(err<tol)  break; //����������С�ھ���Ҫ����ֹ����
			   
			   }
			   printf("\n");
			   fprintf(fp,"\n");
		  }
        
        return RJ;  //��������R(J,J)



}

/**********����ݹ����λ��ּ��㹫ʽ*********/
double suctrap(int i,int j,double a,double b)
{
	double f(int i,double x);  //fΪ��ѧ����
	double T1,T,step,temp=0;
	int k,M;
	M=pow(2.,j-1);
	step=(b-a)/pow(2.,j);

	if (j==0)    //�����0��
		{
			T=step/2*(f(i,a)+f(i,b));
	    }
	else
	{
		double *x=new double[2*M+1];
		for(k=0;k<=2*M;k++)  //�������Ϊ2M��
		{
				x[k]=a+step*k;
		}

		for(k=1;k<=M;k++)
		{
			temp+=f(i,x[2*k-1]);  //���к���ֵ���
		}

		T1=suctrap(i,j-1,a,b);  //�ݹ����
		T=T1/2+step*temp;  //���ι�ʽ���Ľ��
		temp=0;//�м��������
		delete []x;  //�ͷ�һάָ��
	}
	return T;  

}


/*********������������ֵĵ���һ��ļ��㹫ʽ****************************/
double romber(int i,int J,int K,double a,double b) //i��Ӧ��ţ�J��KΪ����R(J,K)�aΪ�������ޣ�bΪ��������
{

    double suctrap(int i,int j,double a,double b);  //���ι�ʽ����
	double f(int i,double x);  

	double R,R1,R11;

	if(K==0)  //�����һ�У�Ϊ���ι�ʽ�ļ���Ľ��
	{
		R=suctrap(i,J,a,b); 
	}
	else  //�����У��ݹ����
	{
		R1=romber(i,J,K-1,a,b);
		R11=romber(i,J-1,K-1,a,b);
		R=R1+(R1-R11)/(pow(4.,K)-1);
	}

	return R;  //���ؼ�����


}


/********������Ҫ����������Ŀ��Ӧ����***********/
double f(int i,double x)  //i��Ӧ��Ŀ�ţ�1��Ӧa��,x��Ӧ����⺯��
{
	//����������a-f��Ӧ��Ŀ����ѧ��ʽ
	double fa(double x);
	double fb(double x);

	double y=0;
	//��Ӧ��ϵ����1-6�ֱ��Ӧa-f
	if(i==1)  y=fa(x);
	if(i==2)  y=fb(x);


	return y;  //��������y
}


/*****a����ѧ����********/
double fa(double x)
{
	double y;
	y=sqrt(4*x-x*x);

	return y;
}

/*****b����ѧ����********/
double fb(double x)
{
	double y;
	y=4/(1+x*x);
	return y;
}




