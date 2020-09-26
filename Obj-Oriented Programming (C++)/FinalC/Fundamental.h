/*这个头文件创建并定义了User类*/
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<iomanip>
#include"UI.h"
using namespace std;
class User//创建类
{
public:
	double deposit;//存款，数据为double型
	int ID;//账户号码，数据为int型
	int pswd;//账户密码，数据为int型
	int locked;//是否为锁定状态，数据为int型
	void inquiry(void)//定义查询余额的函数
	{
		system("cls");
		cout << "Remaining balance:" << deposit << "yuan." << endl;
		system("pause");
	}
	void withdrawal(void)//定义取款的函数
	{
		double withdraw;
		char choice;
		system("cls");
		cout << "Please input the cash you need:" << endl;//由用户输入取款金额
		cout << "Tips: 100 yuan at least,500 yuan at most at one time." << endl;//提示用户最小金额为100元，最大金额为500元
		cin >> withdraw;
		if (withdraw > deposit)//如果用户输入的金额大于余额，则提示金额不够
		{
			cout << "No enough deposit!" << endl;
			system("pause");
			return;
		}
		if (withdraw < 100 | withdraw > 500)//判断取钱金额是否在可取范围内
		{
			cout << "The amount is incorrect ! Please input a number between 100 and 500 !" << endl;
			system("pause");
		}
		else//如果金额符合要求，则取款顺利进行
		{
			deposit -= withdraw;
			cout << "Succeed!" << endl;
			cout << "Press y to print an invoice,press n to skip." << endl;//用户判断是否需要打印发票
			cin >> choice;
			if (choice == 'y')
			{
				cout << "*******************************" << endl;
				cout << "*      Withdrawal Invoice     *" << endl;
				cout << "*                             *" << endl;
				cout << "*       User:     " << ID << "         *" << endl;
				cout << "*                             *" << endl;
				cout << "*     Withdrawn:  " << withdraw << "         *" << endl;
				cout << "*                             *" << endl;
				cout << "*     Remaining:  " << deposit << "      *" << endl;
				cout << "*                             *" << endl;
				printdate();//调用能在发票中打印时间的函数
				cout << "*******************************" << endl;
				system("pause");
			}

		}
		return;
	}
	void changepswd(void)//定义更改密码的函数
	{
		int input;
		int a;
		system("cls");
		for (a = 1; a <= 3;)
		{
			system("cls");
			cout << "Please input current password:" << endl;//需要重新输一次密码
			cin >> input;
			if (input == pswd)//如果密码输入正确，则跳出循环
				break;
			else
			{
				cout << "Wrong password! You have " << 3 - a << " time(s)!" << endl;//如果输入错误，则提示用户剩几次机会
				system("pause");
				a++;
			}
		}
		if (a == 4)//此时如果原密码输入错误，卡仍然会被锁定
		{
			locked = 1;
			return;
		}
		system("cls");
		cout << "Please input a new password:" << endl;//如果输入成功，则更改密码的流程可以顺利进行
		cin >> pswd;
		cout << "Password has been changed." << endl;
		system("pause");
	}
};