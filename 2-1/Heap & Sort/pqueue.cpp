#include <iostream>
#include <cstdio>
using namespace std;

#define min_infinity -1000000;

struct Data
{
    int key;
};
struct Data ara[10000];
class Priority_queue
{
public:
    int heapSize;



    void ChangeKey(int i, int key2)
    {
        //cout<<"change key in "<<key2<<endl;
        int parent, temp;
        if(ara[i].key>key2)
        {
            cout<<"This key is less than the previous key";
        }
        else
        {
            ara[i].key=key2;

            while(i>0)
            {
                parent = (i-1)/2;
                if(ara[i].key>ara[parent].key)
                {
                    temp=ara[i].key;
                    ara[i].key=ara[parent].key;
                    ara[parent].key=temp;
                    //cout<<"Dhukce3"<<endl;
                }
                i=parent;
                //cout<<"new i:"<<i<<endl;
            }
        }
       // cout<<"change key out "<<key2<<endl;
    }
    int FindMax()
    {
        //MaxHeapify(0);
        return ara[0].key;
    }

    void MaxHeapify(int index)
    {
        int left_child, right_child, maximum, temp;
        left_child=(2*index)+1;
        right_child=(2*index)+2;
        if(left_child<heapSize && ara[index].key<ara[left_child].key)
        {
            maximum=left_child;
        }
        else
        {
            maximum=index;
        }
        if(right_child<heapSize && ara[maximum].key<ara[right_child].key)
        {
            maximum=right_child;
        }

        if(maximum!=index)
        {
            temp=ara[index].key;
            ara[index].key=ara[maximum].key;
            ara[maximum].key=temp;
            MaxHeapify(maximum);
        }
        return;
    }


    void ExtractMax()
    {
        if(heapSize<1)
        {
            cout<<"Underflow"<<endl;
        }
        else
        {
            int max=ara[0].key;
            ara[0].key=ara[heapSize-1].key;
            heapSize=heapSize-1;
            MaxHeapify(0);
            cout<<max<<endl;
        }

    }

    void Insert(int key2)
    {
       // cout<<"in "<<key2<<endl;
        ara[heapSize].key=min_infinity;
        heapSize=heapSize+1;
       // cout<<"heapsize:"<<heapSize<<endl;
        ChangeKey(heapSize-1, key2);
       // cout<<"out"<<key2<<endl;
      // MaxHeapify(0);
    }

    void Delete(int i)
    {
        if(i<heapSize)
        {
            int temp=ara[i].key;
            ara[i].key=ara[heapSize-1].key;
            ara[heapSize-1].key=temp;
            heapSize=heapSize-1;
            MaxHeapify(0);
        }

    }

    void Print()
    {
        int i=0, cnt=1;;
        if(heapSize==0)
        {
            cout<<"NO element!!!"<<endl;
        }
        else
        {
            cout<<ara[i].key<<" ";
            while(cnt<heapSize)
            {
                cout<<ara[2*i+1].key<<" ";
                cnt++;
                if(cnt<heapSize)
                {
                    cout<<ara[2*i+2].key<<" ";
                    cnt++;
                }
                i++;
            }
            cout<<endl;
        }
    }
};

int main()
{
    Priority_queue qq;
    qq.heapSize=0;
    char ch;
    while(scanf("%c", &ch)==1)
    {
        if(ch=='I')
        {
            int key;
            cin>>key;
            qq.Insert(key);
        }
        else if(ch=='D')
        {
            int index;
            cin>>index;
            qq.Delete(index);
        }
        else if(ch=='F')
        {
            cout<<qq.FindMax()<<endl;
        }
        else if(ch=='E')
        {
            qq.ExtractMax();
        }
        else if(ch=='P')
        {
            qq.Print();
        }
        else if(ch=='C')
        {
            int i, key;
            cin>>i>>key;
            qq.ChangeKey(i,key);
        }
    }
}
