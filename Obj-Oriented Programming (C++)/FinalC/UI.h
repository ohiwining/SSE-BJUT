/*该头文件主要包含一些UI界面*/
#include<iostream>
#include<stdlib.h>
#include<Windows.h>
using namespace std;
void welcome(void)//欢迎界面
{
	cout << "***************************************" << endl;
	cout << "**      Welcome to use our ATM!      **" << endl;
	cout << "**                                   **" << endl;
	cout << "**             Ver.1.0               **" << endl;
	cout << "**                                   **" << endl;
	cout << "**         Made by 18080128          **" << endl;
	cout << "**                                   **" << endl;
	cout << "***************************************" << endl;
	cout << "Tips: In order not to damage this ATM, please do not shot it down directly." << endl;
	/*
	在调试过程中发现，如果直接将程序关闭，有很大概率导致档案文件内容丢失。
	基于现实中用户并不能轻易关闭ATM机，因此特意加上最后一句话。
	*/
	system("pause");
}
void menu()//选择菜单界面
{
	cout << "1-Withdrawal." << endl;
	cout << "2-Inquiry" << endl;
	cout << "3-Change password" << endl;
	cout << "4-Log out" << endl;
	cout << "Please enter your choice:" << endl;
}
void printdate(void)//该函数用于通过获取系统时间来往发票中打印取款时间
{
	SYSTEMTIME a;
	GetLocalTime(&a);//初始化变量
	cout << "*      Date:   " << a.wYear << "." << a.wMonth << "." << a.wDay << "      *" << endl;//打印日期
	cout << "*      Time:   " << a.wHour << ":" << a.wMinute << ":" << a.wSecond << "       *" << endl;//打印时间
}