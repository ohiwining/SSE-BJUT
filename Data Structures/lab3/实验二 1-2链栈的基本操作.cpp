#include<iostream>
using namespace std;
typedef char ElemType;//设置自定义类型
typedef struct Node//定义节点
{
    ElemType data;
    Node *next;//定义指针
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
Stack *Init(Stack *a)//初始化函数
{
    a=new Stack;//分配内存
    a->data='0';//这个节点用于判断是否为空所以设置数据为一个特殊字符
    return a;
}
Stack *Input(Stack *a)//输入函数
{
    Stack *temp=new Stack;
    cout<<"Please input a data:"<<endl;
    cin>>temp->data;
    temp->next=a;//改变栈顶指针
    a=temp;
    return a;
}
Stack *Output(Stack *a)//输出函数
{
    if(a->next!= nullptr && a->data!='0')
    {
        Stack *temp=a;
        a=a->next;
        cout<<"Output data:"<<temp->data<<endl;//输出数据
        delete temp;//释放内存
    }
    else
        cout<<"Stack is empty!"<<endl;
    return a;
}
void All_output(Stack *a)//顺序输出所有数据，不会改变原栈内容
{
    if(a->next== nullptr)//判断是否为空
    {
        cout<<"Stack is empty!"<<endl;
        system("pause");
        return;
    }
    else
        while(a->next!= nullptr | a->data!='0')
        {
            a=Output(a);//开始输出内容
            cout<<endl;
        }
    cout<<"Output finished."<<endl;
    system("pause");
}
void Empty(Stack *a)//判断栈是否为空
{
    if(a->data== '0')//检测到特殊字符
        cout<<"Stack is empty!"<<endl;
    else
        cout<<"Stack is not empty!"<<endl;
    system("pause");
}
int main()
{
    int choice;
    Stack *a=nullptr;
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
