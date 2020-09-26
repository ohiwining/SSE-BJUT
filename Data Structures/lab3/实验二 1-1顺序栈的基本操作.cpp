#include<iostream>
using namespace std;
typedef char ElemType;//设置自定义类型
const int MAXSIZE=30;//定义栈的最大高度为30
typedef struct
{
    ElemType data[MAXSIZE];//定义栈内部数据
    int top;//栈顶指针
}Stack;
void welcome()//欢迎界面
{
    cout<<"*****************************************"<<endl;
    cout<<"**                                     **"<<endl;
    cout<<"**   Welcome to my Stack Application   **"<<endl;
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
    cout<<"3-Check if stack is empty"<<endl;
    cout<<"4-Output all data at inverted order"<<endl;
    cout<<"5-Quit"<<endl;
    cout<<"Your choice:";
}
Stack Init(Stack a)//初始化函数，定义栈顶指针为-1
{
    a.top=-1;
    return a;
}
Stack Input(Stack a)//输入函数，用户输入一个数据
{
    if(a.top==MAXSIZE-1)//此时栈已满
    {
        cout<<"Stack is full!"<<endl;
        return a;
    }
    ElemType temp;
    cout<<"Please input a data:"<<endl;
    cin>>temp;
    a.top++;
    a.data[a.top]=temp;
    return a;
}
Stack Output(Stack a)//输出栈顶元素
{
    if(a.top>-1)
    {
        ElemType temp;
        temp=a.data[a.top];
        a.top--;
        cout<<"Output data:"<<temp<<endl;//输出数据
    }
    else
        cout<<"Stack is empty!"<<endl;//如果栈为空则提示用户没有数据
    return a;
}
void All_output(Stack a)//顺序输出全部数据，不会改变栈的内容
{
    if(a.top==-1)//此时栈为空
    {
        cout<<"Stack is empty!"<<endl;
        system("pause");
        return;
    }
    else
        while(a.top!=-1)//当栈顶指针不为-1时
        {
            a=Output(a);
            cout<<endl;
        }
    cout<<"Output finished."<<endl;
    system("pause");
}
void Empty(Stack a)//判断栈是否为空
{
    if(a.top==-1)
        cout<<"Stack is empty!"<<endl;
    else
        cout<<"Stack is not empty!"<<endl;
    system("pause");
}
int main()
{
    int choice;
    Stack a;
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
