#include<iostream>
#include"vector.h"
using namespace std;
template<typename T> void print(T e){    
    cout<<e<<' ';
}
int main(){
    Vector<int> v = Vector<int>(20, 10, 0);
    for(int i=0;i<v.size();i++)v[i]=i;
    v.unsort();
    v.insert(10);
    v.remove(v.find(3));
    v.traverse(print);
    cout<<endl;
    v.sort(0,v.size());
    v.traverse(print);
    return 0;
}