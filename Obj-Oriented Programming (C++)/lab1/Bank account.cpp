#include"pch.h"//This program is written in Visual Studio IDE community 2017, it is required to include"pch.h".
#include<iostream>
#include<stdlib.h>
using namespace std;
class Gbank;//提前声明类防止友元函数不通过
class Bbank;
class Cbank//定义第一个银行
{
private:
	float balance;//设定关于这个银行的私有变量，下同
public:
	void input()
	{
		cout << "Please input your money in CBank:" << endl;//用户输入关于这个银行的数据，下同
		cin >> balance;
	}
	friend void total(Cbank cb, Bbank bb, Gbank gb);//声明友元函数，下同
};
class Bbank
{
private:
	float balance;
public:
	void input()
	{
		cout << "Please input your money in BBank:" << endl;
		cin >> balance;
	}
	friend void total(Cbank cb, Bbank bb, Gbank gb);
};
class Gbank
{
private:
	float balance;
public:
	void input()
	{
		cout << "Please input your money in GBank:" << endl;
		cin >> balance;
	}
	friend void total(Cbank cb, Bbank bb, Gbank gb);
};

void total(Cbank cb, Bbank bb, Gbank gb)//定义友元函数
{
	float totalamount;
	totalamount = cb.balance + bb.balance + gb.balance;//将三个银行中的数据相加
	cout << "Total=" << totalamount << endl;//输出结果
}

int main()
{
	Cbank a;//创建类
	Bbank b;
	Gbank c;
	a.input();//输入数据
	b.input();
	c.input();
	total(a, b, c);//输出结果
	system("pause");
}