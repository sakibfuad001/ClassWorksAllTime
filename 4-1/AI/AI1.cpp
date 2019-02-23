#include <bits/stdc++.h>
using namespace std;
int N, counter;
int visited[20][20];

int output[20][20];

int row[]={0, 1 , -1};
int col[]={1, 0, -1};


bool DFS(int i, int j)
{
    // Mark all the vertices as not visited
    visited[i][j]=1;
    counter=counter++;
    if (counter == N*N) return true;
    for(int k=0; k<3; k++)
    {

        int x = i + row[k];
        int y = j + col[k];
       // cout<<x<<" "<<y<<endl;

        if(x>=0 && y>=0 && x<N && y<N)
        {
            if(visited[x][y]==0)
            {

                bool result= DFS(x, y);
                if(result==true) return true;
            }
        }
    }
    visited[i][j]=0;
    counter--;
    return false;
}


int main()
{
    cin>>N;

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            counter=0;
            memset(visited, 0, sizeof(visited));
            bool check = DFS(i, j);

            if(check== true)
            {
                output[i][j]= 1;
            }
            else
                output[i][j]=0;
        }
    }

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            cout<<output[i][j]<<" ";
        }
        cout<<endl;
    }
}
