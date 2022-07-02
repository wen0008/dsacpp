#include "binnode.h"
#include "D:\code\c++\cpp_single\DSAcpp\stack\stack.h"
#include "D:\code\c++\cpp_single\DSAcpp\queue\queue.h"
#define stature(p) ((p)? (p)->height : -1)  //节点高度（空树为-1）
template<typename T> class BinTree{
protected:
    int _size;  //规模
    BinNodePosi(T) _root;   //根节点
    int updateHeight(BinNodePosi(T) x); //更新节点的高度
    void updateHeightAbove(BinNodePosi(T) x);   //更新节点及祖先的高度
public: 
    BinTree(): _size(0), _root(nullptr){}   //构造
    ~BinTree(){if(0<_size) remove(_root);}  //析构
    int size() const {return _size;}    //规模
    bool empty() const {return !_root;} //判空
    BinNodePosi(T) root() const {return _root;} //树根
    BinNodePosi(T) insertAsRoot ( T const& e ); //插入根节点
    BinNodePosi(T) insertAsLC ( BinNodePosi(T) x, T const& e ); //e作为x的左孩子（原无）插入
    BinNodePosi(T) insertAsRC ( BinNodePosi(T) x, T const& e ); //e作为x的右孩子（原无）插入
    BinNodePosi(T) attachAsLC ( BinNodePosi(T) x, BinTree<T>* &S ); //T作为x左子树接入
    BinNodePosi(T) attachAsRC ( BinNodePosi(T) x, BinTree<T>* &S ); //T作为x右子树接入
    int remove ( BinNodePosi(T) x ); //初除以位置x处节点为根的子树，迒回该子树原先的规模
    BinTree<T>* secede ( BinNodePosi(T) x ); //将子树x从当前树中摘除，幵将其转换为一棵独立子树
    template <typename VST> void traverseLevel ( VST& visit ) { if ( _root ) _root->travLevel ( visit ); } //层次遍历
    void traversePre ( void (*visit)(T&) ) { if ( _root ) travPre ( _root, visit ); } //先序遍历
    void traverseIn (void (*visit)(T&)) { if ( _root ) travIn (_root, visit ); } //中序遍历
    void traversePost ( void (*visit)(T&) ) { if ( _root )travPost( _root, visit ); } //后序遍历
    bool operator<(BinTree<T> const& t){return _root && t._root && lt (_root, t._root);}    //比较器
    bool operator==(BinTree<T> const& t){return _root && t._root && (_root == t._root);}    //判等器
};
template<typename T> int BinTree<T>::updateHeight(BinNodePosi(T) x){    //更新高度
    x->height = 1 + std::max(stature(x->lchild), stature(x->rchild)); return x->height;
}
template<typename T> void BinTree<T>::updateHeightAbove(BinNodePosi(T) x){
     while(x){updateHeight(x); x = x->parent;}
}
template<typename T> BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e){   //插入根节点
    _size = 1; return _root = new BinNode<T>(e);
}
template<typename T> BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e){   //插入左孩子
    _size++; x->insertAsLC(e); updateHeightAbove(x); 
    return x->lchild;
}
template<typename T> BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e){   //插入右孩子
    _size++; x->insertAsRC(e); updateHeightAbove(x); 
    return x->rchild;
}
template<typename T> BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &S){   //S作为x的左子树接入，S置空
    if(x->lchild = S->_root) x->lchild->parent = x;
    _size+=S->_size;
    updateHeightAbove(x);
    S->_root = nullptr; S->_size = 0; release(S); S = nullptr; return x;    //释放S，返回接入位置
}
template<typename T> BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>* &S){   //S作为x的右子树接入，S置空
    if(x->rchild = S->_root) x->rchild->parent = x;
    _size+=S->_size;
    updateHeightAbove(x);
    S->_root = nullptr; S->_size = 0; release(S); S = nullptr; return x;    //释放S，返回接入位置
}

template<typename T> int BinTree<T>::remove(BinNodePosi(T) x){  //删除x及其后代，返回规模
    FromParentTo(*x) = nullptr; //切断来自x父节点的指针
    updateHeightAbove(x->parent);
    int n = removeAt(x); _size -= n; return n;
}
template<typename T> static int removeAt(BinNodePosi(T) x){ //删除x及其后代，返回规模
    if(!x) return 0;
    int n = 1 + removeAt(x->lchild) + removeAt(x->rchild);
    //release(x->data); release(x);    //release()负责释放复杂结构
    return n;
}
template<typename T> BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x){
    FromParentTo ( *x ) = NULL; //切断来自父节点的指针
    updateHeightAbove ( x->parent ); //更新原树中所有祖先的高度
    BinTree<T>* S = new BinTree<T>; S->_root = x; x->parent = NULL; //新树以x为根
    S->_size = x->size(); _size -= S->_size; return S; //更新规模，返回分离出来的子树
}
/*
template<typename T, typename VST> void travPre2(BinNodePosi(T) x, VST &visit){ //先序遍历（根左右）递归实现
    if(!x) return;
    visit(x->data);
    traversePre(x->lchild, visit);
    traversePre(x->rchild, visit);
} */
template<typename T> void travPost(BinNodePosi(T) x, void (*visit)(T&)){ //后序遍历（左右根）递归实现
    if(!x) return;
    travPost(x->lchild, visit);
    travPost(x->rchild, visit);
    visit(x->data);
}
template<typename T> void travIn(BinNodePosi(T) x, void (*visit)(T&)){ //中序遍历（左根右）递归实现
    if(!x) return;
    travIn(x->lchild, visit);
    visit(x->data);
    travIn(x->rchild, visit);
}
template <typename T> static void visitAlongLeftBranch(BinNodePosi(T) x, void (*visit)(T&), Stack<BinNodePosi(T)> &S){
    //从当前节点出发，沿左分支不断深入，直至没有左分支的节点；沿途节点遇到后立即访问
    while(x){
        visit(x->data);
        S.push(x->rchild);
        x = x->lchild;
    }
}
template <typename T> void travPre(BinNodePosi(T) x, void (*visit)(T&)){ //先序遍历（根左右）迭代实现
    Stack<BinNodePosi(T)> S;
    while(true){
        visitAlongLeftBranch(x, visit, S);
        if(S.empty())break;
        x = S.pop();
    }
}