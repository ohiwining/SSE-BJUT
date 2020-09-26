#include <iostream>
using namespace std;
typedef char ElemType;//设定特殊数据格式
typedef struct Sqlist//定义链表
{
    ElemType content;
    struct Sqlist *next;
}List;
void welcome()
{
    cout<<"***************************************************\n";
    cout<<"***************************************************\n";
    cout<<"***                                             ***\n";
    cout<<"***   Welcome to use our data storing program!  ***\n";
    cout<<"***                                             ***\n";
    cout<<"***                                             ***\n";
    cout<<"***             Made by 18080128                ***\n";
    cout<<"***                                             ***\n";
    cout<<"***         Press anykey to continue!           ***\n";
    cout<<"***                                             ***\n";
    cout<<"***************************************************\n";
    cout<<"***************************************************\n";
    system("pause");
}
void menu()//用户界面，菜单
{
    cout<<"1-Insert a node\n";
    cout<<"2-Delete a node\n";
    cout<<"3-Find a node by number\n";
    cout<<"4-Find a node by content\n";
    cout<<"5-Print the number of nodes\n";
    cout<<"6-Print all nodes\n";
    cout<<"7-Quit\n";
    cout<<"Please input your choice:";
}
List *insert(List *data)//插入数据函数
{
    system("cls");
    List *input,*temp;
    input=new List;//分配内存
    temp=data;
    ElemType a_node;
    cout<<"Please input data:";
    cin>>a_node;
    input->content=a_node;
    input->next=nullptr;
    if(data==nullptr)//检查链表是否为空
    {
        data=input;
    }
    else
    {
        while(temp->next!=nullptr)//此时链表不为空
        {
            temp=temp->next;
        }
        temp->next=input;//尾插法插入数据
    }
    cout<<"Insert successfully!\n";
    system("pause");
    return data;
}
List *dele(List *data)//删除数据函数
{
    system("cls");
    int position,i=0;
    if(data==nullptr)
    {
        cout<<"DataBase is empty!\n";//如果链表为空
        system("pause");
        return data;
    }
    List *temp1=data,*temp2=data;
    cout<<"Which node you decide to delete?\n";//用户选择要删除哪一位置的节点
    cin>>position;
    position--;
    while(i!=position&&temp1->next!=nullptr)//检测用户输入的位置是否超过链表本身长度以及准备删除
    {
        i++;
        temp2=temp1;
        temp1=temp1->next;
    }
    if(i==position)
    {
        if(temp1==data)
        {
            data=temp2->next;
        }
        else
            temp2->next=temp1->next;
        delete temp1;//释放内存
        cout<<"Delete successfully!\n";
        system("pause");
    }
    else
        {
            cout<<"No such node!\n";
            system("pause");
        }//此时不满足删除的条件，提醒用户无法删除
    return data;
}
void find_by_number(List *data)//根据位置查找数据函数
{
    system("cls");
    int position;
    cout<<"Where is the node you decide to find?\n";
    cin>>position;
    position--;
    for (int i = 0; data!= nullptr; data=data->next)
    {
        if(i==position)
        {
            cout<<"NO."<<i+1<<": "<<data->content<<"\n";
            system("pause");
            return;
        }
        i++;
    }
    cout<<"No such node!\n";
    system("pause");
}
void find_by_data(List *data)//根据数据内容查找数据函数
{
    system("cls");
    ElemType choice;
    int status=0;
    cout<<"Which node you decide to find?\n";
    cin>>choice;
    for (int i = 1; data!= nullptr; data=data->next)
    {
        if(data->content==choice)//便于输出多个相同数据内容的节点
        {
            cout << "Content :" << data->content << "\n";
            cout << "Position :" << i << "\n";
            status=1;
        }
        i++;
    }
    if(!status)//此时查找不到用户输入的内容，提示没有这样的节点
    {
        cout<<"No such node!\n";
    }
    system("pause");
}
int get_length(List *data)//得到链表长度的函数
{
    int length;
    for (length=0; data!= nullptr; data=data->next)
    {
        length++;
    }
    return length;
}
void allprint(List *data)//顺序输出链表所有内容
{
    system("cls");
    int i=0;
    system("cls");
    if(data==nullptr)
        cout<<"No data!\n";//检查链表是否为空
    else
        {
            while(data!=nullptr)
            {
                i++;
                cout<<"NO."<<i<<": "<<data->content<<"\n";
                data=data->next;
            }
        }
    system("pause");
}
int main()//主函数
{
    List *data=nullptr;
    int choice;
    welcome();
    while(true)
    {
        system("cls");
        menu();
        cin>>choice;//由用户根据菜单选择对应功能
        switch(choice)
        {
            case 1:
                data=insert(data);
                break;
            case 2:
                data=dele(data);
                break;
            case 3:
                find_by_number(data);
                break;
            case 4:
                find_by_data(data);
                break;
            case 5:
                system("cls");
                cout<<"It has "<<get_length(data)<<" node(s).\n";
                system("pause");
                break;
            case 6:
                allprint(data);
                break;
            case 7:
                system("cls");
                cout<<"Bye!\n";
                system("pause");
                return 0;//程序唯一出口
            default:
                cout<<"False input!\n";
                system("pause");
                break;
        }
    }
}