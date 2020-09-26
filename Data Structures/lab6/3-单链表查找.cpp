#include <iostream>
#include <random>
using namespace std;
typedef struct node//定义链表节点的结构体
{
    unsigned int data;
    node *next= nullptr;
}Node;
int main()
{
    int n;//用户决定链表长度
    cout<<"Please input the number of nodes: "<<endl;
    cin>>n;

    default_random_engine rng;//自动生成链表中的数，同时这个数字也是关键字
    unsigned int key[n],temp;
    key[0]=rng()%30;
    for (int i = 1; i < n; ++i) {
        temp=rng()%30+1;
        key[i]=key[i-1]+temp;//这条语句保证关键字中的数是递增的  而且不会出现重复的
    }
    cout<<"Number sequence: "<<endl;//输出关键字中的所有数字
    for (int i = 0; i < n; ++i) {
        cout<<key[i]<<" ";
    }

    Node *a=new node;//创建一个新链表
    Node *b=a;
    a->data=key[0];
    for (int i = 1; i < n; ++i) {
        Node *rear=new node;
        rear->data=key[i];//节点中数字为关键字中的数字
        b->next=rear;
        b=rear;
    }

    int search,which_node=0;//链表查找功能语句
    cout<<endl<<"Please input a number to search:"<<endl;//输入要查找的数字
    cin>>search;
    b=a;
    while(b!=nullptr)
    {
        if (search==b->data)
        {
            cout<<"Number found! Number: "<<search<<" is in "<<which_node+1<<"th node."<<endl;//找到结果时输出它在哪个节点
            return 0;
        }
        which_node++;//节点标识符加1
        b=b->next;
    }
    cout<<"Number not found! "<<endl;//此时函数仍然没有结束说明数字没有找到
    return 0;
}