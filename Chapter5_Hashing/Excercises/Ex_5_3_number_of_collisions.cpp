//
// Created by 涂金戈 on 10/11/2016.
//

#include <iostream>
#include <ctime>
#include <sstream>

#include "debug_used_hash_table/LinearProbingHashTable.h"
#include "debug_used_hash_table/QuadraticProbingHashTable.h"
#include "debug_used_hash_table/DoubleHashingHashTable.h"
#include "../Employee.h"

int* Permutation3(int N) {
    int *a = new int[N], a_i;

    for (a_i = 0; a_i < N; ++a_i)
        a[a_i] = a_i + 1;

    for (a_i = 0; a_i < N; ++a_i) {
        std::swap(a[a_i], a[std::rand() % (a_i + 1)]);
    }

    return a;
}

int main() {

    std::srand(std::time(0));

    int * nums = Permutation3(50);

    LinearProbingHashTable<Employee> lph;
    lph.debug_setCollisionsNum();
    for (int i = 0; i < 50; ++i) {
        std::stringstream ss;
        ss << nums[i];
        lph.insert(Employee(ss.str()));
    }
//    std::stringstream ss;
//    ss << nums[10];
//    lph.insert(Employee(ss.str()));
//    std::cout << lph.contains(Employee(ss.str())) << std::endl;
    std::cout << "Linear probing hash table collisions number: " << lph.debug_getCollisionsNum() << std::endl;

    QuadraticProbingHashTable<Employee> qph;
    qph.debug_setCollisionsNum();
    for (int i = 0; i < 50; ++i) {
        std::stringstream ss;
        ss << nums[i];
        qph.insert(Employee(ss.str()));
    }
    std::cout << "Quadratic probing hash table collisions number: " << qph.debug_getCollisionsNum() << std::endl;

    DoubleHashingHashTable<Employee> dhh;
    dhh.debug_setCollisionsNum();
    for (int i = 0; i < 50; ++i) {
        std::stringstream ss;
        ss << nums[i];
        dhh.insert(Employee(ss.str()));
    }
    std::cout << "Double hashing hash table collisions number: " << dhh.debug_getCollisionsNum() << std::endl;

    delete[] nums;

    return 0;
}