/*��ͷ�ļ���Ҫ����һЩUI����*/
#include<iostream>
#include<stdlib.h>
#include<Windows.h>
using namespace std;
void welcome(void)//��ӭ����
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
	�ڵ��Թ����з��֣����ֱ�ӽ�����رգ��кܴ���ʵ��µ����ļ����ݶ�ʧ��
	������ʵ���û����������׹ر�ATM�����������������һ�仰��
	*/
	system("pause");
}
void menu()//ѡ��˵�����
{
	cout << "1-Withdrawal." << endl;
	cout << "2-Inquiry" << endl;
	cout << "3-Change password" << endl;
	cout << "4-Log out" << endl;
	cout << "Please enter your choice:" << endl;
}
void printdate(void)//�ú�������ͨ����ȡϵͳʱ��������Ʊ�д�ӡȡ��ʱ��
{
	SYSTEMTIME a;
	GetLocalTime(&a);//��ʼ������
	cout << "*      Date:   " << a.wYear << "." << a.wMonth << "." << a.wDay << "      *" << endl;//��ӡ����
	cout << "*      Time:   " << a.wHour << ":" << a.wMinute << ":" << a.wSecond << "       *" << endl;//��ӡʱ��
}