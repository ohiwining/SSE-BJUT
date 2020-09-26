#include <iostream>
using namespace std;
typedef char ElemType;
const int MAXLENGTH = 30;
ElemType data[MAXLENGTH];
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
void init(ElemType temp[])
{
    for (int i = 0; i <= MAXLENGTH; i++) {
        temp[i]='0';
    }
}
void insert(ElemType temp[])
{
    if(temp[MAXLENGTH]!='0')
    {
        cout<<"DataBase is full! No more spaces!\n";
        system("pause");
        return;
    }
    int position;
    ElemType a_node;
    cout<<"Please input data:";
    cin>>a_node;
    cout<<"Please input position:";
    cin>>position;
    for (int i = MAXLENGTH; i >= position; i--) {
        temp[i]=temp[i-1];
    }
    temp[position]=a_node;
}
void dele(ElemType temp[])
{
    int position;
    cout<<"Which node you decide to delete?\n";
    cin>>position;
    for (int i = position; i <= MAXLENGTH; i++) {
        temp[i]=temp[i+1];
    }
    temp[MAXLENGTH]='0';
}
void find_by_number(ElemType temp[])
{
    int choice;
    cout<<"Where is the node you decide to find?\n";
    cin>>choice;
    cout<<"NO."<<choice<<" is "<<temp[choice]<<"\n";
    system("pause");
}
void find_by_data(ElemType temp[])
{
    ElemType choice;
    int status=0;
    cout<<"Which node you decide to find?\n";
    cin>>choice;
    for (int i = 1; i <= MAXLENGTH; i++) {
        if(temp[i]==choice) {
            cout << "Content :" << temp[i] << "\n";
            cout << "Position :" << i << "\n";
            status=1;
        }
    }
    if(!status)
    {
        cout<<"No such node!\n";
    }
    system("pause");
}
int get_length(ElemType temp[])
{
    int length=0;
    for (int i = 1; i <= MAXLENGTH; i++) {
        if(temp[i]!='0')
            length++;
    }
    return length;
}
void allprint()
{
    for (int i = 1; i <= MAXLENGTH; i++) {
        cout<<"NO."<<i<<" is :"<<data[i]<<"\n";
    }
    system("pause");
}
int main()
{
    int choice;
    init(data);
    while(true)
    {
        system("cls");
        menu();
        cin>>choice;
        switch(choice)
        {
            case 1:
                insert(data);
                break;
            case 2:
                dele(data);
                break;
            case 3:
                find_by_number(data);
                break;
            case 4:
                find_by_data(data);
                break;
            case 5:
                cout<<get_length(data)<<"\n";
                system("pause");
                break;
            case 6:
                allprint();
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