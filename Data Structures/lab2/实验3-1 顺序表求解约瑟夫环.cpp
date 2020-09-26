#include <iostream>
using namespace std;
class JosephusCircle
{
public:
    explicit JosephusCircle(int n,int s,int m)
    {
        int status=1;//用于检查程序是否结束运行
        status=kill(n,s,m);//开始运行游戏的主程序并更新程序运行状态
        cout<<endl;
        cout<<"Game finished.\n";//提示用户游戏已经结束
        cout<<"Press anykey to quit.\n";
        system("pause");
    }
    static int kill(int n,int s,int m)//游戏主程序，n代表总人数，s代表开始的人，m表示数到几就淘汰
    {
        int a[n];//代表所有参加的人
        for(int i=0;i<n;i++)
        {
            a[i]=i+1;//初始化，0代表死亡，其余数代表活着
        }
        int i=s-1,count=0,t=0;//此时的i也表示开始的人，由于数组从0开始所以减一
        while(count < n - 1)//开始遍历，count表示已经淘汰的人
        {
            if(a[i] != 0)
                t++;//检查到这个人活着，用于淘汰人的计数器就+1
            if(t == m)//此时计数器等于m
            {
                t = 0;
                count++;//已经淘汰的人数+1
                printout(a[i]);//输出他的编号
                a[i] = 0;//设定这个人死亡
            }
            i++;//表示下次遍历就从下一个人开始了
            if(i == n)//如果下次开始的人已经等于总人数（已经超出数组范围）就让i归零
                i = 0;
        }
        for(i=0;i<n;i++)
            if(a[i]!=0)//由于此时还剩最后一个人无法报数，因此世界寻找这个人并输出他的编号
            {
                printout(a[i]);
                return 0;
            }
        return 0;
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
    cout<<"**********************************\n";
    cout<<"*Please input the number of people(N): ";
    cin>>n;
    system("cls");
    cout<<"**********************************\n";
    cout<<"*Please input the number of first people(S): ";
    cin>>s;
    system("cls");
    cout<<"**********************************\n";
    cout<<"*Please input the number that decide which one to wipe out(M): ";
    cin>>m;
    system("cls");
    if (check(n,s,m))//判断用户输入是否有误
    {cout<<"Result:\n";
    JosephusCircle(n,s,m);}//开始运行主程序
    else
        main();//此时用户输入有误，递归主函数让用户重新输入

}
