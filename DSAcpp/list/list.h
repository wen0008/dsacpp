#include "listnode.h"
template <typename T> class List    //列表模板类
{   // header  -first-node-node-node-last-  trailer
private:
    int _size; ListNodePosi(T) header; ListNodePosi(T) trailer;     //规模，头节点，尾结点

protected:
    void init();     //初始化
    int clear();    //清空
    void copyNodes(ListNodePosi(T), int);    //复制p起的n项
    void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int);   //归并
    void sort(ListNodePosi(T), int n);  //排序
    void mergeSort(ListNodePosi(T), int);      //p开始n项归并排序
    void selectionSort(ListNodePosi(T), int);      //选择排序
    void insertionSort(ListNodePosi(T), int);      //插入排序

public:
    List(){init();}    //默认构造
    List(List<T> const& L);      //整体复制
    List(List<T> const& L, Rank r, int n);   //复制从第r项起n项
    List(ListNodePosi(T) p, int n);     //复制从位置p起n项
    ~List();    //析构
    //只读访问接口
    Rank size() const {return _size;}   //规模
    bool empty() const {return _size<=0;}   //判空
    T& operator[](Rank r) const;    //重载[]支持循秩访问L[r](效率低)
    ListNodePosi(T) first(){return header->succ;}   //首节点位置
    ListNodePosi(T) last(){return trailer->pred;}   //末节点位置
    bool vaild(ListNodePosi(T) p){return p && (trailer!=p) && (header!=p);}  //判断位置p是否合法
    int disordered() const;     //判断是否有序
    ListNodePosi(T) find(T const& e) const{return find(e,_size,trailer);}   //无序列表查找
    ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const;     //无序区间查找,区间为p的n个真前驱
    ListNodePosi(T) search(T const& e) const{return search(e,_size,trailer);}   //有序列表查找
    ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const;     //有序区间查找 
    ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);    //在p及其n-1个后继选出最大值
    ListNodePosi(T) selectMin(ListNodePosi(T) p, int n);    //在p及其n-1个后继选出最小值
    ListNodePosi(T) selectMax(){return selectMax(header->succ, _size);}     //选出整体最大值
    ListNodePosi(T) selectMin(){return selectMin(header->succ, _size);}     //选出整体最大值

    //可写访问接口
    ListNodePosi(T) insertAsFirst(T const& e);  //e作为首节点插入
    ListNodePosi(T) insertAsLast(T const& e);   //e作为尾节点插入
    ListNodePosi(T) insertAfter(ListNodePosi(T) p, T const& e);    //e作为p的后继插入
    ListNodePosi(T) insertBefore(ListNodePosi(T) p, T const& e);    //e作为p的前驱插入
    T remove(ListNodePosi(T) p);    //删除p处节点并将其返回（pop）
    void merge(List<T>& L){merge(first(), size, L, L.first(), L._size);}    //全列表归并
    //void sort(ListNodePosi(T) p, int n);    //列表区间排序
    void sort(){sort(first(),_size);}    //列表整体排序
    int depuplicate();  //无序去重
    int uniquify();     //有序去重
    void reverse();     //前后倒置

    //遍历
    void traverse(void(*)(T&));     //遍历，依次实施visit操作（函数指针，只读后局部修改）
    template<typename VST>  //操作器
    void traverse(VST&);    //遍历，依次visit（函数对象，可全局性修改）
};

template <typename T> void List<T>::init(){     //初始化列表
    header = new ListNode<T>;   //创建头节点
    trailer = new ListNode<T>;  //尾结点
    header->succ = trailer; header->pred = nullptr;
    trailer->pred = header; trailer->succ = nullptr;
    _size=0;
} 

template <typename T> ListNodePosi(T) List<T>::insertAsFirst(T const& e){   //作为首节点插入
    _size++;
    return header->insertAsSucc(e);
}
template <typename T> ListNodePosi(T) List<T>::insertAsLast(T const& e){   //作为末节点插入
    _size++;
    return trailer->insertAsPred(e);
}
template <typename T> ListNodePosi(T) List<T>::insertBefore(ListNodePosi(T) p, T const& e){ //e作为p的前驱插入
    ++_size;
    return p->insertAsPred(e);
}
template <typename T> ListNodePosi(T) List<T>::insertAfter(ListNodePosi(T) p, T const& e){ //e作为p的后继插入
    ++_size;
    return p->insertAsSucc(e);
}
template <typename T> void List<T>::copyNodes(ListNodePosi(T) p, int n){    //复制p后n个节点，o(n)
    init();
    while (n--)
    {
        insertAsLast(p->data);
        p = p->succ;
    }        
}
template <typename T> List<T>::List(ListNodePosi(T) p, int n){
    copyNodes(p, n);
}
template <typename T> List<T>::List(List<T> const& L){
    copyNodes(L.first(), L._size);
}
template <typename T> List<T>::List(List<T> const& L, Rank r, int n){
    copyNodes(L[r], n);
}

