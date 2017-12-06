/* 1653633 ���� ��3 */
//4������
/*
�ж���͹����β������
input:������4-9����ÿ����ĺ�������
output:��͹�������������Ǿ������

PS: ������Ҫ�ĺ��� �ж����㹲�ߵĺ���f_ilinertest��������㹹�ɵĶ��������ĺ���f_dscompute
    ���õ���֮ǰ�ĺ��׹�ʽ������������ĺ���f_dtris
	��ά�����ʾƽ���ϵĵ㼯
    �����С define N�����ڴ��븴��
	�жϰ�����ε�˼·�ǣ�ȥ�㰼���γɵĶ���ε��������ԭ���
	f_dscompute task1:tag=0ʱ�����ε����  task2:tag=xʱ����ȥ��x��Ķ���ε��������ѭ���Ƚ�
	ͨ����ַ��ֵ
	���ѭ����ʱ�򱻿���
	��ҪΪ���Լ���ѭ��������Ҫ��� i,j ɶ������Ŀ�����������ر����׸�죡��������
*/


#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;
#define N 8
int mmp = 0;

//function declaration
int f_ilinertest(double x1, double y1, double x2, double y2, double x3, double y3);
double f_dscompute(double b[][N], int n, int tag);
double f_dtris(double dx1, double dy1, double dx2, double dy2, double dx3, double dy3);



int main()
{
    //input
	double a_ddotsxy[2][N] = { 0 }, itest(0), itag(0);
	int ii(0), ij(0),ik(0),inum(0);
	while (1)
	{
		cout << "Please input the number of dots(4-7):" << endl;
		cin >> inum;
		if (!cin.good()|| inum<4 || inum>7)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else
			break;
	}

	cout << "Please input the X_Y position in clockwise or anticlockwise:" << endl;
	for (ii = 1; ii <= inum; ii++)
	{
		while (2)
		{
			cout << "�������" << ii << "����������꣺" << endl;
			cin >> a_ddotsxy[0][ii] >> a_ddotsxy[1][ii];
			if (!cin.good())
			{
				cin.clear();
				cin.ignore(1024, '\n');
				continue;
			}
			else
				break;
		}
	}

	//liner testing
	for(ii=1;ii<=inum;ii++)
		for (ij = 1; ij <= inum; ij++)
			for (ik = 1; ik <= inum; ik++)
				if (f_ilinertest(a_ddotsxy[0][ii], a_ddotsxy[1][ii], a_ddotsxy[0][ij], a_ddotsxy[1][ij], a_ddotsxy[0][ik], a_ddotsxy[1][ik]) == 1)
				{
					if (ii == ij || ii == ik || ik == ij)
						continue;
					cout << "����͹" << inum << "����" << endl;
					return -1;
				}

	//size computation & testing

	itag = f_dscompute(a_ddotsxy, inum, 0);
	if (itag == -1)
	{
		cout << "����͹" << inum << "����" << endl;
		return -1;
	}

	itag = f_dscompute(a_ddotsxy, inum, 0);
	for (ii = 1; ii <= inum; ii++)
	{
		//cout << "+++++++++++" << endl;
		itest = f_dscompute(a_ddotsxy, inum, ii);
		if (itest >= itag)
		{
			cout << "����͹" << inum << "����" << endl;
			return -1;
		}
	}

	cout << "͹" << inum << "���ε����=" << itag << endl;

	return 0;
}


//function defination
int f_ilinertest(double x1,double y1,double x2,double y2,double x3,double y3)
{
	if (((fabs(x1 - x2) <= 1e-6) && (fabs(x1 - x3) <= 1e-6)) || ((fabs(y1 - y2) <= 1e-6) && (fabs(y1 - y3) <= 1e-6)) )
		return 1;
    else if (fabs((x3 - x1) / (y3 - y1) - (x2 - x1) / (y2 - y1)) <= 1e-5)
		return 1;//����
	else
		return 0;
}

//size computation
double f_dscompute(double b[][N],int n, int tag)  //tag=0,����������tag=i,��ȱʡ��i����󹹳ɵĶ���ε����
{
	double gx(0), gy(0), s[N] = {0},a[2][N];
	int i, j, k;
	if (tag == 0)
	{
		for (i = 1; i <= n; i++)
		{
			a[0][i] = b[0][i];
			a[1][i] = b[1][i];
		}
	}
	else
	{
		for (i = 1,j=1; j <= n; j++,i++)
		{
			if (j == tag)
			{
				i--;
				continue;

			}
			a[0][i] = b[0][j];
			a[1][i] = b[1][j];
		}
		n--;
	}

	for (i = 1; i <= n; i++)
	{
		gx += a[0][i];
		//cout << endl << a[0][i];
		gy += a[1][i];
		//cout << endl << a[1][i];
	}
	gx /= n;
	gy /= n;
	for (j = 1; j < n; j++)
	{
		s[j] = f_dtris(gx, gy, a[0][j], a[1][j], a[0][j + 1], a[1][j + 1]);
		if (s[j] == -1)
			return -1;
	}
	s[n]= f_dtris(gx, gy, a[0][1], a[1][1], a[0][n], a[1][n]);
	if (s[n] == -1)
		return -1;
    
	for (k = 1; k <= n; k++)
		s[0] += s[k];

	return s[0];
}


double f_dtris(double dx1, double dy1, double dx2, double dy2, double dx3, double dy3)
{

	
	//cout << ++mmp << endl;
	//printf("%f %f %f %f %f %f\n", dx1, dy1, dx2, dy2, dx3, dy3);   
	double dc12, dc23, dc31, dp, ds;
	dc12 = sqrt((dx1 - dx2)*(dx1 - dx2) + (dy1 - dy2)*(dy1 - dy2));
	dc23 = sqrt((dx3 - dx2)*(dx3 - dx2) + (dy3 - dy2)*(dy3 - dy2));
	dc31 = sqrt((dx1 - dx3)*(dx1 - dx3) + (dy1 - dy3)*(dy1 - dy3));

	if ((dc12 < (dc23 + dc31)) && (dc23 < (dc31 + dc12)) && (dc31 < (dc12 + dc23)))
	{
		dp = (dc12 + dc23 + dc31) / 2;
		ds = sqrt(dp*(dp - dc12)*(dp - dc23)*(dp - dc31));
	//	cout << "!!!!!!!!!" << 1 << endl;
		return ds;
	}
	else
	{
		cout << "!!!!!!!!!" << 0 << endl;
		return -1;   //�������������Ĳ����������ε����
	}
}



