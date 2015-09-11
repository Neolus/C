/*���ļ�ʵ��΢�ַ��̵�����-����-�Ѷ�����*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


/*****��������******/
void RKF(double (*f)(double,double),double yk,double x0,double xn,double h,double tol,FILE *fp); //RKF����-����-�Ѷ�����
double fa(double tk,double yk); //fa��һ����Ŀ΢�ַ���
double fb(double tk,double yk); //fb�ڶ�����Ŀ΢�ַ���

void main()
{
	double y0=0;//��ʼ����
	double A[2],B[2],step,tol; //A����������˵㣬BΪ�Ҷ˵�

	step=0.1;
	tol=1e-7;  //�������
	A[0]=0;  
	B[0]=3;
	
	A[1]=0;
	B[1]=1;
	
		
	FILE*fp;//����ָ���ļ���ָ�����fp
	fp=fopen("A.txt","w+");

	RKF(fa,y0,A[0],B[0],step,tol,fp); //����RK��������һ��΢�ַ���
	fprintf(fp,"The answer of question B\n");
	RKF(fb,y0,A[1],B[1],step,tol,fp); //����RK�������ڶ���΢�ַ���

	fclose(fp); //�ر��ı�
	getchar();
}



/*****��������-����-�Ѷ��������΢�ַ��̺���***********/
void RKF(double (*f)(double,double),double yk,double x0,double xn,double h,double tol,FILE *fp)//f��Ҫ����΢�ַ��̣�yk��ʼ������x0΢����㣬xn΢���յ㣬h����,fpָ���ı�
{
	int i=0,j,m;
	double t1;

	//����-����-�Ѷ���������Ҫ�ĳ�ϵ��
	double a[5]={0.25,0.375,12./13,1.,0.5};
	double b[5][5]={{0.25},{3./32,9./32},{1932./2197,-7200./2197,7296./2197},{439./216,-8.,3680./513,-845./4104},{-8./27,2.,-3544./2565,1859./4104,-11./40}};
	double wy[5]={25./216,0,1408./2565,2197./4101,-0.2};
	double wz[6]={16./135,0,6656./12825,28561./56430,-9./50,2./55};


	double sumy,sumz,y[6],x[6],zk,s,err,hmin,yk0;
	double hmax;
	double k[6];

	hmin=h/64; //����Ӧ��С��������
	hmax=h*64; //����Ӧ��󲽳�����

	while(true)
	{
		sumy=0;
		sumz=0;

		//����k0-k5
     	k[0]=h*f(x0,yk);
/*		k[1]=h*f(t1+a[0]*h,yk+b[0][0]*k[0]);
		k[2]=h*f(t1+a[1]*h,yk+b[1][0]*k[0]+b[1][1]*k[1]);
		k[3]=h*f(t1+a[2]*h,yk+b[2][0]*k[0]+b[2][1]*k[1]+b[2][2]*k[2]);
		k[4]=h*f(t1+a[3]*h,yk+b[3][0]*k[0]+b[3][1]*k[1]+b[3][2]*k[2]+b[3][3]*k[3]);
		k[5]=h*f(t1+a[4]*h,yk+b[4][0]*k[0]+b[4][1]*k[1]+b[4][2]*k[2]+b[4][3]*k[3]+b[4][4]*k[4]);
   */
		for(j=1;j<6;j++)
		{
			x[j]=x0+a[j-1]*h;
			y[j]=yk;
			for(m=0;m<j;m++)
			{
				y[j]+=b[j-1][m]*k[m];
			}
			k[j]=h*f(x[j],y[j]);
		}

     //������Ե�yk+1
		for(j=0;j<5;j++) 
		{
			if (j==1) continue;
			sumy=sumy+wy[j]*k[j]; //k����Ȩ�ز����
		}
		yk0=yk+sumy;

		//����ȽϾ�ȷ��yk+1��zk+1
		for(j=0;j<6;j++) 
		{
			if (j==1) continue;
			sumz=sumz+wz[j]*k[j]; //k����Ȩ�ز����
		}
		zk=yk+sumz; //����yk+1

		err=fabs(zk-yk0); //�������

		if((err<tol)||(h<2*hmin))  //������ﵽ���Ȼ��߲���������С����ʱ������һ����
		{
	      t1=x0+h; //ÿһ��tk
		  
		  if((x0+hmin)>(xn+1e-7)) break; //����ӽ��߽��ʱ��ֹͣ����
	
		  yk=zk; //���þ�ȷ�Ľ�Ϊ�õ��ֵ
		  x0=t1; //��һ�������
		  
		  if(t1>xn) t1=xn; //�����߽��ȡ�߽��
		
		  printf("%0.8f\t%0.11f\t%0.8f\t%0.8f\n",t1,yk,err,h);
	      fprintf(fp,"%0.8f\t%0.11f\t%0.8f\t%0.8f\n",t1,yk,err,h); 

		}

		//������������Ų���
		s=0.84*pow(tol*h/err,0.25); 
		if((s<0.75)&&(h>=2*hmin)) h=h/2;
		if((s>1.5)&&(2*h<=hmax)) h=2*h;
	}
}


/****��һ��΢�ַ���*******/
double fa(double tk,double yk)
{
	double y;
	y=9*tk*exp(3*tk);
	return y;
}

/****�ڶ���΢�ַ���*******/
double fb(double tk,double yk)
{
	double y;
	y=2*atan(tk);
	return y;
}

