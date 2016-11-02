//
// Created by 涂金戈 on 31/10/2016.
//

#include "Stack.h"

#include <iostream>

int main() {
    Stack<int> stk;
    stk.push_back(1);
    stk.push_back(2);
    stk.push_back(3);

    std::cout << stk.top() << "\t" << stk.size() << std::endl;
    stk.pop_back();
    std::cout << stk.top() << "\t" << stk.size() << std::endl;
    stk.pop_back();
    std::cout << stk.top() << "\t" << stk.size() << std::endl;
    stk.pop_back();
    std::cout << stk.top() << "\t" << stk.size() << std::endl;
//    stk.pop_back();
    return 0;
}