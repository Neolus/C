/*���ļ�ʵ������С������������㷨*/
#include <stdio.h>

float A,B;    //����ȫ�ֱ���A��B���ֱ�Ϊy=Ax+B�е�ϵ��
float lsline(float *x,float *y,int N);      //����������lslineΪ��С���˷�������Ϻ���

void main()
{
	int i,n; 
	printf("please input the number of digits\n n= "); //��ʾ�����ĸ���
	scanf("%d",&n);           //�������������n
	float *xk=new float [n];   //����һάָ�룬xk����������ݵĺ�����
	float *yk=new float [n];   //����һάָ�룬yk����������ݵ�������
	printf("please input X[k]\n");
	for(i=0;i<n;i++)
	{
	scanf("%f",&xk[i]);  //�������ݵĺ�����
	}
	printf("please input Y[k]\n");
	for(i=0;i<n;i++)
	{
	scanf("%f",&yk[i]);   //�������ݵ�������
	}
	for(i=0;i<n;i++)
	{
	printf("%f\t%f\n",xk[i],yk[i]);  //�����ʾ��������
	}
	lsline(xk,yk,n);   //������С���˺���

	printf("A is %f\nB is %f",A,B);   //�����ʾ���ռ����ֵA��B

	delete []xk;
	delete []yk;
	getchar();
	getchar();
	getchar();   //����cmd����
}


/*********������С�������Ժ���*************************/
float lsline(float *x,float *y,int N)   //������lsline��*xΪ�����ĺ����꣬*yΪ�����꣬nΪ����ĵ�ĸ���
{
	int i;
	float sx,sx2,sy,sxy;    //��������������
	sx=0;
	sx2=0;
	sy=0;
	sxy=0;
	for(i=0;i<N;i++)  //ѭ�����ʽ
	{
	sx2=sx2+x[i]*x[i];   //sx2Ϊx^2�ĺ�
	sx=sx+x[i];    //sxΪx�ĺ�
	sy=sy+y[i];    //syΪy�ĺ�
	sxy=sxy+x[i]*y[i];   //sxyΪxy�ĺ�
	}


	A=(N*sxy-sx*sy)/(N*sx2-sx*sx);   //����С���˹�ʽ�����A
	B=(sy-sx*A)/N;  //�����B

	return 0;  //����Ҫ����ֵ

}