/*1653633 ¼Æ3 ¹±³©*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
using namespace std;

int main()
{
    char a[80];



#if _GLIBCXX_USE_LFS  || __MSVCRT__
	gets(a);       //Dev C++ || CodeBlocks
#elif _MSC_VER
	gets_s(a);  //vs2017
#elif __linux__
    fgets(a,10,stdin)
#endif

    cout<<a<<endl;



	return 0;
}
