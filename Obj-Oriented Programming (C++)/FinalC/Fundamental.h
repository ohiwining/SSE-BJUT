/*���ͷ�ļ�������������User��*/
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<iomanip>
#include"UI.h"
using namespace std;
class User//������
{
public:
	double deposit;//������Ϊdouble��
	int ID;//�˻����룬����Ϊint��
	int pswd;//�˻����룬����Ϊint��
	int locked;//�Ƿ�Ϊ����״̬������Ϊint��
	void inquiry(void)//�����ѯ���ĺ���
	{
		system("cls");
		cout << "Remaining balance:" << deposit << "yuan." << endl;
		system("pause");
	}
	void withdrawal(void)//����ȡ��ĺ���
	{
		double withdraw;
		char choice;
		system("cls");
		cout << "Please input the cash you need:" << endl;//���û�����ȡ����
		cout << "Tips: 100 yuan at least,500 yuan at most at one time." << endl;//��ʾ�û���С���Ϊ100Ԫ�������Ϊ500Ԫ
		cin >> withdraw;
		if (withdraw > deposit)//����û�����Ľ�����������ʾ����
		{
			cout << "No enough deposit!" << endl;
			system("pause");
			return;
		}
		if (withdraw < 100 | withdraw > 500)//�ж�ȡǮ����Ƿ��ڿ�ȡ��Χ��
		{
			cout << "The amount is incorrect ! Please input a number between 100 and 500 !" << endl;
			system("pause");
		}
		else//���������Ҫ����ȡ��˳������
		{
			deposit -= withdraw;
			cout << "Succeed!" << endl;
			cout << "Press y to print an invoice,press n to skip." << endl;//�û��ж��Ƿ���Ҫ��ӡ��Ʊ
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
				printdate();//�������ڷ�Ʊ�д�ӡʱ��ĺ���
				cout << "*******************************" << endl;
				system("pause");
			}

		}
		return;
	}
	void changepswd(void)//�����������ĺ���
	{
		int input;
		int a;
		system("cls");
		for (a = 1; a <= 3;)
		{
			system("cls");
			cout << "Please input current password:" << endl;//��Ҫ������һ������
			cin >> input;
			if (input == pswd)//�������������ȷ��������ѭ��
				break;
			else
			{
				cout << "Wrong password! You have " << 3 - a << " time(s)!" << endl;//��������������ʾ�û�ʣ���λ���
				system("pause");
				a++;
			}
		}
		if (a == 4)//��ʱ���ԭ����������󣬿���Ȼ�ᱻ����
		{
			locked = 1;
			return;
		}
		system("cls");
		cout << "Please input a new password:" << endl;//�������ɹ����������������̿���˳������
		cin >> pswd;
		cout << "Password has been changed." << endl;
		system("pause");
	}
};