//#include"pch.h"//防止vs2017出错
#include<iostream>
using namespace std;
class Container//声明抽象类container
{
protected:
	double radius;
public:
	Container(double radius1)//抽象类container的构造函数
	{
		radius = radius1;//用于初始化
	}
	virtual double surface_area() = 0;//纯虚函数用于计算表面积
	virtual double volume() = 0;//纯虚函数用于计算体积
};
class Cube :public Container//方块类，公有继承container
{
public:
	Cube(double radius1) :Container(radius1) {}
	virtual double surface_area()
	{
		return (radius * radius * 6);//正方体表面积公式
	}
	virtual double volume()
	{
		return (radius * radius*radius);//正方体体积公式
	}
};
class Sphere :public Container//球体类，公有继承container
{
public:
	Sphere(double radius1) :Container(radius1) {}
	virtual double surface_area()
	{
		return (4 * 3.1415926*radius*radius);
	}
	virtual double volume()
	{
		return ((4.0/3.0)*3.1415926*radius*radius*radius);
	}
};
class Cylinder :public Container//圆柱体类，公有继承container
{
public:
	Cylinder(double radius1) :Container(radius1) {}
	virtual double surface_area()
	{
		return ((3.1415926*radius*radius) * 2 + (3.1415926*radius * 2 * radius));//默认了圆柱体的高等于底面半径，此时恰好圆柱体和球体的表面积是相等的
	}
	virtual double volume()
	{
		return (3.1415926*radius*radius*6);
	}
};

int main()
{
	Cube a(6);//创建三个对象
	Sphere b(5);
	Cylinder c(5);
	cout << "The surface area of cube is:" << a.surface_area() << endl;//输出所有计算的结果
	cout << "The volume of cube is:" << a.volume() << endl;
	cout << "The surface area of sphere is:" << b.surface_area() << endl;
	cout << "The volume of sphere is:" << b.volume() << endl;
	cout << "The surface area of cylinder is:" << c.surface_area() << endl;
	cout << "The volume of cylinder is:" << c.volume() << endl;
	return 0;
}