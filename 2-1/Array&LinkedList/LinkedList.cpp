#include<iostream>
#include<conio.h>
#include<stdlib.h>
using namespace std;

struct node{
    int id;
    int frequency;
    struct node* next;
};
struct node *head=NULL;

int count = 0;


void print_node(struct node* temp){
    cout<<"<"<<temp->id<<", "<<temp->frequency<<"> ";
}
void Print(){
    struct node*s=head;
    while(s->next!=NULL){
        cout<<"<"<<s->id<<", "<<s->frequency<<"> ";
        print_node(s);
        s=s->next;
    }
    cout<<endl;
}
void addbegin(int num){
    struct node *temp;
    temp=(struct node *)malloc(sizeof(struct node));
    temp->id=num;
    temp->frequency=1;
    head=temp;
    temp=head;
    Print();

}

void Insert(int num){
    struct node *temp, *p;
    p=(struct node *)malloc(sizeof(struct node));
    p->id=num;
    temp=head;
    while(temp!=NULL){
        if(temp->id==num){
            temp->frequency++;
            free(p);
            break;
        }
        temp=temp->next;
    }
    if(temp==NULL){
        p->frequency=1;
        temp=p;
        p->next=NULL;
    }
    Print();
}

void Delete(int num){
    struct node* temp, *right, *temp2;
    temp= head;

    while(temp!=NULL){
        if(temp->id==num){
            temp->frequency--;
            if(temp->frequency==0){
                right=temp->next;
                temp=temp->next;

                while(temp2!=NULL){
                    if(temp2==right){

                    }
                }
            }
        }
        temp=temp->next;
    }
    Print();
}
void Find(int num){
    struct node *s=head;
    while(s!=NULL){
        if(s->id==num){
            cout<<"Frequency of data with id = "<<s->id<<" is "<<s->frequency<<endl;
            break;
        }
    }
    if(s==NULL){
        cout<<"Frequency of data with id = "<<s->id<<"is 0"<<endl;
    }
}

void Reverse(){

}

int main()
{
    int id;
    char ch;
    while(cin>>ch){
        if(ch=='I'){
            cin>>id;
            if(head==NULL){
                addbegin(id);
            }
            else{
                Insert(id);
            }
        }
        else if(ch=='D'){
            cin>>id;
            Delete(id);
        }
        else if(ch=='F'){
            cin>>id;
            Find(id);
        }
        else if(ch=='R'){
            Reverse();
        }
        else if(ch=='T'){
            exit(1);
        }
    }
    getch();
    return 0;
}










