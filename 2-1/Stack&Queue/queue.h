#ifndef DS_QUEUE_H
#define DS_QUEUE_H

#include "stack.h"
#include "data.h"
#include <iostream>
#include <new>

using namespace std;

class Queue
{
    Stack stack1, stack2;

public:
    Queue(){};// constructor
    void enqueue(Data x);   // enqueues x
    void dequeue();         // removes the front element
    Data front();           // returns the element from the front (without removing it)
    int size();             // returns the count of elements in the queue
    bool isEmpty();         // returns true of the queue is empty
    void print();           // print the elements of the queue in console
};

void Queue::enqueue(Data x)
{
    stack1.push(x);
}
void Queue::dequeue()
{
    if((stack2.isEmpty())){
        while(!(stack1.isEmpty())){
            stack2.push(stack1.top());
            stack1.pop();
        }
        stack2.pop();
    }
    else{
        stack2.pop();
    }
}

Data Queue::front()
{
    if(stack2.isEmpty()){
        while(!stack1.isEmpty()){
            stack2.push(stack1.top());
            stack1.pop();
        }
        return stack2.top();
    }
    else{
        return stack2.top();
    }
}
int Queue::size()
{
    return (stack1.size()+stack2.size());
}

bool Queue::isEmpty()
{
    if(size()==0){
        return true;
    }
    else{
        return false;
    }
}

void Queue::print()
{
    Stack temp;
    if(!stack2.isEmpty()){
        stack2.print();
    }
    while(!stack2.isEmpty()){
        temp.push(stack2.top());
        stack2.pop();
    }
    while(!stack1.isEmpty()){
        stack2.push(stack1.top());
        stack1.pop();
    }
    stack2.print();
    while(!temp.isEmpty()){
        stack2.push(temp.top());
        temp.pop();
    }

    cout<<endl;
}

#endif
