#include <iostream>
#include "stack.h"
#include "data.h"
#include <stdlib.h>

using namespace std;

int main()
{
    Stack S;
    int n, i;
    cin>>n;
    int *p=(int *)malloc(sizeof(int )*(n+1));

    Data num;

    for(i=1; i<=n; i++){
        cin>>num.x;
        int count=1;
        while(!S.isEmpty() && S.top().x>=num.x){
            S.pop();
            count++;
        }
        if(S.isEmpty()){
            p[i]=i;
        }
        else{
            if(count!=1){
                p[i]=i-count+1;
            }
            else{
                p[i]=1;
            }
        }
        S.push(num);
    }
    for(i=1; i<=n; i++){
        cout<<p[i]<<"  ";
    }
    free(p);
    return 0;
}