template <typename T> T List<T>::remove(ListNodePosi(T) p){     //删除节点p并返回，o(1)
    T e = p->data;  //备份data以便返回
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size--;
    return e; 
}
template <typename T> int List<T>::clear(){     //清空列表
    int oldsize = _size;
    while (0 < oldsize)
    {
        remove(header->succ);
        return oldsize;
    }
    return -9999999;
}
template <typename T> List<T>::~List(){     //析构
    clear();
    delete header;
    delete trailer;
}

template <typename T> ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p)const{ //顺序查找不大于e的最后者，o(n)
    while (0 < n--) //从右向左逐个比对p前驱和e
    {
        if(e == (p = p->pred)->data) return p;  //直至找到或越界
        else return nullptr;
    }
}
template <typename T> ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p)const{   //有序列表查找，o(n)
    while (0 <= n--)
    {
        if(((p = p->pred)->data) <= e) break;
    }
    return p;
    
}

template <typename T> int List<T>::depuplicate(){   //删除重复节点
    if(_size < 2) return 0;
    int oldsize = _size;
    ListNodePosi(T) p = first(); Rank r = 1;    //p从首节点起查找，r为p之前结点个数
    while (trailer != (p = p->succ))
    {
        ListNodePosi(T) q = find(p->data, r, p);    //在p的r个真前驱中查找与之相同者
        q ? remove(q) : r++;
    }   //任意时刻p的真前驱互不相同
    return oldsize - _size;
}   
template <typename T> int List<T>::uniquify(){  //成批剔除重复节点
    if(_size < 2) return 0;
    int oldsize = _size;
    ListNodePosi(T) p = first(); ListNodePosi(T) q;   //p为各区段起点，q为其后继
    while (trailer != (q = p->succ))
    {
        if(p->data != q->data) p = q;
        else remove(q);
    }
    return oldsize - _size;
}

template <typename T> void List<T>::sort(ListNodePosi(T) p, int n){
    /*switch (rand() % 2)
    {
    case 1:
        selectionSort(p, n);
        break;
    case 2:
        insertionSort(p, n);
        break;
    default:
        mergeSort(p, n);
        break;  
    }*/
    selectionSort(p, n);
}
template <typename T> void List<T>::selectionSort(ListNodePosi(T) p, int n){    //选择排序
    ListNodePosi(T) head = p->pred; ListNodePosi(T) tail = p;   //head-tail为待排序区间
    for(int i = 0; i < n; i++) tail = tail->succ;
    while (1 < n)
    {
        insertBefore(tail, remove(selectMax(head->succ, n)));
        tail = tail->pred; n--;
    }   
}
template <typename T> ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n){
    ListNodePosi(T) max = p;
    for(ListNodePosi(T) cur = p; 1 < n; n--){
        if(max->data <= (cur = cur->succ)->data) max = cur;
    }
    return max;
}
template <typename T> void List<T>::insertionSort(ListNodePosi(T) p, int n){ //插入排序
    for(int r = 0; r < n; r++){
        insertAfter(search(p->data, r, p), p->data);
        p = p->succ;
        remove(p->pred);
    }    
}
/*template <typename T> void List<T>::merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m){
    ListNodePosi(T) pp = p->pred;
    while (0 < m)
    {
        if((0 < n) && (p->data <= q->data)){
            if(q == (p = p->succ)) break;
            n--;
        }
        else{
            insertBefore(p, L.remove((q = q->succ)->pred)); //q==nullptr使报错，未解决
            m--;
        }
    }
    p = pp->succ;
}
template <typename T> void List<T>::mergeSort(ListNodePosi(T) p, int n){    //归并排序
    if(n < 2) return;
    int m = n>>1;
    ListNodePosi(T) q = p;
    for(int i = 0; i < m; i++){
        q=q->succ;
    }
    mergeSort(p, m);
    mergeSort(q, n-m);
    merge(p, m, *this, q, n-m);
}*/