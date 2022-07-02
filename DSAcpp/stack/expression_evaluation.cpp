#include<iostream>
#include"stack.h"
#include<string.h>
using namespace std;
float evaulate(char* s, char* &rpn){    //表达式求值
    Stack<float> opnd;  //运算数栈
    Stack<char> optr;   //运算符栈
    optr.push('\0');    //与表达式字符串尾匹配
    while (!optr.empty())
    {
        if(isdigit(*s)) readNumber(s, opnd);
        else switch(orderBetween(optr.top(), *s)){
            case '<': optr.push(*s); s++; break;
            case '=': optr.pop(); s++; break;   //优先级相等，即当前运算符为')或'\0'
            case '>': {
                char op = optr.pop();
                if('!' == op) opnd.push(calcu(op, opnd.pop()));
                else{
                    float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop();
                    opnd.push(calcu(pOpnd1, op, pOpnd2));
                }
                break;
            }
        }
    }
    return opnd.pop();
}