typedef int Rank;   //秩
#define DEFAULT_CAPACITY 3  //默认初始容量

template <typename T> class Vector{
protected:
    Rank _size; //规模
    int _capacity;   //容量
    T* _elem;   //数据区
    void copyFrom(T const* A, Rank lo, Rank hi);    //复制数组区间A[lo,hi)
    void expend();  //空间不足时扩容
    void shrink();  //压缩
    bool bubble(Rank lo, Rank hi);  //扫描交换
    void bubbleSort(Rank lo, Rank hi);  //起泡排序
    Rank max(Rank lo, Rank hi);
    void selectionSort(Rank lo, Rank hi);   //选择排序
    void merge(Rank lo, Rank mi, Rank hi);
    void mergeSort(Rank lo, Rank hi);   //归并排序
    Rank partition(Rank lo, Rank hi);   //轴点构造
    void quickSort(Rank lo, Rank hi);   //快速排序
    void heapSort(Rank lo, Rank hi);    //堆排序
public:
//构造
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0){   //容量为c，规模为s，所有元素初始化为v
        _elem = new T[_capacity = c];
        for(_size = 0; _size < s; _elem[_size++] = v);
    }
    Vector(T const* A, Rank n){copyFrom(A, 0, n);}  //数组整体复制
    Vector(T const* A, Rank lo, Rank hi){copyFrom(A, lo, hi);}  //数组区间复制
    Vector(Vector<T> const& V){copyFrom(V._elem, 0, V._size);}  //向量整体复制
    Vector(Vector<T> const& V, Rank lo, Rank hi){copyFrom(V._elem, lo, hi);}    //向量区间复制
//析构
    ~Vector(){delete [] _elem;}
//只读
    Rank size()const{return _size;}
    bool empty()const{return !_size;}
    int disorder()const;    //是否有序
    Rank find(T const& e)const{return find(e,0,_size);} //无序向量整体查找
    Rank find(T const& e, Rank lo, Rank hi)const;   //区间查找
    Rank search(T const& e)const{return(_size <= 0)? -1 : search(e, 0, _size);} //有序向量区间查找
    Rank search(T const&e, Rank lo, Rank hi)const;  //整体查找
//可写
    T& operator[](Rank r)const; //重载下标操作符
    Vector<T> &operator= (Vector<T>const&); //重载赋值操作符，以便直接复制向量
    T remove(Rank r);   //删除元素
    int remove(Rank lo, Rank hi);   //删除[lo,hi)元素
    Rank insert(Rank r, T const& e);    //插入元素
    Rank insert(T const& e){return insert(_size, e);}
    void sort(Rank lo, Rank hi);    //排序
    void sort(){sort(0, _size);}
    void unsort(Rank lo, Rank hi);  //打乱
    void unsort(){unsort(0, _size);}
    int deduplicate();  //无序去重
    int uniquify(); //有序去重
//遍历
    void traverse(void(*)(T&)); //遍历（使用函数指针，只读或局部修改）
    template <typename VST> void traverse(VST&);    //遍历（使用函数对象，可局部修改） 
};   

