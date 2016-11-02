//
// Created by 涂金戈 on 31/10/2016.
//
#include "List.h"
#include <iostream>

int main() {

    List<int> list;
    int begin_data, end_data;

    std::cout << list.size() << std::endl;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);
    list.push_back(6);
    list.push_back(7);
    list.push_back(8);

    begin_data = *list.begin();
    std::cout << begin_data << std::endl;

    list.pop_front();
    begin_data = *list.begin();
    std::cout << begin_data << std::endl;

    end_data = *--list.end();
    std::cout << end_data << std::endl;

    list.pop_back();
    end_data = list.back();
    std::cout << end_data << std::endl;

    std::cout << list.size() << std::endl;

    return 0;
}