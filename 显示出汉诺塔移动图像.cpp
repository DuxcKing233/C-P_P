/* 1653633 ���� ��3 */
//except Linux GCC
/*
��ʾ����ŵ���ƶ�ͼ��
input:��ŵ����������ʼ���ӣ�Ŀ�����ӣ���ʾ�ٶȲ�������ʾ���Բ���
output:ÿһ�����ƶ�˵���Լ�ͼ����ʾ

PS: tappause()��������while(1){ if .._getche()=='\r'..break  }�ûس������ƣ�
                      switch(){case1 Sleep(1000)(1seconds...)}.
	��cout<<"    "��һ���ո���������Ļ�ϵ�����
	��'\b'��ʹ�û�����Ϥ
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <iomanip>
using namespace std;

//const
const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //ȡ��׼����豸��Ӧ�ľ��
const int MAX_X = 100;	//�����ܵĿ��
const int MAX_Y = 19;	//�����ܵĸ߶�
const int A_X = 12;
const int B_X = 22;
const int C_X = 32;
const int ABC_Y = 15;
short slevel, smvspd, sshowin;
static short a_sa[10] = { 0 }, a_sb[10] = { 0 }, a_sc[10] = { 0 }, stopa(0), stopb(0), stopc(0);

//extern+fun ����
void f_vsetarray(short level, char ch);
void f_vresetarray(char st, char ed);
void f_vcoutarray();
void f_vhanoi(char st, char ed, short level);
void gotoxy(HANDLE hout, int X, int Y);
void showch(HANDLE hout, int X, int Y, char ch);
void clearrow(HANDLE hout);
inline void if_vmoveplant(char st,char ed);
inline void if_vtappause();
void f_vinitial(char cstart);

int main()
{
	//define
	char cstart, cend;

	//input & test
	while (1)
	{
		cout << "�����뺺ŵ���Ĳ���(1-10)�� ";
		cin >> slevel;
		if (!cin.good())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else if (slevel <= 0 || slevel > 10)
			continue;
		else
			break;
	}

	while (2)
	{
		cout << "��������ʼ��(A-C)�� ";
		cin >> cstart;
		if (!cin.good())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else if ((cstart <= 'C'&&cstart >= 'A') || (cstart <= 'c'&&cstart >= 'a'))
			break;
		else
			continue;
	}

	while (3)
	{
		cout << "������Ŀ����(A-C)�� ";
		cin >> cend;
		if (!cin.good() || cstart == cend || cstart == cend + 32 || cstart == cend - 32)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else if ((cend <= 'C'&&cend >= 'A') || (cend <= 'c'&&cend >= 'a'))
			break;
		else
			continue;
	}
	if (cstart > 'C')
		cstart -= 32;
	if (cend > 'C')
		cend -= 32;

	while (4)
	{
		cout << "�������ƶ��ٶ�(0-5��0-���س�������ʾ 1-��ʱ� 5-��ʱ���) ";
		cin >> smvspd;
		if (!cin.good())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else if (smvspd < 0 || smvspd > 5)
			continue;
		else
			break;
	}

	while (5)
	{
		cout << "�������Ƿ���ʾ�ڲ�����ֵ(0 - ����ʾ 1 - ��ʾ) ";
		cin >> sshowin;
		if (!cin.good())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else if (sshowin!=0 && sshowin!=1)
			continue;
		else
			break;
	}

	system("cls");
	cout << "��" << cstart << "�ƶ���" << cend << "����" << slevel << "�㣬��ʱ����Ϊ" << smvspd<<','; 
	if (sshowin == 0)
		cout << "��";
	cout << "��ʾ�ڲ�����ֵ" << endl;
	//using function
    
	//initialization
	f_vinitial(cstart);
	if_vtappause();
	f_vhanoi(cstart, cend, slevel);

	gotoxy(hout, 1, MAX_Y + 2);

	return 0;
}

//fun����

//set array
void f_vsetarray(short level, char ch)
{
	int i;
	if (ch == 'A')
	{
		for (i = 0; i < level; i++)
			a_sa[i] = level - i;
		stopa = level;
	}
	else if (ch == 'B')
	{
		for (i = 0; i < level; i++)
			a_sb[i] = level - i;
		stopb = level;
	}
	else if (ch == 'C')
	{
		for (i = 0; i < level; i++)
			a_sc[i] = level - i;
		stopc = level;
	}
	else
		cout << endl << "Error, the name of tower is wrong!" << endl;
	return;
}

//reset array
void f_vresetarray(char st, char ed)
{
	short tmp(0);
	if (st == 'A')
	{
		tmp = a_sa[--stopa];
		a_sa[stopa] = 0;
	}
	else if (st == 'B')
	{
		tmp = a_sb[--stopb];
		a_sb[stopb] = 0;
	}
	else
	{
		tmp = a_sc[--stopc];
		a_sc[stopc] = 0;
	}

	if (ed == st)
	{
		cout << endl << "Error, Wrong st & ed" << endl;
		return;
	}
	else if (ed == 'A')
		a_sa[stopa++] = tmp;
	else if (ed == 'B')
		a_sb[stopb++] = tmp;
	else
		a_sc[stopc++] = tmp;
	return;
}

//cout array
void f_vcoutarray()
{
	if (sshowin == 0)
		return;
	short i;
	cout << "A:" << setiosflags(ios::right);
	for (i = 0; i < 10; i++)
	{
		if (a_sa[i] == 0)
			cout << "   ";
		else
			cout << setw(2) << a_sa[i] << ' ';
		//cout << setw(2) << ((a_sa[i] == 0) ? '\x20' : a_sa[i]) << ' ';
	}
	cout << "B:" << setiosflags(ios::right);
	for (i = 0; i < 10; i++)
	{
		if (a_sb[i] == 0)
			cout << "   ";
		else
			cout << setw(2) << a_sb[i] << ' ';
	}
	cout << "C:" << setiosflags(ios::right);
	for (i = 0; i < 10; i++)
	{
		if (a_sc[i] == 0)
			cout << "   ";
		else
			cout << setw(2) << a_sc[i] << ' ';
	}
	cout << endl;
	return;
}

//hanoi-recurse
void f_vhanoi(char st, char ed, short level)
{
	static int step(0);
	if (level == 1)
	{
		if_vtappause();
		clearrow(hout);
		cout << "��" << setw(5) << ++step << " �� (" << setw(2) << level << "): " << st << "-->" << ed << ' ';
		f_vresetarray(st, ed);
		f_vcoutarray();
		if_vtappause();
		if_vmoveplant(st, ed);
		return;
	}
	else
	{
		char md = 'A' + 'B' + 'C' - st - ed;
		f_vhanoi(st, md, level - 1);
		if_vtappause();
		clearrow(hout);
		cout << "��" << setw(5) << ++step << " �� (" << setw(2) << level << "): " << st << "-->" << ed << ' ';
		f_vresetarray(st, ed);
		f_vcoutarray();
		if_vtappause();
		if_vmoveplant(st, ed);
		f_vhanoi(md, ed, level - 1);
		return;
	}
}


/* ������ƶ���ָ��λ�� */
void gotoxy(HANDLE hout, int X, int Y)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(hout, coord);

	return;
}

