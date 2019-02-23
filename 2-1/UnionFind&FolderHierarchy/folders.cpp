#include<iostream>
#include<queue>
#include<algorithm>
#include <stack>
#include <cstdio>
using namespace std;


class Folder
{
public:
    int n;
    int **ara;
    int *visited;
    int *start;
    int *endt;
    int *root;
    int cnt;

    Folder(int x)
    {
        n=x;
        visited= new int[x+1];
        start=new int[x+1];
        endt=new int[x+1];
        root=new int [x+1];
        for(int j=1; j<=n; j++)
        {
            visited[j]=0;
            start[j]=0;
            endt[j]=0;
            root[j]=1;
        }
        ara = new int* [x+1];
        for(int i=1; i<=n; i++)
        {
            ara[i]=new int[x+1];

            for(int j=1; j<=x; j++)
            {
                ara[i][j]=0;
            }
        }

    }
    void dfs(int u)
    {
        visited[u]=1;
        start[u]=++cnt;
        for(int i=1; i<=n; i++)
        {
            if(visited[i]==0 && ara[u][i]==1)
            {
                dfs(i);
            }
        }
        endt[u]=++cnt;
       // cout<<u<<"    "<<cnt<<endl;
    }

    bool check(int u, int v)
    {
        for(int i=1; i<=n; i++)
        {   //cnt=0;
            if(root[i]==1)
            {
                cnt=0;
                dfs(i);
                if(start[u]<start[v] && endt[u]>endt[v])
                {

                    return true;
                }

            }
        }
        return false;
    }
    ~Folder()
    {
        for (int i=1; i<=n; i++)
        {
            delete []ara[i];
        }
        delete []ara;
        delete []visited;
        delete []root;
    }
};

int main()
{
    int x, node1, node2, u, v;
    cin>>x;
    Folder ob(x);

    for(int i=1; i<x; i++)
    {
        cin>>node1>>node2;
        ob.ara[node1][node2]=1;
        ob.root[node2]=0;

    }

    while( scanf("%d %d", &u, &v) )
    {
        if(ob.check(u, v))
        {
            cout<<"YES"<<endl;
        }
        else
        {
            cout<<"NO"<<endl;
        }
        for(int i=0;i<=x;i++)
        {
            ob.endt[i]=0;
            ob.start[i]=0;
            ob.visited[i]=0;


        }

    }
    return 0;
}


