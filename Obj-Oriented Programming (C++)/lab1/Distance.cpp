#include"pch.h"//This program is written in Visual Studio IDE community 2017, it is required to include"pch.h".
#include<iostream>
#include<stdlib.h>
#include<cmath>
using namespace std;
class Point//定义点的类
{
private:
	double x;//创建私有数据，下同
	double y;
public:
	void info()//函数：输入关于点的数据，下同
	{
		cout << "x=";
		cin >> x;
		cout << "y=";
		cin >> y;
	}
	friend class Line;//声明线的友元类
};
class Line//定义线的类
{
private:
	double a;
	double b;
	double c;
public:
	void info()
	{
		cout << "a=";
		cin >> a;
		cout << "b=";
		cin >> b;
		cout << "c=";
		cin >> c;
	}
	void calculate(Point po)//计算距离，此时已经可以直接使用点的私有数据
	{
		double cal;
		cal = (po.x*a + po.y*b + c) / (sqrt(a*a + b * b));
		cout << "Distance=" << cal << endl;
	}
};
int main()
{
	Point poi;//创建类
	Line lin;
	poi.info();//输入数据
	lin.info();
	lin.calculate(poi);//计算并输出结果
	system("pause");
	return 0;
}