/* ��ָ��λ�ô���ӡһ��ָ�����ַ� */
void showch(HANDLE hout, int X, int Y, char ch)
{
	gotoxy(hout, X, Y);
	putchar(ch);

	return;
}


/*������ƶ���logָʾ�У����һ��ѿո��ԭlog���ǣ����˸������������log*/
void clearrow(HANDLE hout)
{
	gotoxy(hout,1, MAX_Y);
	cout << "                                                                    ";
	gotoxy(hout, 1, MAX_Y);

	return;
}



inline void if_vmoveplant(char st, char ed)
{
	/*��ŵ���̵�ժȡ*/
	switch (st)
	{
		case 'A':
			gotoxy(hout, A_X -1, +ABC_Y - 1 -stopa - 1 );
			break;
		case 'B':
			gotoxy(hout, B_X-1 , +ABC_Y - 1 -stopb - 1 );
			break;
		case 'C':
			gotoxy(hout, C_X -1, +ABC_Y - 1 -stopc - 1 );
			break;
		default:
			cout << "Error!" << endl;
	}
	cout << "   ";

	/*��ŵ���̵ķ���*/
	switch (ed)
	{
		case 'A':
			gotoxy(hout, A_X , -stopa + ABC_Y - 1), cout << a_sa[stopa - 1];
			break;
		case 'B':
			gotoxy(hout, B_X , -stopb + ABC_Y - 1), cout << a_sb[stopb - 1];
			break;
		case 'C':
			gotoxy(hout, C_X , -stopc + ABC_Y - 1), cout << a_sc[stopc - 1];
			break;
		default:
			cout << "Error!" << endl;
	}

	return;
}

inline void if_vtappause()
{
	while (1)
	{
		if (smvspd)
			break;
		if (_getche() == '\r')
			break;
	}

	switch (smvspd)
	{
		case 0:
			break;
		case 1:
			Sleep(700);
			break;
		case 2:
			Sleep(400);
			break;
		case 3:
			Sleep(100);
			break;
		case 4:
			Sleep(50);
			break;
		case 5:
			break;
		default:
			cout << "Error!" << endl;
			break;
	}

	return;
}

void f_vinitial(char cstart)
{
	int ii(0);
	char ch = cstart;
	clearrow(hout);
	f_vsetarray(slevel, cstart);
	cout << "��ʼ:                  ";
	f_vcoutarray();
	gotoxy(hout, 9, 14);
	for (ii = 1; ii <= 27; ii++)
		cout << '=';
	gotoxy(hout, A_X, ABC_Y);
	cout << 'A';
	gotoxy(hout, B_X, ABC_Y);
	cout << 'B';
	gotoxy(hout, C_X, ABC_Y);
	cout << 'C';
	if (ch == 'A')
	{
		for (ii = 1; ii <= stopa; ii++)
		{
			gotoxy(hout, A_X, ABC_Y - 1 - ii);
			cout << a_sa[ii - 1];
		}
	}
	else if (ch == 'B')
	{
		for (ii = 1; ii <= stopb; ii++)
		{
			gotoxy(hout, B_X, ABC_Y - 1 - ii);
			cout << a_sb[ii - 1];
		}
	}
	else if (ch == 'C')
	{
		for (ii = 1; ii <= stopc; ii++)
		{
			gotoxy(hout, C_X, ABC_Y - 1 - ii);
			cout << a_sc[ii - 1];
		}
	}
	else
		cout << "Error" << endl;

	return;
}