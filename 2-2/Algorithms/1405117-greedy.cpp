#include <bits/stdc++.h>
using namespace std;


class myclass
{
    public:
    int index;
    int strt;
    int end;
    bool taken;
};

bool myfunc(myclass ob1, myclass ob2)
{
    return ob1.end<ob2.end;
}
int main()
{
    int t;
    cin>>t;

    for(int cs=1; cs<=t; cs++)
    {
        int N, a, b;
        cin>>N;
        myclass ob[N+1];

        for(int i=0; i<N; i++)
        {
            ob[i].taken=false;
        }
        for(int i=0; i<N; i++)
        {
            cin>>a; ob[i].strt=a;
            cin>>b; ob[i].end=b;
            ob[i].index=i+1;
        }
        sort(ob, ob+N, myfunc);

        int cnt=0;
        int i=0, j=0;
        ob[i].taken=true;
        while(i<N)
        {
            if(ob[i].end<=ob[j+1].strt && ob[j+1].taken==false)
            {
                //cout<<ob[j].end<<" , "<<endl;
                ob[j+1].taken=true;
                cnt++;
                i=j+1;
            }
            else
            {
                j++;
            }
        }
        cout<<"Case "<<cs<<"#"<<endl;
        cout<<cnt<<endl;
        for(int i=0; i<N; i++)
        {
            if(ob[i].taken==true)
            {
                cout<<ob[i].index<<" ";
            }
        }
        cout<<endl;
        for(int i=0; i<N; i++)
        {
            if(ob[i].taken==true)
            {
                cout<<ob[i].strt<<" "<<ob[i].end<<" ";
            }
        }
        cout<<endl;

    }


}
