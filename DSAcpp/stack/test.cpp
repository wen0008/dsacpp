#include<iostream>
#include"stack.h"
#include<string.h>
using namespace std;
bool paren_matching(string s){  //括号匹配
    Stack<char> sc;
    for(auto c : s){
        if(c == '(' || c == '[' || c == '{') sc.push(c);
        if(c == ')'){
            char x = sc.pop();
            if(x != '(') return false;
        }
        if(c == ']'){
            char x = sc.pop();
            if(x != '[') return false;
        }
        if(c == '}'){
            char x = sc.pop();
            if(x != '{') return false;
        }  
    }
    return sc.empty();
}

int main(){
    string s("{[()][(())]]}");
    cout<<paren_matching(s);
    return 0;
}