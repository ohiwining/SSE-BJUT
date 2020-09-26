/*本程序用来测试图的深度优先遍历(包括递归与非递归)和广度优先遍历
 * 使用了邻接表的表示方法
 * 用户可任意创建图*/
#include <iostream>
#include <stack>
#include <queue>
using namespace std;
const int MAX=10;
bool visited[MAX]= {false};
typedef struct aNode//定义表节点
{
    int target=-1;//表示目标点
    struct aNode *next= nullptr;//指向下一表节点
}Node;
typedef struct HNode//头节点
{
    int no=-1;//表示这个节点代表的编号
    Node *point= nullptr;//指向表节点
}HNode;
typedef struct Graph//邻接表
{
    HNode points[MAX];//头节点数组
    int num_points=0;//点的个数
    int num_lines=0;//边的个数
}Graph;
void init_graph(Graph &graph)
{
    int start,end;
    cout<<"Please input number of points: ";
    cin>>graph.num_points;
    cout<<"Please input number of lines: ";
    cin>>graph.num_lines;
    for (int i = 0; i < graph.num_points; ++i) {
        graph.points[i].no=i;
    }
    cout<<"Where is every line started and ended?"<<endl;
    for (int j = 0; j < graph.num_lines; ++j) {
        cin>>start>>end;
        if(graph.points[start].point== nullptr)
        {
            auto temp=new Node;
            temp->target=end;
            graph.points[start].point=temp;
        }
        else
        {
            Node *p= graph.points[start].point;
            while (p->next!= nullptr)
                p=p->next;
            auto temp=new Node;
            temp->target=end;
            p->next=temp;
        }
        if(graph.points[end].point== nullptr)
        {
            auto temp=new Node;
            temp->target=start;
            graph.points[end].point=temp;
        }
        else
        {
            Node *p= graph.points[end].point;
            while (p->next!= nullptr)
                p=p->next;
            auto temp=new Node;
            temp->target=start;
            p->next=temp;
        }
    }
}
void DFS(Node *p)
{
    if (visited[p->target])
        return;
    else
    {
        cout<<p->target;
        visited[p->target]=true;
        if (p->next!= nullptr)
            DFS(p->next);
    }
}
void DFSTraverseRecursion(Graph G)//使用递归的深度优先遍历
{
    for (bool & i : visited) {//重置visited为false
        i= false;
    }
    for (int j = 0; j < G.num_points; ++j)
    {
        if(!visited[j])
        {
            cout<<j;
            visited[j]=true;
            DFS(G.points[j].point);
        }
    }
}
void DFSTraverseNonRecursion(Graph G,int v=0)//使用非递归方式的深度优先遍历
{
    for (bool & i : visited) {//重置visit中元素为false
        i=false;
    }
    stack<int> s;//建立栈
    cout<<v;
    visited[v]= true;
    s.push(v);//进栈
    Node *p=nullptr;
    v=s.top();
    while(!s.empty())//当栈不空时进行遍历
    {
        for(p=G.points[v].point;p!= nullptr;p=p->next)
        {
            if(!visited[p->target])
            {
                cout<<p->target;
                visited[p->target]=true;
                s.push(p->target);
            }
            v=s.top();
        }
        s.pop();
    }
}
void BFSTraverse(Graph G,int v=0)//广度优先遍历
{
    for (bool & i : visited) {//重置visit中元素为false
        i=false;
    }
    queue<int> q;
    cout<<v;
    visited[v]= true;
    q.push(v);//进队
    Node *p= nullptr;
    while(!q.empty())//队不空时开始遍历
    {
        v=q.front();
        q.pop();
        for(p=G.points[v].point;p!= nullptr;p=p->next)
            if(!visited[p->target])
            {
                cout<<p->target;
                visited[p->target]=true;
                q.push(p->target);
            }
    }
}
int main()
{
    Graph graph;
    init_graph(graph);
    cout<<"DFS Traverse using Recursion: "<<endl;
    DFSTraverseRecursion(graph);
    cout<<endl<<"DFS Traverse using Non-Recursion: "<<endl;
    DFSTraverseNonRecursion(graph);
    cout<<endl<<"BFS Traverse: "<<endl;
    BFSTraverse(graph);
    system("pause");
}