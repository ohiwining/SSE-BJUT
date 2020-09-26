#include<iostream>
using namespace std;
typedef struct//定义栈
{
    char *data=new char;//分配内存，不指定长度
    int top=-1;//初始化栈顶指针
}Stack;
Stack Input(Stack a,char ch)//向栈里存入一个字符的函数
{
    a.top++;//改变栈顶指针
    a.data[a.top]=ch;
    return a;
}
char Output(Stack &a)//出栈函数
{
    char temp;
    temp=a.data[a.top];
    a.top--;
    return temp;//返回值为出栈元素
}
bool Check(const string& str)//检测是否对称的主要函数
{
    int len=str.length();//检测字符串长度
    Stack front = Stack(), rear = Stack();//定义两个栈，一头一尾
    for (int i = 0; 2*i<len ; ++i)
    {
        front = Input(front, str[i]);//向栈里顺序存入字符
        rear = Input(rear, str[len-1-i]);//向栈里倒序存入字符
    }
    for (int i = 0; 2*i<len ; ++i)
    {
        if(Output(front)!=Output(rear))//判断两个栈的出栈元素是否始终相等
            return false;//只要出现不相等就返回false
    }
    return true;//安全退出循环，证明出栈元素时相等的
}
int main()
{
    string a;
    cout<<"Please input a string"<<endl;//由用户输入字符串
    cin >> a;
    if(Check(a))//此时判断字符串为对称
        cout<<"String fits symmetry!"<<endl;
    else//此时判断为不对称
        cout<<"String does not fits symmetry!"<<endl;
}