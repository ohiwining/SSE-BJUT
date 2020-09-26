#include <iostream>
#include <cstring>
using namespace std;
typedef struct Node{//定义节点
    char data;//存入字符
    int parent=0,l=0,r=0;
    int Weight;//权重
}TNode,*HuffmanTree;
int Select(HuffmanTree T,int k){//选择函数，用与选择树中权重最小的节点
    int i=0,min_Weight=0,min=0;
    while(T[i].parent!=0)
        i++;
    min_Weight=T[i].Weight;
    min=i;
    for(; i < k; i++){
        if(T[i].Weight<min_Weight&&T[i].parent==0){
            min_Weight=T[i].Weight;
            min=i;
        }
    }
    T[min].parent=1;
    return min;
}
void CreateHuffmanTree(HuffmanTree &T,const int *wet,int n,string string1){//建立哈夫曼树
    int i=0;
    int m=2*n-1;
    T=new TNode;
    for(i=0;i<n;i++)
    {
        T[i].data=string1[i];
        T[i].l=0;//初始化，双亲左右孩子都为0，字符为用户输入的字符
        T[i].parent=0;
        T[i].r=0;
        T[i].Weight=wet[i];
    }
    for(i=n;i<m;i++){
        T[i].l=0;//非叶子节点的初始化
        T[i].r=0;
        T[i].parent=0;
        T[i].Weight=0;
    }
    int min1=0,min2=0;
    for(i=n;i<m;i++){
        min1=Select(T,i);//选择权重最小的两个节点并进行哈夫曼树的建立
        min2=Select(T,i);
        T[min1].parent=i;
        T[min2].parent=i;
        T[i].l=min1;
        T[i].r=min2;
        T[i].Weight=T[min1].Weight+T[min2].Weight;
    }
}
void HuffmanCoding(HuffmanTree T,char ** &HC,int n){//哈夫曼编码函数，将字符转化为二进制编码
    HC=new char* [n+1];//分配内存
    char *cd;
    cd=new char [n];
    cd[n-1]='\0';
    int start,c,f;
    for(int i=0;i<n;i++)
    {
        c=i;
        f=T[i].parent;
        start=n-1;
        while(f!=0)
        {
            --start;
            if(T[f].l==c)
                cd[start]='0';
            else
                cd[start]='1';
            c=f;
            f=T[f].parent;
        }
        HC[i]=new char [n-start];
        strcpy(HC[i],cd+start);//转换完成后将字符串存入字符串数组
    }
    delete cd;//释放内存
}
void Encoding(HuffmanTree T, char ** &HC,int n)//将长字符串转化为一串长二进制编码
{
    string input;
    cout<<"Please input a string:"<<endl;
    cin>>input;
    int t=0;
    int i=0;
    while(input[t]!='\0'){
        while(input[t]!=T[i].data&&i<=n){
            i++;
        }
        if(input[t]==T[i].data){
            cout<<HC[i];
        }
        t++;
        i=1;
    }
    cout<<endl;
}
void Decoding(HuffmanTree T,int n)//解码函数，哈夫曼编码转化为字符串
{
    string input;
    cout<<"Please input a Huffman code:"<<endl;
    cin>>input;
    int i=0;
    while(input[i]!='\0')
    {
        Node p=T[2*n-1];
        while(p.l||p.r)
        {
            if(input[i]=='0'&&p.l)
                p=T[p.l];
            if(input[i]=='1'&&p.r)
                p=T[p.r];
            i++;
        }
        cout<<p.data;
    }
    cout<<endl;
}
int main(){
    int letters=0;
    auto *weight=new int;
    string letter;
    cout<<"How many letters to encode?"<<endl;//输入不同字符的数量
    cin>>letters;
    cout<<"Please input these letters:"<<endl;//输入具体字符，（一次性输入完毕）
    cin>>letter;
    cout<<"Please input their weights:"<<endl;//分别输入权重
    for(int i=0;i<letters;i++){
        cin>>*(weight+i);
    }
    HuffmanTree T = nullptr;
    CreateHuffmanTree(T,weight,letters,letter);//创建哈夫曼树
    char **HC;
    HuffmanCoding(T,HC,letters);//创建哈夫曼编码
    for(int i=0;i<letters;i++)
    {
        cout<<letter[i]<<": "<<HC[i]<<endl;
    }
    Encoding(T,HC,letters);//将字符串转换为二进制编码
    Decoding(T,letters);//解码函数
    delete weight;
    return 0;
}