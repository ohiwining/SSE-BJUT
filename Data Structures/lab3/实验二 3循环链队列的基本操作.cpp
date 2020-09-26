#include<iostream>
using namespace std;
typedef char ElemType;//设置自定义类型
typedef struct node//定义节点
{
    ElemType data;//定义数据类型
    node *front;//定义前后指针
    node *next;
}Node;
class Queue//创建队列类
{
private:
    Node *head;//定义头节点
public:
    Queue();
    ~Queue();
    void Input();
    void Output();
    void All_output( );
    void Empty( );
};
Queue::Queue() //构造函数，初始化
{
    head= new Node;//头节点分配内存
    head->next=head;//设定此时节点指针都为空
    head->front=head;
}
Queue::~Queue()//析构函数，释放内存
{
    delete head;
}
void Queue::Input() //入队函数
{
    ElemType input;
    cout<<"Please input a data:"<<endl;//用户输入数据
    cin>>input;
    Node *temp=new Node;//分配内存
    temp->data=input;
    if(head->next==head)//如果队列为空
    {
        head->next=temp;//改变指针
        head->front=temp;
        temp->front=head;
        temp->next=head;
    }
    else//此时队列不为空
    {
        temp->front=head->front;
        temp->next=head;
        head->front->next=temp;
        head->front=temp;
    }
}
void Queue::Output()//出队函数
{
    if(head->next==head)//此时队列为空
        cout<<"Queue is empty!"<<endl;
    else//此时队列不为空
    {
        Node *temp= head->next;
        head->next->next->front=head;
        head->next=head->next->next;
        temp->front=nullptr;//改变指针
        temp->next=nullptr;
        cout<<"Output data:"<<temp->data<<endl;//输出数据
        delete temp;
    }
}
void Queue::All_output()//顺序输出全部数据，会丢失队列中所有数据
{
    if(head->next==head)//此时队列为空
    {
        cout<<"Queue is empty!"<<endl;
        system("pause");
        return;
    }
    else
        while(head->next!=head)
        {
            Output();
            cout<<endl;
        }
    cout<<"Output finished."<<endl;//输出全部数据
    system("pause");
}
void Queue::Empty()//判断队列是否为空
{
    if(head->next==head)
        cout<<"Queue is empty!"<<endl;
    else
        cout<<"Queue is not empty!"<<endl;
    system("pause");
}
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
    cout<<"3-Check if Queue is empty"<<endl;
    cout<<"4-Output all data"<<endl;
    cout<<"5-Quit"<<endl;
    cout<<"Your choice:";
}
int main()
{
    int choice;
    Queue a;
    welcome();
    while(true)
    {
        system("cls");
        menu();
        cin>>choice;
        switch(choice)
        {
            case 1:
                a.Input();
                break;
            case 2:
                a.Output();
                system("pause");
                break;
            case 3:
                a.Empty();
                break;
            case 4:
                a.All_output();
                break;
            case 5:
                cout<<"Program terminated."<<endl;
                return 0;
            default:
                cout<<"Please input again!"<<endl;
        }
    }
}