#include <iostream>
#include <cstdio>
using namespace std;

class graph
{
public:
    int address;

};


int Count(int v, graph *ptr)
{
    int count=0;
    while(ptr[v].address!=-1)
    {
        v=ptr[v].address;
        count++;
    }
    return count;
}


int Find(int a, graph *ptr)
{
    int temp_int=a;
    while(ptr[a].address!=-1)
    {
        a=ptr[a].address;
    }

    while(ptr[temp_int].address!=-1){
        int temp=ptr[temp_int].address;
        ptr[temp_int].address=a;
        temp_int=temp;
    }

    return a;
}

bool Union(int v, int e, graph *ptr, int n)
{
    int a=Find(v, ptr);
    int b=Find(e, ptr);

    if(a==b)
    {
        return false;
    }
    else
    {
        if(Count(v, ptr)>=Count(e, ptr))
        {
            ptr[b].address=a;
        }
        else
        {
            ptr[a].address=b;
        }

        return true;
    }
}


int main()
{
    graph *ptr;
    long long int n;
    cin>>n;
    ptr=new graph[n];

    for(int i=1; i<=n; i++)
    {
        ptr[i].address=-1;
    }

    int v, e;

    while(EOF!=scanf("%d%d", &v, &e))
    {
        if(Union(v,e, ptr, n))
        {
            n=n-1;
            cout<<n<<endl;
        }
        else
        {
            cout<<n<<" CYCLE FORMED!"<<endl;
        }
    }


    delete []ptr;

    return 0;


}

