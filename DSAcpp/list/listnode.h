typedef int Rank;
#define ListNodePosi(T)  ListNode<T>*   //节点位置

template <typename T> struct ListNode   //列表节点模板类（双向链表）
{
    T data;     //数值
    ListNodePosi(T) pred;   //前驱
    ListNodePosi(T) succ;   //后继
    ListNode(){}    //针对header和trailer的构造
    ListNode(T e, ListNodePosi(T) p=nullptr, ListNodePosi(T) s=nullptr): data(e), pred(p), succ(s) {}   //默认构造器
    //操作接口
    ListNodePosi(T) insertAsPred(T const& e);   //前插
    ListNodePosi(T) insertAsSucc(T const& e);   //后插

};

template <typename T> ListNodePosi(T) ListNode<T>::insertAsPred(T const& e){    //o(1)
    ListNodePosi(T) x = new ListNode(e, pred, this);    //创建
    pred->succ = x; pred = x; 
    return x;
} 
template <typename T> ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e){    //o(1)
    ListNodePosi(T) x = new ListNode(e, this, succ);    //创建
    succ->pred = x; succ = x; 
    return x;
} 