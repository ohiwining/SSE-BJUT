#include"pch.h"//This program is written in Visual Studio IDE community 2017, it is required to include"pch.h".
#include<iostream>
#include<stdlib.h>
using namespace std;
class Clock//创建一个钟表的类
{
private:
	int seconds;//定义关于钟表的私有变量
	int minutes;
	int hours;
public:
	void set_time()//用户在这里设置时间
	{
		cout << "Please input Hour Minute Second:" << endl;
		cin >> hours >> minutes >> seconds;
	}
	void check(Clock a, Clock b)//函数：把时间相加
	{
		int ho;
		int mi;
		int se;
		ho = a.hours + b.hours;
		mi = a.minutes + b.minutes;
		se = a.seconds + b.seconds;
		for (; se >= 60;)//判断是否需要进位
		{
			se -= 60;
			mi++;
		}
		for (; mi >= 60;)
		{
			mi -= 60;
			se++;
		}
		cout << "The summary of time is " << ho << ":" << mi << ":" << se << endl;//输出相加后的时间
	}
};
int main()
{
	Clock a, b;//定义两个时钟类
	a.set_time();
	b.set_time();
	a.check(a, b);
	system("pause");
}