#include <iostream>
using namespace std;

int ara[10000];

void Swap(int a, int b)
{
    int temp=ara[a];
    ara[a]=ara[b];
    ara[b]=temp;
}

int median(int first, int last)
{
    int mid=(first+last)/2;
    if(ara[first]>ara[last])
    {
        Swap(first, last);
    }
    if(ara[mid]<ara[first])
    {
        Swap(mid, first);
    }
    if(ara[mid]>ara[last])
    {
        Swap(mid, last);
    }

    return mid;
}

int part(int first, int last)
{
    int mid=median(first, last);
    int pivot=ara[mid];
    int i=first;
    int j=last;
    while(i<=j)
    {
        while(ara[i]<pivot)
        {
            i++;
        }
        while(ara[j]>pivot)
        {
            j--;
        }
        if(i<=j)
        {
            Swap(i, j);
            i++;
            j--;
        }
    }

    return i;
}

void quickSort(int first, int last)
{
   int q=part(first,last);
   if(first<q-1)
   {
       quickSort(first,q-1);
   }
   if(q<last)
   {
       quickSort(q,last);
   }
}
int main()
{
    int n;
    cin>>n;
    for(int i=0; i<n;i++)
    {
        cin>>ara[i];
    }
    quickSort(0, n-1);

    for(int i=0; i<n; i++)
    {
        cout<<ara[i]<<" ";
    }

    return 0;
}
