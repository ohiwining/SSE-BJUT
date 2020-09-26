#include <cstdio>
#include <iostream>
using namespace std;
#define NUMS 8
#define inf 65535

typedef struct
{
    int edges[8][8]={
            {000,200,inf,inf,inf,250,inf,500},
            {200,000,400,inf,180,inf,inf,inf},
            {inf,400,inf,150,inf,inf,380,375},
            {inf,inf,150,000,inf,350,inf,inf},
            {inf,180,inf,inf,000,200,inf,inf},
            {250,inf,inf,350,200,000,inf,inf},
            {inf,inf,380,inf,inf,inf,000,300},
            {500,inf,375,inf,inf,inf,300,000},
    };
    int n=8,e=64;
}Graph;

void Dispath(int A[][NUMS],int path[][NUMS],int n);

void Floyd(Graph G)
{
    int A[NUMS][NUMS],path[NUMS][NUMS];
    int i,j,k;
    for (i=0;i<G.n;i++)
    {
        for (j=0;j<G.n;j++)
        {
            A[i][j]=G.edges[i][j];
            path[i][j]=-1;
        }
    }
    for (k=0;k<G.n;k++)
    {
        for (i=0;i<G.n;i++)
        {
            for (j=0;j<G.n;j++)
            {
                if (A[i][j]>A[i][k]+A[k][j])
                {
                    A[i][j]=A[i][k]+A[k][j];
                    path[i][j]=k;
                }
            }
        }
    }
    Dispath(A,path,G.n);
}

void Ppath(int path[][NUMS],int i,int j)
{
    int k;
    k=path[i][j];
    if (k==-1)
    {
        return;
    }
    Ppath(path,i,k);
    cout<<k<<",";
    Ppath(path,k,j);
}

void Dispath(int A[][NUMS],int path[][NUMS],int n)
{
    int i,j;
    for (i=0;i<n;i++)
    {
        for (j=0;j<n;j++)
        {
            if (A[i][j]==inf)
            {
                if (i!=j)
                {
                    cout<<"from"<<i <<"to "<<j<<" don't have path\n";
                }
            }
            else
            {
                cout<<"from"<<i<<" to "<<j<<" => shortest path : "<<A[i][j]<<" passed :";
                cout<<i <<",";
                Ppath(path,i,j);
                cout<<j <<endl;
            }
        }
    }
}

int main()
{
    Graph G;
    Floyd(G);
    return 0;
}
