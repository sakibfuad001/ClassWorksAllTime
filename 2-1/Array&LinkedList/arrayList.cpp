#include<iostream>
#include<cstdio>
#include<stdlib.h>
using namespace std;

struct node{
    int id;
    int frequency;
};
int count=0, size=1;
struct node *p=(struct node*)malloc(size*sizeof(struct node));


void mall_oc(int size){
    int i;
    struct node *temp=NULL, *q=NULL;
    temp=p;
    q=(struct node*) malloc(size* sizeof(struct node));
    for(i=0; i<count; i++){
        q[i]=temp[i];
    }
    p=q;
    free(temp);
}

void Print()
{
    int i;
    for(i=0; i<count; i++){
        cout<<"<"<<p[i].id<<", "<<p[i].frequency<<"> ";
    }
    cout<<endl;
}
void Insert(int num){
    int i=0;
    for(i=0; i<count; i++){
        if(p[i].id==num){
            p[i].frequency=p[i].frequency+1;
            break;
        }
    }
    if(i==count){
        p[i].id=num;
        p[i].frequency=1;
        count++;
    }
    Print();
}
void Delete(int num){
    int i, j, flag=0;
    for(i=0; i<count; i++){
        if(p[i].id==num){
            if(p[i].frequency>1){
                p[i].frequency=p[i].frequency-1;
                break;
            }
            else{
                for(j=i; j<count-1; j++){
                    p[j].id=p[j+1].id;
                    p[j].frequency=p[j+1].frequency;
                }
                count--;
                flag=1;
                break;
            }
        }
    }
    if((i==count)&& (flag!=1)){ cout<<"Not Found"<<endl;}
    else{
        Print();
    }
}
void Find(int num){
    int i;
    for(i=0; i<count; i++){
        if(p[i].id==num){
            cout<<"Frequency of data with id = "<<p[i].id<<" is "<<p[i].frequency<<endl;
            break;
        }
    }
    if(i==count){
        cout<<"Frequency of data with id = "<< num <<" is 0"<<endl;
    }
}

void Reverse()
{
    int i, j;
    struct node *q=NULL, *temp=NULL;
    q=(struct node *) malloc(size * sizeof(struct node));

    temp=p;

    for(i=count-1, j=0; i>=0 ; i--, j++){
        q[j].id=p[i].id;
        q[j].frequency=p[i].frequency;
    }
    p=q;
    Print();
    free(temp);

}

int main()
{
    char ch;
    int id;
    while(cin>>ch){
        if(ch=='I'){
            cin>>id;
            if(count<size){
               // count++;
                Insert(id);

            }
            else{
                size=2*size;
                mall_oc(size);

                Insert(id);
                //count++;
            }
        }
        else if(ch=='D'){
            cin>>id;
            Delete(id);
            //count--;
            if(count==0){
                size=1;
                mall_oc(size);
            }
            if(size== 2*count){
                size=size/2;
                mall_oc(size);
            }
        }
        else if(ch=='F'){
            cin>>id;
            Find(id);
        }
        else if(ch=='R'){
            Reverse();
        }
        else if(ch=='T'){
            free(p);
            break;
        }
    }
    return 0;
}