template<typename T> void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi){    //复制
    _elem = new T[_capacity = 2 * (hi - lo)];
    _size = 0;
    while (lo < hi)
    {
        _elem[_size++] = A[lo++];
    }
}
template<typename T> Vector<T>& Vector<T>::operator=(Vector<T> const& V){   //重载赋值操作符
    if(_elem) delete [] _elem;  //释放原有内容
    copyFrom(V._elem, 0, V.size());
    return *this;
}
template<typename T> void Vector<T>::expend(){  //扩容
    if(_size < _capacity) return;
    if(_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
    T* oldElem = _elem;
    _elem = new T[_capacity <<= 1]; //容量加倍
    for (int i = 0; i < _size; i++)
    {
        _elem[i] = oldElem[i];
    }
    delete oldElem;
}
template<typename T> void Vector<T>::shrink(){  //缩容
    if(_capacity < DEFAULT_CAPACITY <<1) return;
    if(_size << 2 > _capacity) return;  //以1/4为界
    T* oldElem = _elem;
    _elem = new T[_capacity >>= 1]; //容量减半
    for (int i = 0; i < _size; i++)
    {
        _elem[i] = oldElem[i];
    }
    delete oldElem;
}
template<typename T> T& Vector<T>::operator[](Rank r)const{ //重载下标操作符
    return _elem[r];
}
template<typename T> void Vector<T>::unsort(Rank lo, Rank hi){  //等概率随机置乱
    T* v = _elem + lo;
    for (Rank i = hi - lo; i > 0; i--)
    {
        std::swap(v[i - 1], v[rand() % i]);
    }
}
template<typename T> Rank Vector<T>::find(T const& e, Rank lo, Rank hi)const{   //无序向量查找，失败时返回lo-1
    while ((lo < hi--) && (e != _elem[hi]));
    return hi;
}
template<typename T> Rank Vector<T>::insert(Rank r, T const& e){    //插入
    expend();
    for(int i = _size; i > r; i--) _elem[i] = _elem[i-1];
    _elem[r] = e;
    _size++;
    return r;
}
template<typename T> int Vector<T>::remove(Rank lo, Rank hi){   //删除
    if(lo == hi) return 0;
    while(hi < _size) _elem[lo++] = _elem[hi++];
    _size = lo;
    shrink();
    return hi-lo;
}
template<typename T> T Vector<T>::remove(Rank r){
    T e = _elem[r];
    remove(r, r+1);
    return e;
}
template<typename T> int Vector<T>::deduplicate(){  //去重
    int oldsize = _size;
    Rank i = 1;
    while(i < _size) (find(_elem[i], 0, i) < 0) ? i++ : remove(i);  //在i的前面寻找雷同者，若有则删除，无则i后移
    return oldsize- _size;
}
template<typename T>  void Vector<T>::traverse(void (*visit)(T&)){  //函数指针
    for(int i = 0; i < _size; i++) visit(_elem[i]); //遍历向量
}
template<typename T> template<typename VST> void Vector<T>::traverse(VST& visit){   //函数对象
    for(int i = 0; i < _size; i++) visit(_elem[i]);
} 
template<typename T> int Vector<T>::disorder()const{    //返回逆序相邻元素对总数
    int n = 0;
    for (int i = 0; i < _size; i++)
    {
        if(_elem[i-1] > _elem[i]) n++;
    }
    return n;
}
template<typename T>  int Vector<T>::uniquify(){    //有序向量去重
    Rank i = 0, j = 0;
    while (++j < _size) if(_elem[i] != _elem[j]) _elem[++i] = _elem[j];
    _size = ++i;
    shrink();
    return j-i;
}
template<typename T> Rank Vector<T>::search(T const& e, Rank  lo, Rank hi)const{    //查找接口
    return binSearch(_elem, e, lo, hi);
}
template<typename T> static Rank binSearch(T* A, T const& e, Rank lo, Rank hi){ //二分查找
    while (1 < hi-lo)
    {
        Rank mi = (lo + hi) >> 1;
        (e < A[mi]) ? hi = mi : lo = mi;
    }
    return (e == A[lo]) ? lo : -1;
}
template<typename T> void Vector<T>::sort(Rank lo, Rank hi){    //排序接口
    bubbleSort(lo, hi);
    //mergeSort(lo, hi);
}
template<typename T> void Vector<T>::bubbleSort(Rank lo, Rank hi){  //冒泡排序
    while(! bubble(lo, hi));
}
template<typename T> bool Vector<T>::bubble(Rank lo, Rank hi){
    bool sorted = true;
    while(++lo < hi) if(_elem[lo-1] > _elem[lo]){
        sorted = false;
        std::swap(_elem[lo-1], _elem[lo]);
    }
    return sorted;
}
template<typename T> void Vector<T>::mergeSort(Rank lo, Rank hi){   //归并排序,有问题，未解决
    if(hi-lo < 2) return;
    int mi = (lo+hi) / 2;
    mergeSort(lo, mi); mergeSort(mi, hi);
    merge(lo, mi, hi);
}
template<typename T> void Vector<T>::merge(Rank lo, Rank mi, Rank hi){
    T* A = _elem + lo;
    int lb = mi - lo;
    T* B = new T[lb];
    for(Rank i = 0; i < lb; B[i] = A[i++]);
    int lc = hi - mi;
    T* C = _elem + mi;
    for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);)
    {
        if((j < lb) && (!(k < lc) || (B[j] <= C[k]))) A[i++] = B[j++];
        if((k < lc) && (!(j < lb) || (C[k] < B[j]))) A[i++] = C[k++];
    }
    delete [] B;
}