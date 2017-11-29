//��ŵ�� ������ʾ�����裬���ô洢���裨ȫ������ﵽ��ջ�����ã�+����
#include <iostream>
#include <stdio.h>
#include <iomanip>
using namespace std;

void Hanoi(int n, int st, int ed)
{
	static long int lstep(0);
	
	int imd = 'A' + 'B' + 'C' - st - ed;      //ȷ���м���������һ��
	if (n == 1)
	{
		cout << setiosflags(ios::right) << setw(5) << ++lstep << ':' << setw(2) << n << "# " << char(st) << "-->" << char(ed) << endl;
	}
	else
	{
		Hanoi(n - 1, st, imd);
		cout << setiosflags(ios::right) << setw(5) << ++lstep << ':' << setw(2) << n << "# " << char(st) << "-->" << char(ed) << endl;
		Hanoi(n - 1, imd, ed);
	}
	return;
}

int main()
{
	int ifloor;
	char chstart, chend;

	while (1)
	{
		cout << "Please input the floor of your tower:" << endl;
		cin >> ifloor;
		if (!cin.good())   //�������͵��ж���ǰ�����ݷ�Χ���ж��ں���Ϊ������������������ǳ���Χ�ģ����һ���Ϊû�������������������ѭ��
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "Your input is error ";
			continue;
		}
		else if (ifloor <= 0)
		{
			continue;
			cout << "Your input is error ";
		}
		else
			break;
	}



	while (1)
	{
		cin.ignore(1024, '\n');
		int tag = 0;
		cout << "Please input the start tower(A-C):" << endl;     //����Ҫ��֤���غϣ�СдҲҪת�ɴ�д
		chstart = getchar();

		/*if (!cin.good())    //���ݵ��жϷ�ʽ��ǰ����ͬ�����Ǵ��������ַ���ȴ����������������������ۣ���ȡ�ַ�ʱ��Ӧ����getchar�źã�cin�Ļ������assdsdf��aͨ���ˣ����Ǻ�����ַ��������ֵ������
		{
		cin.clear();
		cin.ignore(1024, '\n');
		cout << "Your input is error ";
		continue;
		}*/
		//��������

		switch (chstart)
		{
			case 'a':
			case 'b':
			case 'c':
				chstart -= 32;
			case 'A':
			case 'B':
			case 'C':
				tag++;
				break;
			default:
				break;
		}

		if (tag)
			break;
		else
		{
			cout << "Your input is error ";
			continue;
		}
	}



	while (1)
	{
		cin.ignore(1024, '\n');
		int tag = 0;
		cout << "Please input the end tower(A-C):" << endl;
		//cin >> chend;
		chend = getchar();

		switch (chend)
		{
			case 'a':
			case 'b':
			case 'c':
				chend -= 32;
			case 'A':
			case 'B':
			case 'C':
				tag++;
				break;
			default:
				break;
		}

		if (chend == chstart)
			continue;
		if (tag)
			break;
		else
		{
			cout << "Your input is error ";
			continue;
		}
	}
	cout << "the step is:" << endl;
	Hanoi(ifloor, chstart, chend);

	return 0;
}

//���ж��������ͣ����ж����ݷ�Χ;  ��ȡ�ַ���getchar()������cin
//while(1){cin.ignore('1024','\n')}ÿ��ѭ����������ջ��棬��ֹ�ϴ��������ַ�����Ӱ��
//���θ��ƴ���ʱ���м���жϱ����Ͳ�������ҲҪ����������Ȼ������
//charҪע����������������漰getcharʱ����ֱ�������Σ������ʱ��ǿ��ת��
