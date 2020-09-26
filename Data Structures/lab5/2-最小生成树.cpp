#include <iostream>
#include <algorithm>
const int MAX=30
const int INF=10000
using namespace std;
int n,m;//定义点的个数，边的个数
int parent[MAX];//定义双亲点，防止闭环
typedef struct line//定义边
{
    int u,v,w;//出发点，终点，权值
}Edge;
Edge E[MAX];//创建全局变量
int Map[MAX][MAX]={0};
bool compare(Edge x1,Edge x2)
{
    return x1.w<x2.w;//比较两个权值的大小
}
int Find_parent(int x)//寻找双亲，防止闭环
{
    if(parent[x]==x)//如果双亲就是自己则返回自己
        return x;
    parent[x]=Find_parent(parent[x]);//如果不是自己就一直寻找
    return parent[x];//找到则返回最终的双亲
}
void Kruskal()
{
    int lines=0;//所形成最小连通书的边数
    for(int i=1;i<=n;i++)
        parent[i]=i;
    sort(E,E+m,compare);//为权值的大小排序
    for(int i=0;i<m;i++)
    {
        if(Find_parent(E[i].u)!=Find_parent(E[i].v))//如果一条边的始末不同，即未形成环
        {
            cout<<"From "<<E[i].u<<" to "<<E[i].v<<", Length: "<<E[i].w<<endl;//输出这条边的信息
            lines++;
            parent[E[i].v]=E[i].u;//标记为环
        }
        if(lines==n-1)//此时边的条数是顶点数减一，已经形成连通树
        {
            return;
        }
    }
}
void Prim(int u)//最小生成树起点
{
    int low_cost[MAX], dis[MAX];
    for(int i = 0; i < n; i++)//初始化两个数组
    {
        low_cost[i] = Map[u][i];
        dis[i] = u;
    }
    dis[u] = -1;//设置成-1表示已经加入生成树
    for(int i = 0; i < n-1; i++)
    {
        int minn = INF;
        int v = -1;
        for(int j = 0; j < n; j++)//在low_cost数组中寻找未加入dis的最小值
        {
            if(dis[j] != -1 && low_cost[j] < minn)
            {
                v = j;
                minn = low_cost[j];
            }
        }
        if(v != -1)//表示未找到最小的边,v为当前距离dis最短的点
        {
            cout<<"From "<<dis[v]<<" to "<<v<<", Length: "<<low_cost[v]<<endl;//输出路径
            dis[v] = -1;
            for(int j = 0; j < n; j++)//更新最短边
            {
                if(dis[j] != -1 && low_cost[j] > Map[v][j])
                {
                    low_cost[j] = Map[v][j];
                    dis[j] = v;
                }
            }
        }
    }
}
int main()
{
    int u,v,w;
    cout<<"Please input number of points: ";
    cin>>n;
    cout<<"Please input number of lines: ";
    cin>>m;
    cout<<"Please input start and end and length of each line:"<<endl;
    for(int i=0;i<m;i++)
    {
        cin>>u>>v>>w;//输入数据，此处将邻接表和邻接矩阵都初始化了
        E[i].u=u;
        E[i].v=v;
        E[i].w=w;
        Map[u][v] = Map[v][u] = w;
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i == j)Map[i][j] = 0;//初始化邻接矩阵中未被输入的地方
            else if(!Map[i][j])Map[i][j] = INF;
        }
    }
    cout<<"Result(Kruskal): "<<endl;
    Kruskal();
    cout<<endl;
    cout<<"Result(Prim): "<<endl;
    Prim(0);//任意输入一个起点即可
}
