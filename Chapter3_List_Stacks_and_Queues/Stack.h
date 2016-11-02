//
// Created by 涂金戈 on 01/11/2016.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_STACK_H
#define DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_STACK_H


#include "List.h"

template <typename Object>
class Stack: private List<Object> {
public:
    Stack(): List<Object>{} {}

    void push_back(const Object & x) {
        List<Object>::push_back(x);
    }

    void push_back(Object && x) {
        List<Object>::push_back(x);
    }

    Object & top() {
        return List<Object>::back();
    }

    const Object & top() const {
        return List<Object>::back();
    }

    void pop_back() {
        List<Object>::pop_back();
    }

    int size() const {
        return List<Object>::size();
    }
};


#endif //DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_STACK_H
