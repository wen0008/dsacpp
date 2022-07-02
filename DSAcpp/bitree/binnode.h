#define BinNodePosi(T) BinNode<T>*  //节点位置
template<typename T> struct BinNode{
    BinNodePosi(T) parent;  //父
    BinNodePosi(T) lchild;
    BinNodePosi(T) rchild;  //左右孩子
    T data; //数据
    int height; //高度
    int size(); //子树规模
    int npl;    //左式堆
    //RBcolor color;  //颜色（红黑树）
    //构造函数
    BinNode():parent(nullptr), lchild(nullptr), rchild(nullptr), height(0), npl(1){}
    BinNode(T e, BinNodePosi(T) p=nullptr, BinNodePosi(T) lc=nullptr, BinNodePosi(T) rc=nullptr,
            int h=0, int l=1): data(e), parent(p), lchild(lc), rchild(rc), height(h), npl(l){}
    //操作接口
    BinNodePosi(T) insertAsLC(T const &);   //作为左孩子插入
    BinNodePosi(T) insertAsRC(T const &);   //作为右孩子插入
    //比较器，判别器
    bool operator< (BinNode const bn){return data < bn.data;}
    bool operator== (BinNode const bn){return data == bn.data;}
};
template<typename T> BinNodePosi(T) BinNode<T>::insertAsLC(T const &e){ //插入
    return lchild = new BinNode(e, this);
}
template<typename T> BinNodePosi(T) BinNode<T>::insertAsRC(T const &e){
    return rchild = new BinNode(e, this);
}
template<typename T> int BinNode<T>::size(){    //后代总数（以其为根的子树规模
    int s = 1;  //计入本身
    if(lchild) s += lchild->size(); //递归计入左子树规模
    if(rchild) s += rchild->size();
    return s;
}
// BinNode状态性质的判断
#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lchild ) )
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rchild ) )
#define HasParent(x) ( ! IsRoot(x) )
#define HasLChild(x) ( (x).lchild )
#define HasRChild(x) ( (x).rchild )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) ) //至少拥有一个孩子
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) ) //同时拥有两个孩子
#define IsLeaf(x) ( ! HasChild(x) )
//与BinNode具有特定关系的节点及指针
#define sibling(p) ( IsLChild( * (p) ) ? (p)->parent->rchild : (p)->parent->lchild )    //兄弟
#define uncle(x) ( IsLChild( * ( (x)->parent ) ) ? (x)->parent->parent->rchild : (x)->parent->parent->lchild )  //叔叔
#define FromParentTo(x) ( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lchild : (x).parent->rchild ) )   //来自父节点的引用
