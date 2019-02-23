#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Graph
{
public:
    int n, m;
    int *check;
    int **edge;
    Graph(int x, int y)
    {
        n=x;
        m=y;
        check=new int[x+1];
        for(int i=1; i<=n; i++)
        {
            check[i]=-1;
        }

        edge=new int*[x+1];
        for(int i=0; i<=x+1; i++)
        {
            edge[i]=new int [x+1];
            for(int j=1; j<=x+1; j++)
            {
                edge[i][j]=0;
            }
        }

    }

    bool bfs(int source)
    {
        int flag=0;
        queue<int>qq;
        qq.push(source);
        check[source]=0;

        while(!qq.empty())
        {
            int node=qq.front();
            qq.pop();
            for(int i=1; i<=n; i++)
            {
                if(check[i]==-1 && edge[node][i]==1)
                {
                    if(check[node]==0)
                    {
                        check[i]=1;
                    }
                    else
                    {
                        check[i]=0;
                    }
                    qq.push(i);

                }
                else if(edge[node][i]==1)
                {
                    if(check[node]==check[i])
                    {
                        flag=1;
                        break;
                    }
                }
            }
            if(flag==1)
            {
                break;
            }
        }
        if(flag==1)
        {
            return false;
        }
        else
        {
            return true;
        }

    }

    int bicolorCheck()
    {
        for(int i=1; i<=n; i++)
        {
            if(check[i]==-1)
            {
                if(!bfs(i))
                {
                    return 1;
                }
            }
        }
        return 2;
    }

    ~Graph()
    {
        for(int i=0; i<=n+1; i++)
        {
            delete  []edge[i];
        }
        delete []edge;
        delete []check;
    }


};

int main()
{
    int n, m, node1, node2;
    cin>>n>>m;
    Graph ob(n, m);

    for(int i=1; i<=m; i++)
    {
        cin>>node1>>node2;
        ob.edge[node1][node2]=1;
        ob.edge[node2][node1]=1;
    }

    int result=ob.bicolorCheck();

    if(result==1)
    {
        cout<<"NO";
    }
    else
    {
        cout<<"YES";
    }

    return 0;

}



