#include"D:\code\c++\cpp_single\DSAcpp\list\list.h"
template<typename T> class Queue: public List<T>{   //由list派生
public:
    void enqueue(T const & e){this->insertAsLast(e);} //入队
    T dequeue(){return this->remove(this->first());}    //出队
    T& front(){return this->first()->data;}   //队首
};