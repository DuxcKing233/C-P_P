//汉诺塔 不仅显示出步骤，还得存储步骤（全局数组达到堆栈的作用）+迭代
#include <iostream>
#include <stdio.h>
#include <iomanip>
using namespace std;

void Hanoi(int n, int st, int ed)
{
	static long int lstep(0);
	
	int imd = 'A' + 'B' + 'C' - st - ed;      //确定中间柱子是哪一个
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
		if (!cin.good())   //数据类型的判断在前，数据范围的判断在后，因为错误的数据类型往往是超范围的，而且会因为没有清空输入区而陷入死循环
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
		cout << "Please input the start tower(A-C):" << endl;     //后期要保证不重合，小写也要转成大写
		chstart = getchar();

		/*if (!cin.good())    //数据的判断方式与前面相同，但是错误输入字符串却会出现连续输出的情况，结论：读取字符时还应采用getchar才好，cin的话如读入assdsdf，a通过了，但是后面的字符会造成奇怪的情况。
		{
		cin.clear();
		cin.ignore(1024, '\n');
		cout << "Your input is error ";
		continue;
		}*/
		//这样不行

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

//先判断数据类型，再判断数据范围;  读取字符用getchar()，不用cin
//while(1){cin.ignore('1024','\n')}每次循环都可以清空缓存，防止上次输了了字符串的影响
//整段复制代码时，中间的判断变量和操作变量也要换过来，不然亏大了
//char要注意相加溢出的情况，涉及getchar时不妨直接用整形，在输出时候强制转换
