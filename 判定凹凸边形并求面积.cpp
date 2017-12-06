/* 1653633 贡畅 计3 */
//4编译器
/*
判定凹凸多边形并求面积
input:边数（4-9），每个点的横纵坐标
output:是凸就输出面积，不是就输出否

PS: 两个主要的函数 判定三点共线的函数f_ilinertest，求任意点构成的多边形面积的函数f_dscompute
    还用到了之前的海伦公式求三角形面积的函数f_dtris
	二维数组表示平面上的点集
    数组大小 define N，便于代码复用
	判断凹多边形的思路是：去点凹点形成的多边形的面积大于原面积
	f_dscompute task1:tag=0时求多边形的面积  task2:tag=x时，求去掉x点的多边形的面积，再循环比较
	通过地址传值
	多次循环的时候被坑了
	不要为难自己：循环变量不要设成 i,j 啥玩意儿的看不清楚，还特别容易搞混！！！！！
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
			cout << "请输入第" << ii << "个顶点的坐标：" << endl;
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
					cout << "不是凸" << inum << "边形" << endl;
					return -1;
				}

	//size computation & testing

	itag = f_dscompute(a_ddotsxy, inum, 0);
	if (itag == -1)
	{
		cout << "不是凸" << inum << "边形" << endl;
		return -1;
	}

	itag = f_dscompute(a_ddotsxy, inum, 0);
	for (ii = 1; ii <= inum; ii++)
	{
		//cout << "+++++++++++" << endl;
		itest = f_dscompute(a_ddotsxy, inum, ii);
		if (itest >= itag)
		{
			cout << "不是凸" << inum << "边形" << endl;
			return -1;
		}
	}

	cout << "凸" << inum << "边形的面积=" << itag << endl;

	return 0;
}


//function defination
int f_ilinertest(double x1,double y1,double x2,double y2,double x3,double y3)
{
	if (((fabs(x1 - x2) <= 1e-6) && (fabs(x1 - x3) <= 1e-6)) || ((fabs(y1 - y2) <= 1e-6) && (fabs(y1 - y3) <= 1e-6)) )
		return 1;
    else if (fabs((x3 - x1) / (y3 - y1) - (x2 - x1) / (y2 - y1)) <= 1e-5)
		return 1;//共线
	else
		return 0;
}

//size computation
double f_dscompute(double b[][N],int n, int tag)  //tag=0,求最大面积，tag=i,求缺省第i个点后构成的多边形的面积
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
		return -1;   //相邻两点与重心不构成三角形的情况
	}
}



