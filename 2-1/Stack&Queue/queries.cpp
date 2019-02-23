#include <iostream>
#include "stack.h"
#include "queue.h"

using namespace std;

int main()
{
    Stack s;
    Queue q;
    char cmd;
    Data data;

    while (true)
    {
        cin >> cmd;
        if ('q' == cmd)
            break;
        if ('p' == cmd || 'e' == cmd)
            cin >> data.x;

        switch(cmd)
        {
        case 'p':
            s.push(data);
            break;
        case 'P':
            s.pop();
            break;
        case 't':
            if (!s.isEmpty())
                cout << "top of stack: " << s.top().x << endl;
            break;
        case 'e':
            q.enqueue(data);
            break;
        case 'd':
            q.dequeue();
            break;
        case 'f':
            if (!q.isEmpty())
                cout << "front of queue: " << q.front().x << endl;
            break;
        case 's':
            cout << "Stack size: " << s.size() << " Queue size: " << q.size() << endl;
            break;
        case 'i':
            cout << "Stack " << (s.isEmpty() ? "is empty" : "is not empty") << endl;
            cout << "Queue " << (q.isEmpty() ? "is empty" : "is not empty") << endl;
            break;
        }

        s.print();
        cout<<endl;
        q.print();
    }

    return 0;
}
