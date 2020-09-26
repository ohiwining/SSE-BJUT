//#include"pch.h"//This program is written in Visual Studio IDE community 2017, it is required to include"pch.h".
#include<iostream>
#include<stdlib.h>
using namespace std;
class Stu//创建学生的类
{
private:
	int ID;//创建私有数据来保存学生信息
	char name[30];
	int math;
	int english;
	int computer;
	int sum;
	double average;
public:
	void set_stu_inf()//函数：设置学生信息
	{
		cout << "ID:" << endl;
		cin >> ID;
		cout << "Name:" << endl;
		cin >> name;
		cout << "Math:" << endl;
		cin >> math;
		cout << "English:" << endl;
		cin >> english;
		cout << "Computer:" << endl;
		cin >> computer;
		sum = math + english + computer;
		average = sum / 3.0;
	}
	void get_reg_num()//函数：输出一个学生的相关信息
	{
		cout << "ID         " << ID << endl;
		cout << "Name       " << name << endl;
		cout << "Math       " << math << endl;
		cout << "English    " << english << endl;
		cout << "Computer   " << computer << endl;
		cout << "Sum        " << sum << endl;
		cout << "Average    " << average << endl;
	}
	void find(Stu student[], int number)//函数：输入一个学生的学号并输出他的信息
	{
		int findid, loop, status = 1;
		cout << "Please input the ID:" << endl;
		cin >> findid;
		for (loop = 0; loop <= number; loop++)
		{
			if (findid == student[loop].ID)
			{
				student[loop].get_reg_num();
				system("pause");
				status = 1;
				break;
			}
			else
				status = 0;
		}
		if (status == 0)
		{
			cout << "No such ID!" << endl;//如果输入的数据没有找到则提示用户没有这个id
			system("pause");
		}
	}

	void highsum(Stu student[], int number)//函数：找到最高分的学生并输出他的信息
	{
		int highscore = 0, highid, loop;
		if (number == 0)
		{
			cout << "No information recorded!" << endl;//如果没有录入任何学生就提示没有数据
		}
		else
		{
			for (loop = 0; loop < number; loop++)
			{
				if (highscore < student[loop].sum)
				{
					highscore = student[loop].sum;
					highid = loop;
				}
			}
			student[highid].get_reg_num();
		}
		system("pause");
	}

	void avg(Stu student[], int number)//函数：计算全班平均分（总分）
	{
		int loop;
		double totalaver, total = 0;
		if (number == 0)
		{
			cout << "No information recorded!" << endl;//如果没有录入任何学生就提示没有数据
		}
		else
		{
			for (loop = 0; loop < number; loop++)
			{
				total += student[loop].sum;
			}
			totalaver = total / number;
			cout << "Average score in class is: " << totalaver << endl;
		}
		system("pause");
	}
};

void menu()//函数：打印一个开始菜单方便使用
{
	cout << "1- Create a student " << endl;
	cout << "2- Find a student " << endl;
	cout << "3- Find the highest score " << endl;
	cout << "4- Calculate the average score " << endl;
	cout << "5- Quit" << endl;
	cout << "Please choose: ";
}

Stu create()//在这里创建一个学生的类并返回给主函数
{
	Stu temp;
	temp.set_stu_inf();
	return temp;
}

int main()
{
	int choice, number = 0;
	Stu student[50];//创建学生数组
	while (1)//主程序从这里运行
	{
		system("cls");
		menu();
		cin >> choice;
		switch (choice)//判断用户的选择并进入相应的函数
		{
		case 1:
			system("cls");
			student[number] = create();
			number++;
			break;
		case 2:
			system("cls");
			student[0].find(student, number);
			break;
		case 3:
			system("cls");
			student[0].highsum(student, number);
			break;
		case 4:
			system("cls");
			student[0].avg(student, number);
			break;
		case 5:
			return 0;
		default:
			cout << "Input incorrect!";
			system("pause");
			break;
		}
	}
}