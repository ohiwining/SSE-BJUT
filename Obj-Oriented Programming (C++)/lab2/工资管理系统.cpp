//#include"pch.h"//防止vs2017报错
#include<iostream>
#include<stdlib.h>
using namespace std;
class Employee//定义员工的类，之后所有类型的员工都从这里继承
{
protected:
	int ID;
	char name[30];
	double salary;
	double product;
public:
	void input()//通用录入信息函数，在这里输入号码和姓名
	{
		cout << "Please input ID:" << endl;
		cin >> ID;
		cout << "Please input name:" << endl;
		cin >> name;
	}
	void print()//通用输出函数，在这里打印出员工对应的号码，信息以及薪水
	{
		cout << "ID:     " << ID << endl;
		cout << "Name:   " << name << endl;
		cout << "Salary: " << salary << endl;
	}
};

class Technician :public Employee//定义技术人员类，继承员工类
{
private:
	int worktime;//新增数据成员：工作时间
public:
	Technician()//构造函数初始化成员数据
	{
		input();
		cout << "Please input worktime:";
		cin >> worktime;
		salary = 100 * worktime;
	}
};

class Manager :public Employee//定义经理类，继承员工类
{
public:
	Manager()
	{
		salary = 8000;//经理工资是固定的，因此构造函数也相对简单
	}
};

class Salesman :public Employee
{
public:
	void salesinit()//为防止SalesManager构造函数出现错误，在此使用了普通的成员函数
	{
		cout << "Please input sale product:" << endl;
		cin >> product;
		salary = product * 0.04;
	}
};

class SalesManager :public Manager, public Salesman//定义销售经理类，继承经理类和销售人员类
{
public:
	SalesManager()
	{
		Manager::input();//多继承的二义性
		cout << "Please input SalesManager governed product:" << endl;
		cin >> Manager::product;
		Manager::salary = Manager::product * 0.05 + 5000;
	}
};

int main()//开始运行程序
{
	cout << "Now you're creating a Manager:" << endl;//一边提示用户输入，一边创建对象
	Manager b;
	b.input();
	system("cls");
	cout << "Now you're creating a Technician:" << endl;
	Technician a;
	system("cls");
	cout << "Now you're creating a Salesman:" << endl;
	Salesman c;
	c.input();//调用成员函数
	c.salesinit();
	system("cls");
	cout << "Now you're creating a SalesManager:" << endl;
	SalesManager d;
	system("cls");
	cout << "Result:" << endl;//打印最终信息，显示所有人的信息
	cout << "Manager: " << endl;
	b.print();
	cout << "Technician: " << endl;
	a.print();
	cout << "Salesman: " << endl;
	c.print();
	cout << "SalesManager: " << endl;
	d.Manager::print();
	system("pause");
}