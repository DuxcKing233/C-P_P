#include <iostream>
using namespace std;

int main()
{
    while(1)
    {
	    unsigned a;
	    cout<<"input"<<endl;
	    cin>>a;
	    if(a==0)
	        break;
		cout<<a/1024/1024/1024<<'G'<<(a%(1024*1024*1024))/(1024*1024)<<'M'<<' '<<(a%(1024*1024))/1024<<'K'<<endl;
	}

    return 0;
}
  
