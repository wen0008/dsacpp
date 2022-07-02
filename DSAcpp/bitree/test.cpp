#include<iostream>
#include"bintree.h"
using namespace std;
template<typename T> void print(T e){    
    cout<<e<<' ';
}
int main(){
    BinTree<int> t;
    BinNodePosi(int) root = t.insertAsRoot(0);//                0
    BinNodePosi(int) l = t.insertAsLC(root, 1);//           1       2
    BinNodePosi(int) r = t.insertAsRC(root, 2);//         3   4   5   6
    t.insertAsLC(l, 3); t.insertAsRC(l, 4); t.insertAsLC(r, 5); t.insertAsRC(r, 6);
    t.traversePre(print); cout<<"  size="<<t.size()<<endl;
    BinTree<int> *t1 = t.secede(r);
    t.traversePre(print); cout<<"  size="<<t.size()<<endl;
    t1->traversePre(print); cout<<"  size="<<t.size()<<endl;
    return 0;
}