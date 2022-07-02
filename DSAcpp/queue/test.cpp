#include<iostream>
#include"queue.h"
using namespace std;
int main(){
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.dequeue();
    cout<<q.front();
    return 0;
}