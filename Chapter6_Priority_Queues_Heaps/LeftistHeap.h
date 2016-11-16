//
// Created by 涂金戈 on 11/11/2016.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_LEFTISTHEAP_H
#define DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_LEFTISTHEAP_H

#include <iostream>

template<typename Comparable>
class LeftistHeap {
public:
    LeftistHeap();

    LeftistHeap(const LeftistHeap &rhs);

    LeftistHeap(LeftistHeap &&rhs);

    ~LeftistHeap();

    LeftistHeap &operator=(const LeftistHeap &rhs);

    LeftistHeap &operator=(LeftistHeap &&rhs);

    bool isEmpty() const;

    const Comparable &findMin() const;

    void insert(const Comparable &x);

    void insert(Comparable &&x);

    void deleteMin();

    void deleteMin(Comparable &minItem);

    void makeEmpty();

    void merge(LeftistHeap &rhs);

    void printHeap(std::ostream &out = std::cout) const;

private:
    struct LeftistNode {
        Comparable element;
        LeftistNode *left;
        LeftistNode *right;
        int npl;

        LeftistNode(const Comparable &e, LeftistNode *lt = nullptr, LeftistNode *rt = nullptr, int np = 0)
                : element{e}, left{lt}, right{rt}, npl{np} {}

        LeftistNode(Comparable &&e, LeftistNode *lt = nullptr, LeftistNode *rt = nullptr, int np = 0)
                : element{std::move(e)}, left{lt}, right{rt}, npl{np} {}
    };

    LeftistNode *root;

    LeftistNode *merge(LeftistNode *h1, LeftistNode *h2);

    LeftistNode *merge1(LeftistNode *h1, LeftistNode *h2);

    void swapChildren(LeftistNode *t);

    void reclaimMemory(LeftistNode *t);

    void printHeap(LeftistNode *t, std::ostream & out, int indent = 0) const;

    LeftistNode *clone(LeftistNode *t) const;

};

#include "LeftistHeap.cpp"

#endif //DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_LEFTISTHEAP_H
