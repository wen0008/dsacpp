#include"D:\code\c++\cpp_single\DSAcpp\vector\vector.h"
template <typename T> class Stack: public Vector<T>{    //由向量派生
public:
    void push(T const& e){this->insert(this->size(), e);}   //入栈
    T pop(){return this->remove(this->size() - 1);}      //出栈
    T& top(){return (*this)[this->size() - 1];}    //取栈顶
  //empty()可直接调用  
};