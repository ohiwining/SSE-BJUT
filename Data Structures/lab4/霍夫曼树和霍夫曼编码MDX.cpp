#include <iostream>
#include<string.h>
using namespace std;
struct HuffmanNode{
    float f;
    char ch;
    int parent, Lchild,Rchild;
};
class Huffman{
private :
    int S1,S2;
    int n;
    char *cd;
    char **HC;
    HuffmanNode *Node;
public :
    Huffman();
    void CreatHuffMan();
    void Select(int);
    void Code();
    void PrintCode(char*);
    void Interpret(char*);
};
Huffman::Huffman(){
    Node=NULL;
    n=0;
    S1=1;
    S2=1;
}
void Huffman::CreatHuffMan(){
    int m;
    cout<<"Please enter how many char you want to code: ";
    cin>>n;
    m=2*n-1;
    Node=new HuffmanNode[m+1];
    for(int i=1;i<=m;i++){
        Node[i].Lchild=0;
        Node[i].Rchild=0;
        Node[i].parent=0;
    }
    cout<<"Please enter some char and its frequency(such as A 0.1): ";
    for(int i=1;i<=n;i++){
        cin>>Node[i].ch;
        cin>>Node[i].f;
    }
    for(int i=n+1;i<=m;i++){
        Select(i-1);
        Node[S1].parent=i;
        Node[S2].parent=i;
        //cout<<Node[S1].parent<<' '<<Node[S2].parent<<endl;
        Node[i].Lchild=S1;
        Node[i].Rchild=S2;
        Node[i].f=Node[S1].f+Node[S2].f;
    }
    for(int i=1;i<=m;i++){
        cout<<Node[i].Lchild<<' '<<Node[i].Rchild<<endl;
    }

}
//&&Node[i].parent==0
void Huffman::Select(int j){
    int i;
    S1=1;S2=1;
    while(S1<=j&&Node[S1].parent!=0){
        S1++;
    }
    i=S1;
    S2=S1;
    for(;i<=j;i++){
        if(((Node[S1].f>=Node[i].f)||(Node[S2].f>=Node[i].f))&&Node[i].parent==0){
            if(Node[S1].f<=Node[S2].f){
                S2=S1;
                S1=i;
            }
            else{
                S1=S2;
                S2=i;
            }
        }
    }
    if(S1==S2){
        S2++;
        for(int i=S1+1;i<=j;i++){
            if(Node[i].parent!=0){
                S2++;
            }
            if(Node[S2].f>=Node[i].f&&Node[i].parent==0){
                S2=i;
            }
        }
    }
}
void Huffman::Code(){
    HC=new char*[n+1];
    cd=new char[n];
    cd[n-1]='\0';
    int start,c,f;
    for(int i=1;i<=n;i++){
        start=n-1;
        c=i;
        f=Node[i].parent;
        while(f!=0){
            start--;
            if(Node[f].Lchild==c) cd[start]='0';
            else cd[start]='1';
            c=f;
            f=Node[f].parent;
        }
        HC[i]=new char[n-start];
        strcpy(HC[i], &cd[start]);
    }
    delete cd;
}
void Huffman::PrintCode(char *T){
    int t=0;
    int i=1;
    while(T[t]!='\0'){
        while(T[t]!=Node[i].ch&&i<=n){
            i++;
        }
        if(T[t]==Node[i].ch){
            cout<<HC[i];
        }
        t++;
        i=1;
    }
    cout<<endl;
}
void Huffman::Interpret(char *T){
    int i=0;
    while(T[i]!='\0')
    {
        HuffmanNode p=Node[2*n-1];
        while(p.Lchild!=0||p.Rchild!=0){
            if(T[i]=='0'&&p.Lchild!=0){
                p=Node[p.Lchild];
            }
            if(T[i]=='1'&&p.Rchild!=0){
                p=Node[p.Rchild];
            }
            i++;
        }
        cout<<p.ch;
    }
    cout<<endl;
}
int main(){
    Huffman Tree;
    char T[100];
    char t[100];
    Tree.CreatHuffMan();
    Tree.Code();
    cout<<"Please enter a long string use the letter you enter:"<<endl;
    cin>>T;
    Tree.PrintCode(T);
    cout<<"Please enter a string number:"<<endl;
    cin>>t;
    Tree.Interpret(t);
}