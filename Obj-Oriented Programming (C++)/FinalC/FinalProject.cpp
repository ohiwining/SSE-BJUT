/*
题目：模拟 ATM 机存取款管理系统设计
学号：18080128
姓名：孙晨伟
时间：2019.5.7 15：35 +0800 
修改时间：2019.5.14 16：33 +0800

该程序的编写使用了Visual Studio Community IDE 2017，使用其它程序打开可能出现乱码
为了模拟现实中的ATM机，该程序设定了仅能使用数字按键交互。因此并没有着力解决输入字母时产生的bug

*/
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<iomanip>
#include"Fundamental.h"//包含所有需要的头文件
using namespace std;
User u[10];//建立用户对象数组
int write(void)//定义读取档案文件的函数
{
	fstream thefile;
	thefile.open("pswd.txt", ios::in);//尝试打开文件
	if (!thefile)
	{
		cout << "There is a problem with server.Please contact authority." << endl;//如果档案文件不存在，该程序便无法继续执行，自动退出。
		cout << "Quitting..." << endl;
		system("pause");
		return 0;
	}
	else
	{
		for (int a = 0; a < 10; a++)//如果文件存在，则开始往用户对象中写入数据
		{
			thefile >> u[a].ID;
			thefile >> u[a].pswd;
			thefile >> u[a].deposit;
			thefile >> u[a].locked;
		}
	}
	thefile.close();//关闭文件
	return 1;
}
int checkpswd(void)//检查用户的账户状态
{
	int i, wt, acc;
	int inputer;
	while (1)
	{
		system("cls");
		cout << "Please input your account:";//先输入账户名
		cin >> acc;
		for (i = 0; i < 10; i++)
		{
			if (acc == u[i].ID)//此时找到账户名了，开始判定
			{
				if (u[i].locked == 1)
				{
					cout << "Your account has been frozen.Please contact authority." << endl;//如果用户的账户已经处于被锁住的状态，则退出程序，并提醒用户去联系相关客服
					cout << "Quitting..." << endl;
					system("pause");
					return -1;
				}
				for (wt = 1; wt <= 3; wt++)//此时用户输入密码，总共有三次机会
				{
					system("cls");
					cout << "Password:";
					cin >> inputer;
					if (inputer == u[i].pswd)//如果输入正确，则进入用户交互界面
					{
						cout << "Welcome back,User " << u[i].ID << "!" << endl;
						system("pause");
						return i;
					}
					else
					{
						cout << "Wrong password! You have " << 3 - wt << " time(s)!" << endl;//如果输入错误，则提示用户输入密码的剩余次数
						system("pause");
					}
				}
				if (wt == 4)
				{
					u[i].locked = 1;
					cout << "Your account has been frozen.Please contact authority." << endl;//三次输入错误，用户的卡将会被锁住
					cout << "Quitting..." << endl;
					system("pause");
					return -1;
				}
			}
		}
		cout << "No such account!Please check if input is correct." << endl;//如果到这一步说明用户输入的账户不存在，可能是输入错误，则返回输入账户的地方
		system("pause");
	}
}
void filewrite(void)//定义写入档案文件的函数
{
	fstream thefile;
	thefile.open("pswd.txt", ios::out);//打开文件
	for (int a = 0; a < 10; a++)//依次写入数据
	{
		thefile << u[a].ID << endl;
		thefile << u[a].pswd << endl;
		thefile << u[a].deposit << endl;
		thefile << u[a].locked << endl;
	}
	thefile.close();//关闭文件
}
int main()
{
	int status;
	status = write();//首先判断能否找到档案文件
	if (status == 0)
		return 0;
	int choice;
	int identity = -1;
	welcome();//欢迎界面
	system("cls");
	identity = checkpswd();//检查用户输入的账户名和密码
	if (identity == -1)//此时登陆没有成功，则写入一次文件，记录是否存在账户被锁住的情况
	{
		filewrite();
		return 0;
	}
	else//登陆成功后
	{
		while (1)
		{
			if (u[identity].locked == 1)//判定用户的卡是否被锁（这个过程主要用在修改密码之后）
			{
				cout << "Your account has been frozen.Please contact authority." << endl;
				cout << "Quitting..." << endl;
				system("pause");
				filewrite();
				return 0;
			}
			system("cls");
			menu();//选择菜单
			cin >> choice;
			switch (choice)
			{
			case 1:
				u[identity].withdrawal();//取款函数
				filewrite();
				break;
			case 2:
				u[identity].inquiry();//查询余额函数
				break;
			case 3:
				u[identity].changepswd();//修改密码函数
				break;
			case 4:
				cout << "Thank you for choosing us!" << endl;//用户选择退出程序
				cout << "Quitting..." << endl;
				system("pause");
				filewrite();//往文件里写入最后的状态
				return 0;
			default:
				cout << "Please input a number between 1 to 4!";//防止用户输入其它数字
				system("pause");
				break;
			}
		}
	}
	filewrite();//再次写入档案文件，防止纰漏
	return 0;
}