//#include"pch.h"//防止vs2017报错
#include<iostream>
using namespace std;
class CComplex//定义CComplex的类
{
private:
	double real;
	double image;
public:
	CComplex()//构造函数：当没有传入参数时默认将值设为0
	{
		real = 0;
		image = 0;
	}
	CComplex(double a, double b)//构造函数:当传入两个参数时赋值给类中两个数据
	{
		real = a;
		image = b;
	}
	void print()//输出数据的函数
	{
		cout << "Real=" << real << endl;
		cout << "Image=" << image << endl;
	}
	CComplex operator = (CComplex &p)//定义=的函数
	{
		real = p.real;
		image = p.image;
	}
	CComplex operator ++ ()//定义前++的函数
	{
		++real;
		++image;
		return CComplex(real, image);
	}
	CComplex operator ++ (int whatever)//定义后++的函数
	{
		real++;
		image++;
		return CComplex(real, image);
	}
	friend CComplex operator + (CComplex &a, CComplex &b)//定义友元函数：a+b
	{
		return CComplex(a.real + b.real, a.image + b.image);
	}
	friend CComplex operator - (CComplex &a, CComplex &b)//定义友元函数：a-b
	{
		return CComplex(a.real - b.real, a.image - b.image);
	}
};
int main()
{
	double ar, ai, br, bi;
	cout << "Please input two CComplex data:" << endl;//用户输入两个CComplex类的数据
	cout << "A.real=";
	cin >> ar;
	cout << "A.image=";
	cin >> ai;
	cout << "B.real=";
	cin >> br;
	cout << "B.image=";
	cin >> bi;

	CComplex a = CComplex(ar, ai);//构建几个类，分别进行不同的运算
	CComplex b = CComplex(br, bi);
	CComplex c = a + b;
	CComplex d = a - b;
	CComplex e = ++a;
	cout << "Here is the answer of A+B:" << endl;//输出结果
	c.print();
	cout << "Here is the answer of A-B:" << endl;
	d.print();
	cout << "Here is the answer of ++A:" << endl;
	e.print();
	return 0;
}