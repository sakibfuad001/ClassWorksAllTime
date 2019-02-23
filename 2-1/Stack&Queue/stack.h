
#ifndef DS_STACK_H
#define DS_STACK_H

#include "data.h"
#include <iostream>
#include <new>

using namespace std;

class node{
public:
    Data b;
    node *next;
    friend class Stack;
};

class Stack
{
private:
    node *top1;
    int length;
public:
    Stack(){top1=NULL; length=0;}// constructor
    void push(Data a);  // pushes x into stack
    void pop();         // removes the top element of stack
    Data top();         // returns the top element of stack (without removing it)
    int size();         // returns the count of elements in the stack
    bool isEmpty();     // returns true if the stack is empty
    void print();       // prints the elements of the stack in console
};

void Stack::push(Data a){
    node* new_top = new node;
    new_top->b=a;
    new_top->next=top1;
    top1=new_top;
    length++;
}
void Stack::pop(){
    if(!isEmpty()){
        node *temp=top1;
        top1=top1->next;
        delete temp;
        length--;
    }

}
Data Stack::top(){
    if(!isEmpty()){
        return top1->b;
    }
}
int Stack::size(){
    return length;
}
bool Stack::isEmpty(){
    if(length==0){
        return true;
    }
    else{
        return false;
    }
}
void Stack::print(){
    node *temp=top1;
    while(temp!=NULL){
        cout<< temp -> b.x <<"  ";
        temp=temp->next;
    }
}

#endif
