#include <iostream>
#include <stack>
using namespace std;
typedef struct Node {//定义节点构造
    char data;
    Node *l = nullptr, *r = nullptr;//左孩子和右孩子
} Tree;
void Create(Tree *a[]) {//创建树的函数，通过手动连接节点的方式构造了题目中的树
    int i = 0;
    for (char ch = 'A'; ch <= 'N'; ++ch) {
        a[i] = new Node;//给节点中存入大写字母
        a[i]->data = ch;
        i++;
    }
    a[0]->l = a[1];//连接节点
    a[0]->r = a[2];
    a[1]->l = a[3];
    a[1]->r = a[4];
    a[2]->l = a[5];
    a[2]->r = a[6];
    a[4]->l = a[7];
    a[6]->r = a[8];
    a[7]->l = a[9];
    a[7]->r = a[10];
    a[10]->l = a[11];
    a[10]->r = a[12];
    a[12]->r = a[13];
}

void Traverse(Tree *a) {//先序遍历，使用递归
    if (a == nullptr) return;
    else {
        cout << a->data;
        Traverse(a->l);
        Traverse(a->r);
    }
}

void FindOutput(Tree *a) {//查找H节点的左右孩子函数
    if (a == nullptr) return;
    else {
        if (a->data != 'H') {
            FindOutput(a->l);//通过递归方式找到节点
            FindOutput(a->r);
        } else {
            cout << "Left child of H: " << a->l->data << endl;
            cout << "Right child of H: " << a->r->data << endl;
        }
    }
}

int GetHeight(Tree *a) {//计算树的高度，使用递归方式
    int height = 0;
    if (a == nullptr) return height;
    else {
        height = 1 + (GetHeight(a->l) > GetHeight(a->r) ? GetHeight(a->l) : GetHeight(a->r));
        return height;
    }
}

void DeleteTree(Tree *a) {//删除树中所有节点并释放内存
    if (a == nullptr) return;
    else {
        DeleteTree(a->l);
        DeleteTree(a->r);
        delete a;
    }
}

void Recursion(Tree *a) {//中序遍历，使用递归方式
    if (a == nullptr) return;
    else {
        Recursion(a->l);
        cout << a->data;
        Recursion(a->r);
    }
}

void NonRecursion(Tree *p) {//中序遍历，使用非递归方式
    stack <Tree *> st;//将树和栈结合来实现非递归遍历
    while(!st.empty() || p!= nullptr)
    {
        while(p!= nullptr)
        {
            st.push(p);
            p=p->l;
        }
        if(!st.empty())
        {
            p=st.top();
            st.pop();
            cout<<p->data;
            p=p->r;
        }
    }
}
int how_many_nodes(Tree *b)//统计树中有多少个节点
{
    if(!b)return 0;
    else
        return how_many_nodes(b->l)+how_many_nodes(b->r)+1;//使用递归方式
}
int main() {
    Tree *a[14];
    Create(a);//建立题目所述的树
    cout << "Output all nodes:" << endl;
    Traverse(a[0]);//先序输出所有节点
    cout << endl;
    FindOutput(a[0]);//查找H节点的左右孩子
    cout << "Height of tree:" << GetHeight(a[0]) << endl;//获取高度
    cout << "Traverse using recursion:" << endl;//递归和非递归来实现遍历
    Recursion(a[0]);
    cout <<endl<< "Traverse using non-recursion:" << endl;
    NonRecursion(a[0]);
    cout <<endl<<"The number of nodes: "<<how_many_nodes(a[0])<<endl;//统计节点个数
    DeleteTree(a[0]);//删除树，释放内存
    cout << "Delete tree successfully." << endl;
}