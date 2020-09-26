//#include "pch.h"
#include <iostream>
using namespace std;
void move(int n, char x, char y, char z)
{
	if (n == 1)
		cout << n << " From " << x << " To " << z<<endl;
	else
	{
		move(n - 1, x, y, z);
		cout << n << " From " << x << " To " << z<<endl;
		move(n - 1, y, x, z);
	}
}
int main()
{
	char ch1 = 'A';
	char ch2 = 'B';
	char ch3 = 'C';
	int n;
	cout << "input the number of disks:" << endl;
	cin >> n;
	move(n, ch1, ch2, ch3);
	system("pause");
	return 0;
}