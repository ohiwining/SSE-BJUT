#include <iostream>
using namespace std;
typedef char ElemType;//设定特殊数据格式
const int MAXLENGTH = 30;//设定顺序表最大值
ElemType data[MAXLENGTH];//生命顺序表
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
void init(ElemType temp[])//初始化顺序表
{
    for (int i = 0; i <= MAXLENGTH; i++) {
        temp[i]='0';//让数组内容为0，表示初始化
    }
}
void insert(ElemType temp[])//插入数据函数
{
	system("cls");
    if(temp[MAXLENGTH]!='0')
    {
        cout<<"DataBase is full! No more spaces!\n";//防止顺序表溢出
        system("pause");
        return;
    }
    int position;
    ElemType a_node;//如果没有溢出则新建一个数据节点
    cout<<"Please input data:";
    cin>>a_node;
    cout<<"Please input position:";//用户可自行决定位置
    cin>>position;
    for (int i = MAXLENGTH; i >= position; i--) {
        temp[i]=temp[i-1];
    }
    temp[position]=a_node;
    cout<<"Insert successfully!\n";
    system("pause");
}
void dele(ElemType temp[])//删除数据函数
{
	system("cls");
    int position;
    cout<<"Which node you decide to delete?\n";
    cin>>position;
    for (int i = position; i <= MAXLENGTH; i++) {
        temp[i]=temp[i+1];
    }
    temp[MAXLENGTH]='0';//使顺序表最后一个数据节点为0，统一格式
    cout<<"Delete successfully!\n";
    system("pause");
}
void find_by_number(ElemType temp[])//根据位置查找数据函数
{
	system("cls");
    int choice;
    cout<<"Where is the node you decide to find?\n";
    cin>>choice;
    cout<<"NO."<<choice<<" is "<<temp[choice]<<"\n";
    system("pause");
}
void find_by_data(ElemType temp[])//根据数据内容查找数据函数
{
	system("cls");
    ElemType choice;
    int status=0;
    cout<<"Which node you decide to find?\n";
    cin>>choice;
    for (int i = 1; i <= MAXLENGTH; i++) {
        if(temp[i]==choice) {
            cout << "Content :" << temp[i] << "\n";//打印结果
            cout << "Position :" << i << "\n";
            status=1;
        }
    }
    if(!status)//如果没有搜索到则提示用户没有这样的数据点
    {
        cout<<"No such node!\n";
    }
    system("pause");
}
int get_length(ElemType temp[])//得到顺序表长度的函数
{
    int length=0;
    for (int i = 1; i <= MAXLENGTH; i++) {
        if(temp[i]!='0')
            length++;
    }
    return length;//返回顺序表函数，返回值类型为int
}
void allprint(ElemType temp[])//顺序输出顺序表所有内容
{
	system("cls");
    for (int i = 1; i <= get_length(temp); i++) {
        cout<<"NO."<<i<<" is :"<<data[i]<<"\n";
    }
    system("pause");
}
int main()//主函数
{
    int choice;
    welcome();
    init(data);//初始化顺序表
    while(true)
    {
        system("cls");
        menu();
        cin>>choice;//由用户根据菜单选择对应功能
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
            	system("cls");
                cout<<get_length(data)<<"\n";
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