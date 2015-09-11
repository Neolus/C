/*���ļ�ʵ���ڵ�-�׵·���*/
#include <math.h>
#include <stdio.h>
#include <float.h>


double eps=FLT_MIN;

/***��������********/
void order(double (*f)(double,double,double,double,int),int k,double B[4],double W[4],double H[4],double L[4],double M[4]);//�������5��������
double *neder(double (*f)(double,double,double,double,int),int k,double *B,double *W,double *H,double *L,double *M,double tol,FILE *fp);//�ڵ¡��׵·���
void copy(double A[4],double C[4]); //��C��ֵ���Ƶ�A�С�CΪһ�������
double f(double x,double y,double z,double u,int i); //��ѧ��ʽ
double fa(double x,double y,double z); //a-c�����ѧ��ʽ
double fb(double x,double y,double z,double u);
double fc(double x,double y,double z,double u);



void main()
{
	double A[4][4]={{1,1,1,0},{0,1,0,0},{1,0,1,0},{0,0,1,0}}; //A�����ʼ�㣬��һ��һά���������һ���������
	double B[5][4]={{1,1,1,0.8},{1,0.8,1,1},{0.8,1,0.9,1},{1,0.9,0.8,1},{0.9,0.8,0.9,1.1}}; //B�����ʼ��
	double C[5][4]={{0.7,0.6,0.7,0.8},{0.8,0.7,1.0,0.9},{0.65,0.8,0.9,0.5},{1.0,0.8,0.7,0.9},{0.6,0.9,0.7,0.7}}; //C�����ʼ��

	FILE *fp; //fpָ���ı�
	fp=fopen("result.txt","w+");

	neder(f,1,B[0],B[1],B[2],B[3],B[4],1e-8,fp);//�����ڵ¶�-�׵º��������b�⣬�����������Ҫ��΢�޸Ĳ���

	int i,j;
	for(i=0;i<5;i++)  //�����������Ҫ���5����
	{
		for(j=0;j<4;j++)
		{
		printf("%0.8f\t",B[i][j]);  
		fprintf(fp,"%0.8f\t",B[i][j]);  //д���ı�
		}
		printf("\n");
		fprintf(fp,"\n");
	
	}

	fclose(fp);//�ر��ı�
	getchar();

}



/****�������պ���ֵ��С������**********/
void order(double (*f)(double,double,double,double,int),int k,double *B,double *W,double *H,double *L,double *M) //fΪ��ѧ������k��Ӧ��Ŀ�ţ�B��W��H��L��MΪ��Ҫ����ĵ�
{

	double y[5],tmax[4],tmin[4],th[4],tl[4],tm[4];
	double min,max,high,low;
	int i,nm,nn,nh,nl;

	//����5����ĺ���ֵ
	y[0]=f(B[0],B[1],B[2],B[3],k);
	y[1]=f(W[0],W[1],W[2],W[3],k);
	y[2]=f(H[0],H[1],H[2],H[3],k);
	y[3]=f(L[0],L[1],L[2],L[3],k);
	y[4]=f(M[0],M[1],M[2],M[3],k);

	min=y[0];
	max=y[0];


	for(i=0;i<5;i++)
	{
		if(y[i]>=max)  //�ҳ����㣬����������
		{
			max=y[i];
			if(i==0) copy(tmax,B);  
			if(i==1) copy(tmax,W);
		    if(i==2) copy(tmax,H);
		    if(i==3) copy(tmax,L);
			if(i==4) copy(tmax,M);
			nm=i;
		}
		if(y[i]<=min)    //�ҳ���С�㣬����������
			{
				min=y[i];
				if(i==0) copy(tmin,B);
				if(i==1) copy(tmin,W);
				if(i==2) copy(tmin,H);
				if(i==3) copy(tmin,L);
				if(i==4) copy(tmin,M);
				nn=i;
		    }
	}
	high=min;
	low=max;

	for(i=0;i<5;i++)
	{
		if(i==nn||i==nm) continue; //���������С��
		if((y[i]<=max)&(y[i]>=min)&(y[i]>high)) //�ҳ��δ�㣬����������
		{
			high=y[i];
			if(i==0) copy(th,B);
			if(i==1) copy(th,W);
			if(i==2) copy(th,H);
			if(i==3) copy(th,L);
            if(i==4) copy(th,M);
			nh=i;

		}
			if((y[i]<=max)&(y[i]>=min)&(y[i]<low)) //�ҳ���С�㣬����������
		{
			low=y[i];
			if(i==0) copy(tl,B);
			if(i==1) copy(tl,W);
			if(i==2) copy(tl,H);
			if(i==3) copy(tl,L);
            if(i==4) copy(tl,M);
			nl=i;
		}
	}
	for(i=0;i<5;i++) //Ѱ���м�㣬����������
	{
		if(i==nn||i==nm||i==nl||i==nh) continue;
		{
			if(i==0) copy(tm,B);
			if(i==1) copy(tm,W);
			if(i==2) copy(tm,H);
			if(i==3) copy(tm,L);
            if(i==4) copy(tm,M);
		}



	}


	copy(B,tmin);  //����ֵ��С��
	copy(W,tmax);  //����ֵ����
	copy(L,tl);  //����ֵ��С��
	copy(H,th);  //����ֵ�δ��
	copy(M,tm);  //����ֵ�м��

}


