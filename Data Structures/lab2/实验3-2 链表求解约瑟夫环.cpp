#include <iostream>
using namespace std;
typedef struct Them//定义链表结构
{
    int num;//用于存储序号
    struct Them *next;
}Link;
class JosephusCircle
{
public:
    explicit JosephusCircle(int n,int s,int m)
    {
        Link *temp1= nullptr;//定义三个链表，head为主要链表，其余为临时链表，此处都不分配内存
        Link *temp2= nullptr;
        Link *head = nullptr;
        int i;
        for(i = 1;i <= n;i++)//初始化链表
        {
            temp1 = new Link;//创造一个临时的新节点并分配内存
            temp1->num = i;
            if(head == nullptr)//如果主要链表为空
            {
                head = temp1;//临时链表直接覆盖主要链表
            }
            else//此时主要链表并不为空
            {
                temp2->next = temp1;//临时链表1接到临时链表2后端
            }
            temp2 = temp1;//临时2后移，作为链表的最后一个节点
        }
        temp1->next = head;//最后一个节点的尾指针指向头节点，循环链表建立完成
        temp1 = head;//临时1复制主链表
        for(i = 1;i < s;i++)
        {
            temp2=temp1;//当循环执行完毕时，temp2表示开局一个人的节点
            temp1=temp1->next;
        }
        while(temp1->next != temp1)//while可进行多次遍历
        {
            for(i = 1;i < m;i++)//遍历一轮，找到要淘汰的人
            {
                temp2 = temp1;
                temp1 = temp1->next;
            }
            temp2->next = temp1->next;//复制即将被删除的节点
            printout(temp1->num);//输出这轮被淘汰的人的号码
            delete temp1;//释放内存
            temp1 = temp2->next;//指针重定向，保持链表完整
        }
        printout(temp1->num);//此时还剩最后一个人，这个人满足temp1->next == temp1的关系，因此直接输出
        cout<<endl<<"Finished.\n";
        cout<<"Press anykey to quit.\n";
        system("pause");
    }
    static void printout(int num)
    {
        cout<<num<<"  ";//用于输出当前淘汰的人的编号
    }
};
bool check(int n,int s,int m)//用于检查用户输入的数字有没有问题
{
    if (m<=0)//m不可小于0，如果出现则提示
    {
        cout<<"M cannot smaller than 1!\n";
        system("pause");
        return false;
    }
    if (m>n)//n不可小于m，如果出现则提示
    {
        cout<<"N cannot smaller than M!\n";
        system("pause");
        return false;
    }
    return true;//如果两个判断语句都没有执行，则返回true，程序可以继续运行
}
void welcome()
{
    cout<<"***************************************************\n";
    cout<<"***************************************************\n";
    cout<<"***                                             ***\n";
    cout<<"***     Welcome to try JosephusCircle game!     ***\n";
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
int main()
{
    welcome();
    system("cls");
    int n,s,m;
    cout<<"***************************************\n";
    cout<<"*Please input the number of people(N): ";
    cin>>n;
    system("cls");
    cout<<"***************************************\n";
    cout<<"*Please input the number of first people(S): ";
    cin>>s;
    system("cls");
    cout<<"************************************\n";
    cout<<"*Please input the number that decide which one to wipe out(M): ";
    cin>>m;
    system("cls");
    if (check(n,s,m))//判断用户输入是否有误
    {cout<<"Result:\n";
        JosephusCircle(n,s,m);}//开始运行主程序
    else
        main();//此时用户输入有误，递归主函数让用户重新输入

}
