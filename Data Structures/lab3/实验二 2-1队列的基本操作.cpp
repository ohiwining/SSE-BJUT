#include<iostream>
using namespace std;
typedef char ElemType;//设置自定义类型
const int MAXSIZE=5;//定义队列的最大长度为5
typedef struct
{
    ElemType data[MAXSIZE];//定义数据类型
    int front;//头指针
    int rear;//尾指针
}Queue;
void welcome()//欢迎界面
{
    cout<<"*****************************************"<<endl;
    cout<<"**                                     **"<<endl;
    cout<<"**   Welcome to my Queue Application   **"<<endl;
    cout<<"**                                     **"<<endl;
    cout<<"**        Made by 18080128 SCW         **"<<endl;
    cout<<"**                                     **"<<endl;
    cout<<"*****************************************"<<endl;
    system("pause");
}
void menu()//用户选择菜单
{
    cout<<"Please input your choice"<<endl;
    cout<<"1-Input data"<<endl;
    cout<<"2-Output data"<<endl;
    cout<<"3-Check if queue is empty"<<endl;
    cout<<"4-Output all data"<<endl;
    cout<<"5-Quit"<<endl;
    cout<<"Your choice:";
}
Queue Init(Queue a)//初始化函数
{
    a.front=0;//设定头指针尾指针都是0
    a.rear=0;
    return a;
}
Queue Input(Queue a)//输入函数
{
    if (a.front==(a.rear+1)%MAXSIZE)//判断队列已满的条件
    {
        cout<<"Queue is full!"<<endl;
        return a;
    }
    ElemType temp;
    cout<<"Please input a data:"<<endl;//此时队列有空位
    cin>>temp;
    a.rear=(a.rear+1)%MAXSIZE;//移动尾指针
    a.data[a.rear]=temp;
    return a;
}
Queue Output(Queue a)//输出函数
{
    if(a.rear==a.front)//判断队列为空的条件
        cout<<"Queue is empty!"<<endl;
    else
    {
        ElemType temp;
        a.front=(a.front+1)%MAXSIZE;//此时队列不为空，则输出头指针所指节点的数据
        temp=a.data[a.front];
        cout<<"Output data:"<<temp<<endl;//输出数据
    }
    return a;
}
void All_output(Queue a)//顺序输出全部数据，不会改变队列的内容
{
    if(a.rear==a.front)//判断队列为空
    {
        cout<<"Queue is empty!"<<endl;
        system("pause");
        return;
    }
    else
        while(a.rear!=a.front)//当队列不为空时，持续输出
        {
            a=Output(a);
            cout<<endl;
        }
    cout<<"Output finished."<<endl;
    system("pause");
}
void Empty(Queue a)//判断队列是否为空
{
    if(a.rear==a.front)
        cout<<"Queue is empty!"<<endl;
    else
        cout<<"Queue is not empty!"<<endl;
    system("pause");
}
int main()
{
    int choice;
    Queue a;
    welcome();
    a=Init(a);
    while(true)
    {
        system("cls");
        menu();
        cin>>choice;
        switch(choice)
        {
            case 1:
                a=Input(a);
                break;
            case 2:
                a=Output(a);
                system("pause");
                break;
            case 3:
                Empty(a);
                break;
            case 4:
                All_output(a);
                break;
            case 5:
                cout<<"Program terminated."<<endl;
                return 0;
            default:
                cout<<"Please input again!"<<endl;
        }
    }
}
