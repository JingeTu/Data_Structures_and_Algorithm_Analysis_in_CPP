//
// Created by 涂金戈 on 11/11/2016.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_BINOMIALQUEUE_H
#define DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_BINOMIALQUEUE_H

#include <vector>

template<typename Comparable>
class BinomialQueue {
public:
    BinomialQueue();

    BinomialQueue(const Comparable &item);

    BinomialQueue(const BinomialQueue &rhs);

    BinomialQueue(BinomialQueue &&rhs);

    ~BinomialQueue();

    BinomialQueue &operator=(const BinomialQueue &rhs);

    BinomialQueue &operator=(BinomialQueue &&rhs);

    bool isEmpty() const;

    const Comparable &findMin() const;

    void insert(const Comparable &x);

    void insert(Comparable &&x);

    void deleteMin();

    void deleteMin(Comparable &minItem);

    void makeEmpty();

    void merge(BinomialQueue &rhs);

private:
    struct BinomialNode {
        Comparable element;
        BinomialNode *leftChild;
        BinomialNode *nextSibiling;

        BinomialNode(const Comparable &e, BinomialNode *lt, BinomialNode *rt)
                : element{e}, leftChild{lt}, nextSibiling{rt} {}

        BinomialNode(Comparable &&e, BinomialNode *lt, BinomialNode *rt)
                : element{std::move(e)}, leftChild{lt}, nextSibiling{rt} {}
    };

    const static int DEFAULT_TREES = 1;

    std::vector<BinomialNode *> theTrees;
    int currentSize;

    int findMinIndex() const;

    int capacity() const;

    BinomialNode *combineTrees(BinomialNode *t1, BinomialNode *t2);

    void makeEmpty(BinomialNode *&t);

    BinomialNode *clone(BinomialNode *t) const;
};

#include "BinomialQueue.cpp"

#endif //DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_BINOMIALQUEUE_H
