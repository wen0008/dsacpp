#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include"list.h"
using namespace std;
int main(){
    List<int> L;
    ListNodePosi(int) first = L.insertAsFirst(1);
    ListNodePosi(int) p = first;
    for(int i = 0; i != 7; ++i){
        L.insertAfter(p, i*13%8);
        p = p->succ;
    }
    for (ListNodePosi(int) p = L.first(); p != L.last()->succ; p = p->succ)
    {
        cout<<p->data<<' ';
    }
    cout<<endl;
    L.sort();
    for (ListNodePosi(int) p = L.first(); p != L.last()->succ; p = p->succ)
    {
        cout<<p->data<<' ';
    }
    
    return 0;
}