#include <iostream>
using namespace std;
typedef char ElemType;
typedef struct Sqlist
{
    char content;
    struct Sqlist *next;
}List;
void menu()
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
List *insert(List *data)
{
    List *input,*temp;
    input=new List;
    temp=data;
    ElemType a_node;
    cout<<"Please input data:";
    cin>>a_node;
    input->content=a_node;
    input->next=nullptr;
    if(data==nullptr)
    {
        data=input;
    }
    else
    {
        while(temp->next!=nullptr)
        {
            temp=temp->next;
        }
        temp->next=input;
    }
    return data;
}
List *dele(List *data)
{
    int position,i=0;
    if(data==nullptr)
    {
        cout<<"DataBase is empty!\n";
        system("pause");
        return data;
    }
    List *temp1=data,*temp2=data;
    cout<<"Which node you decide to delete?\n";
    cin>>position;
    position--;
    while(i!=position&&temp1->next!=nullptr)
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
        delete temp1;
        cout<<"Delete successfully!\n";
        system("pause");
    }
    else
        cout<<"No such node!\n";
    return data;
}
void find_by_number(List *data)
{
    int position;
    cout<<"Where is the node you decide to find?\n";
    cin>>position;
    position--;
    for (int i = 0; data!= nullptr; data=data->next)
    {
        if(i==position)
        {
            cout<<"NO."<<i+1<<": "<<data->content<<"\n";
            return;
        }
        i++;
    }
    cout<<"No such node!\n";
    system("pause");
}
void find_by_data(List *data)
{
    ElemType choice;
    int status=0;
    cout<<"Which node you decide to find?\n";
    cin>>choice;
    for (int i = 1; data!= nullptr; data=data->next)
    {
        if(data->content==choice)
        {
            cout << "Content :" << data->content << "\n";
            cout << "Position :" << i << "\n";
            status=1;
        }
        i++;
    }
    if(!status)
    {
        cout<<"No such node!\n";
    }
    system("pause");
}
int get_length(List *data)
{
    int length=0;
    for (; data!= nullptr; data=data->next)
    {
        length++;
    }
    return length;
}
void allprint(List *data)
{
    int i=0;
    system("cls");
    if(data==nullptr)
        cout<<"No data!\n";
    else
        {
            while(data!=nullptr)
            {
                i++;
                cout<<"NO."<<i<<": "<<data->content<<"\n";
                data=data->next;
            }
        }
}
int main()
{
    List *data=nullptr;
    int choice;
    while(true)
    {
        system("cls");
        menu();
        cin>>choice;
        switch(choice)
        {
            case 1:
                data=insert(data);
                system("pause");
                break;
            case 2:
                data=dele(data);
                system("pause");
                break;
            case 3:
                find_by_number(data);
                system("pause");
                break;
            case 4:
                find_by_data(data);
                system("pause");
                break;
            case 5:
                cout<<get_length(data)<<"\n";
                system("pause");
                break;
            case 6:
                allprint(data);
                system("pause");
                break;
            case 7:
                return 0;
            default:
                cout<<"False input!\n";
                system("pause");
                break;
        }
    }
}