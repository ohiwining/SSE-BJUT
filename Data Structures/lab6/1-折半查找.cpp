#include <iostream>
#include <random>
using namespace std;
int main()
{
    int n;//用户决定数组长度
    cout<<"Please input the number of nodes: "<<endl;
    cin>>n;

    default_random_engine rng;//自动生成数组中的数
    unsigned int a[n],temp;
    a[0]=rng()%30;
    for (int i = 1; i < n; ++i) {
        temp=rng()%30+1;
        a[i]=a[i-1]+temp;//这条语句保证数组中的数是递增的  而且不会出现重复的
    }
    cout<<"Number sequence: "<<endl;//输出数组中的所有数字
    for (int i = 0; i < n; ++i) {
        cout<<a[i]<<" ";
    }

    unsigned int search,low=0,high=n-1,sign;//折半查找算法
    cout<<endl<<"Please input a number to search:"<<endl;//输入要查找的数字
    cin>>search;
    while(low+1<high)//折半查找判定条件
    {
        sign=(low+high)/2;//计算下标
        if(search==a[sign])
        {
            cout<<"Number found! Number: a["<<sign<<"] = "<<a[sign]<<endl;//找到结果时输出相关信息
            return 0;
        }
        else if (search<a[sign])//如果此次循环没有找到就更改搜索范围
            high=sign;
        else if (search>a[sign])
            low=sign;
    }
    cout<<"Number not found! "<<endl;//此时函数仍然没有结束说明数字没有找到
    return 0;
}