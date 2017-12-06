/*1653633 ��3 ����*/
//except for linux
/*
������ݣ���ӡ����
input:1900-2100֮���ĳһ��
output:�����������Ҫ������������Ҳ���ǿ��·����

PS:���·�������ѵ�
   ����Ҫ�õ�֮ǰ�Ĳ��չ�ʽ��
   ��ᵽ֮ǰ�İ�Ҳ�п��ܲ�����
   �ඨ�弸��������Ϊ���Ʊ���
   �����ظ��ϸߣ��������ٸĽ�
*/


#include <iostream>
#include <iomanip>
#include <cstdio>
#include <windows.h>
using namespace std;


//���չ�ʽ
int zeller(int y, int m, int d)
{
	int w, c;
	c = y / 100;
	y = y % 100;
	if (m <= 2)
	{
		m = m + 12;
		y--;
		if (y < 0)
		{
			y = 99;
			c--;
		}
	}

	w = y + y / 4 + c / 4 - 2 * c + 13 * (m + 1) / 5 + d - 1;
	while (1)                       //��Ҫ̫�������Լ�֮ǰ�ĺ�����
	{
		if (w < 0)
			w += 7;
		else
			break;    
	}
		
	w = w % 7;
	return w;
}



int main()
{
	system("mode con cols=100 lines=40");
	
	//define
	int itag = 0,iyear(0),imonth(1),irow,icol,irun(0);
	short a_sTab[366] = { 0 }, a_sCase[12] = {0}, a_sEnd[12] = { 0 }, a_sMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	//input
	while (1)
	{
		cout<<"���������(1900-2100) :" <<endl;
		cin >> iyear;
		if (!cin.good() || iyear < 1900 || iyear>2100)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else
			break;
	}

	irun = ((iyear % 400) == 0) || ((iyear % 4 == 0) && (iyear % 100 != 0));
	a_sMonth[1] += irun;
	//cout << irun << endl;


	//fill array
	imonth = 0;
	irow = 0;
	int iii = 1;

	a_sEnd[0] = 0;   //1,1������λ��
	while (2)
	{
		a_sTab[irow] = iii;
		iii++;
		irow++;
		if (iii > a_sMonth[imonth])
		{
			iii = 1;
			imonth++;
			if (imonth == 12)
				break;
			else
				a_sEnd[imonth] = irow; //ÿ�µ�һ�յ�����λ��
		}
	}

	//output array
	cout <<iyear<< "���������" << endl << endl;
	cout << "            1��                             2��                             3��" << endl;
	cout << "Sun Mon Tue Wed Thu Fri Sat     Sun Mon Tue Wed Thu Fri Sat     Sun Mon Tue Wed Thu Fri Sat" << endl;
	for (icol = 0; icol < 126; )
	{
		imonth = (icol%21) / 7;
		if (zeller(iyear, imonth+1, a_sTab[a_sEnd[imonth]]) != (icol%7))
		{
			cout << setiosflags(ios::left )<<setw(4)<<' ';
		}
		else if (a_sCase[imonth] == 1)
		{
			cout << setw(4) << ' ';
		}
		else
		{
			cout <<setiosflags(ios::left)<<setw(4) <<a_sTab[a_sEnd[imonth]] ;
			if (a_sTab[a_sEnd[imonth]] == a_sMonth[imonth])
				a_sCase[imonth] = 1;
			else
                a_sEnd[imonth]++;
		}
		icol++;
		if (icol % 7 == 0 && icol%21!=0)
		{
			cout << "    ";
			imonth++;
		}
		if (icol % 21 == 0)
		{
			cout << endl;
		}
		if (icol == 21 * 5 && a_sCase[2] * a_sCase[1] * a_sCase[0])
			break;
	}


	cout << endl<<"            4��                             5��                             6��" << endl;
	cout << "Sun Mon Tue Wed Thu Fri Sat     Sun Mon Tue Wed Thu Fri Sat     Sun Mon Tue Wed Thu Fri Sat" << endl;
	for (icol = 0; icol < 126; )
	{
		imonth = (icol % 21) / 7+3;
		if (zeller(iyear, imonth + 1, a_sTab[a_sEnd[imonth]]) != (icol % 7))
		{
			cout << setiosflags(ios::left) << setw(4) << ' ';
		}
		else if (a_sCase[imonth] == 1)
		{
			cout << setw(4) << ' ';
		}
		else
		{
			cout << setiosflags(ios::left) << setw(4) << a_sTab[a_sEnd[imonth]];
			if (a_sTab[a_sEnd[imonth]] == a_sMonth[imonth])
				a_sCase[imonth] = 1;
			else
				a_sEnd[imonth]++;
		}
		icol++;
		if (icol % 7 == 0 && icol % 21 != 0)
		{
			cout << "    ";
			imonth++;
		}
		if (icol % 21 == 0)
		{
			cout << endl;
		}
		if (icol == 21 * 5 && a_sCase[5] * a_sCase[4] * a_sCase[3])
			break;
	}
	

	cout <<endl<< "            7��                             8��                             9��" << endl;
	cout << "Sun Mon Tue Wed Thu Fri Sat     Sun Mon Tue Wed Thu Fri Sat     Sun Mon Tue Wed Thu Fri Sat" << endl;
	for (icol = 0; icol < 126; )
	{
		imonth = (icol % 21) / 7 + 6;
		if (zeller(iyear, imonth + 1, a_sTab[a_sEnd[imonth]]) != (icol % 7))
		{
			cout << setiosflags(ios::left) << setw(4) << ' ';
		}
		else if (a_sCase[imonth] == 1)
		{
			cout << setw(4) << ' ';
		}
		else
		{
			cout << setiosflags(ios::left) << setw(4) << a_sTab[a_sEnd[imonth]];
			if (a_sTab[a_sEnd[imonth]] == a_sMonth[imonth])
				a_sCase[imonth] = 1;
			else
				a_sEnd[imonth]++;
		}
		icol++;
		if (icol % 7 == 0 && icol % 21 != 0)
		{
			cout << "    ";
			imonth++;
		}
		if (icol % 21 == 0)
		{
			cout << endl;
		}
		if (icol == 21 * 5 && a_sCase[8] * a_sCase[7] * a_sCase[6])
			break;
	}

	cout <<endl<< "           10��                            11��                            12��" << endl;
	cout << "Sun Mon Tue Wed Thu Fri Sat     Sun Mon Tue Wed Thu Fri Sat     Sun Mon Tue Wed Thu Fri Sat" << endl;
	for (icol = 0; icol < 126; )
	{
		imonth = (icol % 21) / 7 + 9;
		if (zeller(iyear, imonth + 1, a_sTab[a_sEnd[imonth]]) != (icol % 7))
		{
			cout << setiosflags(ios::left) << setw(4) << ' ';
		}
		else if (a_sCase[imonth] == 1)
		{
			cout << setw(4) << ' ';
		}
		else
		{
			cout << setiosflags(ios::left) << setw(4) << a_sTab[a_sEnd[imonth]];
			if (a_sTab[a_sEnd[imonth]] == a_sMonth[imonth])
				a_sCase[imonth] = 1;
			else
				a_sEnd[imonth]++;
		}
		icol++;
		if (icol % 7 == 0 && icol % 21 != 0)
		{
			cout << "    ";
			imonth++;
		}
		if (icol % 21 == 0)
		{
			cout << endl;
		}
		if (icol == 21 * 5 && a_sCase[11] * a_sCase[10] * a_sCase[9])
			break;
	}
	cout << endl << endl;
	return 0;
}