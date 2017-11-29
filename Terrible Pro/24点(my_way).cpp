
/*
 ����ͨ����ѧ�ϵ���ٷ���
 һ��˳����ĸ����������һ���� 5 �ַ�ʽ  icomp=1 2 3 4 5
 ������֮��ķ���һ���� itag=1 2 3 4(+ - * /) 4��
 �� f_iresult()������������ϵ�ֵ
 �� f_vcout()����������������������ø���icomp��5�������ÿ��������������һ�������д��Ľ���������
 �� f_vdot24()��������icomp�ĵ�ֵ ȷ��������֯��ʽ���÷�5��������д��Ľ���������
 (8+4)/(2/4)=24����������©���ˣ�����Ϊ���γ����ᵼ����Ӧ������double��
*/

#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <math.h>
using namespace std;
void f_vdot24(int i1, int i2, int i3, int i4, int icomp, int itag1, int itag2, int itag3);
void f_vcout(int i1, int i2, int i3, int i4, int icomp, int itag1, int itag2, int itag3);
double f_iresult(double a, double b, int tag);

int main()
{
	cout << "Please input 4 integreters varing from 1-10:" << endl;
	int i1, i2, i3, i4,icomp,itag1,itag2,itag3;//icomp:�ĸ�������5�ֽ�Ϸ�ʽ��itag���ĸ���֮�������������ţ�
	while (1) 
	{
		cin >> i1 >> i2 >> i3 >> i4;
		if (!cin.good())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "Please input 4 integreters varing from 1-10:" << endl;
			continue;
		}
		else if ((i1 <= 0 || i1 > 10) || (i2 <= 0 || i2 > 10) || (i3 <= 0 || i3 > 10) || (i4 <= 0 || i4 > 10))
		{
		    cin.clear();
		    cin.ignore(1024, '\n');
		    cout << "Please input 4 integreters varing from 1-10:" << endl;
		    continue;
		}
		else
			break;
	}

	for (icomp = 1; icomp <= 5; icomp++)
		for (itag1 = 1; itag1 <= 4; itag1++)
			for (itag2 = 1; itag2 <= 4; itag2++)
				for (itag3 = 1; itag3 <= 4; itag3++)
					f_vdot24(i1,i2,i3,i4,icomp,itag1,itag2,itag3);

	return 0;
}


void f_vdot24(int i1, int i2, int i3, int i4, int icomp, int itag1, int itag2, int itag3)  //1 + 2 - 3 * 4 /
{
	double tmp1(0), tmp2(0), tmp3(0);
	if (icomp == 1)
	{
		tmp1 = f_iresult(i1, i2, itag1);
		tmp2 = f_iresult(tmp1, i3, itag2);
		tmp3 = f_iresult(tmp2, i4, itag3);
	}
	else if (icomp == 2)
	{
		tmp1 = f_iresult(i1, i2, itag1);
		tmp2 = f_iresult(i3, i4, itag2);
		tmp3 = f_iresult(tmp1, tmp2, itag3);
	}
	else if (icomp == 3)
	{
		tmp1 = f_iresult(i2, i3, itag1);
		tmp2 = f_iresult(i1, tmp1, itag2);
		tmp3 = f_iresult(tmp2, i4, itag3);
	}
	else if (icomp == 4)
	{
		tmp1 = f_iresult(i2, i3, itag1);
		tmp2 = f_iresult(tmp1, i4, itag2);
		tmp3 = f_iresult(i1, tmp2, itag3);
	}
	else if (icomp == 5)
	{
		tmp1 = f_iresult(i3, i4, itag1);
		tmp2 = f_iresult(i2, tmp1, itag2);
		tmp3 = f_iresult(i1, tmp2, itag3);
	}
	else
	{
		cout << endl << "Error in icomp" << endl;
		return;
	}

	if (fabs(tmp3 -24)<=1e-5)
	{
		switch (itag1)
		{
			case 1:
				itag1 = '+';
				break;
			case 2:
				itag1 = '-';
				break;
			case 3:
				itag1 = '*';
				break;
			case 4:
				itag1 = '/';
				break;
		}
		switch (itag2)
		{
			case 1:
				itag2 = '+';
				break;
			case 2:
				itag2 = '-';
				break;
			case 3:
				itag2 = '*';
				break;
			case 4:
				itag2 = '/';
				break;
		}
		switch (itag3)
		{
			case 1:
				itag3 = '+';
				break;
			case 2:
				itag3 = '-';
				break;
			case 3:
				itag3 = '*';
				break;
			case 4:
				itag3 = '/';
				break;
		}
		f_vcout(i1, i2, i3, i4, icomp, itag1, itag2, itag3);
	}
	return;
}

void f_vcout(int i1, int i2, int i3, int i4, int icomp, int itag1, int itag2, int itag3)
{
	switch (icomp)
	{
		case 1:
			cout << "((" << i1 << char(itag1) << i2 << ')' << char(itag2) << i3 << ')' << char(itag3) << i4 <<"=24" << endl;
			break;
		case 2:
			cout << '(' << i1 << char(itag1) << i2 << ')' << char(itag2) << '(' << i3 << char(itag3) << i4 << ')' << "=24" << endl;
			break;
		case 3:
			cout << '(' << i1 << char(itag1) << '(' << i2 << char(itag2) << i3 << "))" << char(itag3) << i4 << "=24" << endl;
			break;
		case 4:
			cout << i1 << char(itag1) << "((" << i2 << char(itag2) << i3 << ')' << char(itag3) << i4 << ')' << "=24" << endl;
			break;
		case 5:
			cout << i1 << char(itag1) << '(' << i2 << char(itag2) << '(' << i3 << char(itag3) << i4 << "))" << "=24" << endl;
			break;
		default:
			cout << "ERROR output " << endl;
	}
}


double f_iresult(double a, double b, int tag)
{
	switch (tag)
	{
		case 1:
			return a + b;
			break;
		case 2:
			return a - b;
			break;
		case 3:
			return a*b;
			break;
		case 4:
			return a / b;
			break;
		default:
			cout << "\nerror\n";
			break;
	}
}