/****�ڵ�-�׵·�������***********/
double *neder(double (*f)(double,double,double,double,int),int k,double *B,double *W,double *H,double *L,double *M,double tol,FILE *fp)  //fΪ��ѧ������k��Ӧ��Ŀ�ţ�B��W��H��L��MΪ5�㣬tolΪʵ�龫�ȣ�fpָ���ı�
{
	order(f,k,B,W,H,L,M);  //�Ƚ������5��������

	double R[4],E[4],MM[4],C1[4],C2[4];
	double yr,ye,yb,yw,yh,yl,ym,yc1,yc2;
	int i;

	//�����õ�B�����W֮�������ֵ֮��ﵽʵ�龫��Ҫ�󣬷���B��
	if((fabs(W[0]-B[0])<tol)&&(fabs(W[1]-B[1])<tol)&&(fabs(W[2]-B[2])<tol)&&(fabs(W[3]-B[3])<tol))
	{return B;}




	for(i=0;i<4;i++) 
	{
		MM[i]=(B[i]+H[i]+L[i]+M[i])/4; //����4���ε�����
		R[i]=2*MM[i]-W[i];  //R��
		E[i]=2*R[i]-MM[i];  //��չ��E
	}

	//������㺯��ֵ
	yr=f(R[0],R[1],R[2],R[3],k);
	ye=f(E[0],E[1],E[2],E[3],k);
	yb=f(B[0],B[1],B[2],B[3],k);
	yw=f(W[0],W[1],W[2],W[3],k);
	yh=f(H[0],H[1],H[2],H[3],k);
	yl=f(L[0],L[1],L[2],L[3],k);
	ym=f(M[0],M[1],M[2],M[3],k);	


	printf("%0.8f\t%0.8f\t%0.8f\t%0.8f\t%0.8f\n",B[0],B[1],B[2],B[3],yb);
	fprintf(fp,"%0.8f\t%0.8f\t%0.8f\t%0.8f\t%0.8f\n",B[0],B[1],B[2],B[3],yb);


	if(yr<yw) //���R�㺯��ֵС��W��
	{
		if(ye<yr)//���E�㺯��ֵС��R��
		{
			copy(W,E);
		}
		else copy(W,R);
	}
	else //���R�㺯��ֵ��С��W��
	{
		for(i=0;i<4;i++)  //������
		{
			C1[i]=(W[i]+MM[i])/2;
			C2[i]=(R[i]+MM[i])/2;
		}
		yc1=f(C1[0],C1[1],C1[2],C1[3],k);
		yc2=f(C2[0],C2[1],C2[2],C2[3],k);

      if((yw>yc1)||(yw>yc2))
		  {
			if(yc1>yc2) copy(C1,C2);
			copy(W,C1);
		  }
	  else{  //������ĺ���ֵ��W���
		  for(i=0;i<4;i++) //���е���B����
			  {
				  L[i]=(L[i]+B[i])/2;
				  M[i]=(M[i]+B[i])/2;
				  H[i]=(H[i]+B[i])/2;			  
				  W[i]=(W[i]+B[i])/2;
			  }

	      }

	}

	B=neder(f,k,B,W,H,L,M,tol,fp);  //�����ݹ����
	return B; //����B������
}


/****���帴�����꺯��********/
void copy(double *A,double*C) //��C���긴�Ƶ�A��
{
	int i;
	for(i=0;i<4;i++)
	{
		A[i]=C[i];
	}
}



/***������ѧ����***********/
double f(double x,double y,double z,double u,int i) //�ڣ�x,y,z,u������ֵ��i��Ӧ��Ŀ��
{
	double s=0;
	if(i==0) s=fa(x,y,z);
	if(i==1) s=fb(x,y,z,u);
	if(i==2) s=fc(x,y,z,u);
	return s;
}


/***a����ѧ��ʽ****/
double fa(double x,double y,double z)
{
	double s;
	s=2*x*x+2*y*y+z*z-2*x*y+y*z-7*y-7*z;
	return s;
}

/***b����ѧ��ʽ****/
double fb(double x,double y,double z,double u)
{
	double s;
	s=2*(x*x+y*y+z*z+u*u)-x*(y+z-u)+y*z-3*x-8*y-5*z-9*u;
	return s;
}

/***c����ѧ��ʽ****/
double fc(double x,double y,double z,double u)
{
	double s;
	s=x*y*z*u+1/(x+eps)+1/(y+eps)+1/(z+eps)+1/(u+eps);
	return s;
}