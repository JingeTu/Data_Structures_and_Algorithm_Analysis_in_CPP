//
// Created by 涂金戈 on 11/11/2016.
//

#include "BinomialQueue.h"

template<typename Comparable>
BinomialQueue<Comparable>::BinomialQueue() : theTrees(0), currentSize{0} {}

template<typename Comparable>
BinomialQueue<Comparable>::BinomialQueue(const Comparable &item) : theTrees(2) {
    theTrees[0] = nullptr;
    theTrees[1] = new BinomialNode(item, nullptr, nullptr);
    currentSize = 1;
}

template<typename Comparable>
BinomialQueue<Comparable>::BinomialQueue(const BinomialQueue &rhs) {
    theTrees.resize(rhs.theTrees.size());
    currentSize = rhs.currentSize;

    for (int i = 0; i < rhs.theTrees.size(); ++i) {
        theTrees[i] = clone(theTrees[i]);
    }
}

template<typename Comparable>
BinomialQueue<Comparable>::BinomialQueue(BinomialQueue &&rhs) {
    BinomialQueue(std::move(rhs));
}

template<typename Comparable>
BinomialQueue<Comparable>::~BinomialQueue() {
    makeEmpty();
}

template<typename Comparable>
typename BinomialQueue<Comparable>::BinomialQueue &BinomialQueue<Comparable>::operator=(const BinomialQueue &rhs) {
    BinomialQueue copy{rhs};
    std::swap(*this, copy);

    return *this;
}

template<typename Comparable>
typename BinomialQueue<Comparable>::BinomialQueue &BinomialQueue<Comparable>::operator=(BinomialQueue &&rhs) {
    return operator=(std::move(rhs));
}

template<typename Comparable>
bool BinomialQueue<Comparable>::isEmpty() const {
    return currentSize == 0;
}

template<typename Comparable>
const Comparable &BinomialQueue<Comparable>::findMin() const {
    return theTrees[findMinIndex()]->element;
}

template<typename Comparable>
void BinomialQueue<Comparable>::insert(const Comparable &x) {
    BinomialQueue *newNode = new BinomialQueue(x);
    merge(*newNode);
}

template<typename Comparable>
void BinomialQueue<Comparable>::insert(Comparable &&x) {
    insert(std::move(x));
}

template<typename Comparable>
void BinomialQueue<Comparable>::deleteMin() {
    Comparable tmp;
    deleteMin(tmp);
}

template<typename Comparable>
void BinomialQueue<Comparable>::deleteMin(Comparable &minItem) {
    if (isEmpty())
        return;

    int minIndex = findMinIndex();
    minItem = theTrees[minIndex]->element;
    BinomialNode *oldRoot = theTrees[minIndex];
    BinomialNode *deletedTree = oldRoot->leftChild;
    delete oldRoot;

    BinomialQueue deletedQueue;
    deletedQueue.theTrees.resize(minIndex + 1);
    deletedQueue.currentSize = (1 << minIndex) - 1;
    for (int j = minIndex - 1; j >= 0; --j) {
        deletedQueue.theTrees[j] = deletedTree;
        deletedTree = deletedTree->nextSibiling;
        deletedQueue.theTrees[j]->nextSibling = nullptr;
    }

    theTrees[minIndex] = nullptr;
    currentSize -= deletedQueue.currentSize + 1;

    merge(deletedQueue);
}

template<typename Comparable>
void BinomialQueue<Comparable>::makeEmpty() {
    for (int i = 0; i < theTrees.size(); ++i)
        makeEmpty(theTrees[i]);
}

template<typename Comparable>
void BinomialQueue<Comparable>::merge(BinomialQueue &rhs) {
    if (this == &rhs)
        return;

    currentSize += rhs.currentSize;

    if (currentSize > capacity()) {
        int oldNumTrees = theTrees.size();
        int newNumTrees = (theTrees.size() > rhs.theTrees.size() ? theTrees.size() : rhs.theTrees.size()) + 1;
        theTrees.resize(newNumTrees);
        for (int i = oldNumTrees; i < newNumTrees; ++i)
            theTrees[i] = nullptr;
    }

    BinomialNode *carry = nullptr;
//    for (int i = 0, j = 1; j <= currentSize; ++i, j += 2) {
    for (int i = 0; i < theTrees.size(); ++i) {
        BinomialNode *t1 = theTrees[i];
        BinomialNode *t2 = i < rhs.theTrees.size() ? rhs.theTrees[i] : nullptr;

        int whichCase = t1 == nullptr ? 0 : 1;
        whichCase += t2 == nullptr ? 0 : 2;
        whichCase += carry == nullptr ? 0 : 4;

        switch (whichCase) {
            case 0: // No trees
            case 1: // Only this
                break;
            case 2: // Only rhs
                theTrees[i] = t2;
                rhs.theTrees[i] = nullptr;
                break;
            case 4: // Only carry
                theTrees[i] = carry;
                carry = nullptr;
                break;
            case 3: // this and rhs
                carry = combineTrees(t1, t2);
                theTrees[i] = rhs.theTrees[i] = nullptr;
                break;
            case 5: // this and carry
                carry = combineTrees(t1, carry);
                theTrees[i] = nullptr;
                break;
            case 6: // rhs and carry
                carry = combineTrees(t2, carry);
                rhs.theTrees[i] = nullptr;
                break;
            case 7: // All three
                theTrees[i] = carry;
                carry = combineTrees(t1, t2);
                rhs.theTrees[i] = nullptr;
                break;
        }
    }

    for (auto &root : rhs.theTrees)
        root = nullptr;
    rhs.currentSize = 0;
}

template<typename Comparable>
int BinomialQueue<Comparable>::findMinIndex() const {
    int i, minIndex;

    for (i = 0; theTrees[i] == nullptr; ++i);

    for (minIndex = i; i < theTrees.size(); ++i)
        if (theTrees[i] != nullptr && theTrees[i]->element < theTrees[minIndex]->element)
            minIndex = i;

    return minIndex;
}

template<typename Comparable>
int BinomialQueue<Comparable>::capacity() const {
    return (int) theTrees.size();
}

template<typename Comparable>
typename BinomialQueue<Comparable>::BinomialNode *
BinomialQueue<Comparable>::combineTrees(BinomialNode *t1, BinomialNode *t2) {
    if (t2->element < t1->element)
        return combineTrees(t2, t1);
    t2->nextSibiling = t1->leftChild;
    t1->leftChild = t2;

    return t1;
}

template<typename Comparable>
void BinomialQueue<Comparable>::makeEmpty(BinomialNode *&t) {
    if (t == nullptr)
        return;

    BinomialNode *deletedTree = t->nextSibiling;
    while (deletedTree != nullptr) {
        BinomialNode *oldDeletedTree = deletedTree;
        makeEmpty(deletedTree);
        deletedTree = oldDeletedTree->nextSibiling;
    }

    makeEmpty(t->leftChild);

    delete t;
    t = nullptr;
    --currentSize;
}

template<typename Comparable>
typename BinomialQueue<Comparable>::BinomialNode *BinomialQueue<Comparable>::clone(BinomialNode *t) const {
    if (t == nullptr) return t;

    return new BinomialNode{t->element, clone(t->leftChild), clone(t->nextSibiling)};
}