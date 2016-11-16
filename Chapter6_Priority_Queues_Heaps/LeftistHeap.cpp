//
// Created by 涂金戈 on 11/11/2016.
//

#include "LeftistHeap.h"
#include <iomanip>

template<typename Comparable>
LeftistHeap<Comparable>::LeftistHeap(): root{nullptr} {

}

template<typename Comparable>
LeftistHeap<Comparable>::LeftistHeap(const LeftistHeap &rhs) {
    root = clone(rhs.root);
}

template<typename Comparable>
LeftistHeap<Comparable>::LeftistHeap(LeftistHeap &&rhs) {
    LeftistNode(std::move(rhs));
}

template<typename Comparable>
LeftistHeap<Comparable>::~LeftistHeap() {
    makeEmpty();
}

template<typename Comparable>
typename LeftistHeap<Comparable>::LeftistHeap &LeftistHeap<Comparable>::operator=(const LeftistHeap &rhs) {
    root = clone(rhs.root);
    return *this;
}

template<typename Comparable>
typename LeftistHeap<Comparable>::LeftistHeap &LeftistHeap<Comparable>::operator=(LeftistHeap &&rhs) {
    return operator=(std::move(rhs));
}

template<typename Comparable>
void LeftistHeap<Comparable>::insert(const Comparable &x) {
    root = merge(root, new LeftistNode{x, nullptr, nullptr, 0});
}

template<typename Comparable>
void LeftistHeap<Comparable>::insert(Comparable &&x) {
    insert(std::move(x));
}

template<typename Comparable>
void LeftistHeap<Comparable>::merge(LeftistHeap &rhs) {
    if (this == &rhs)
        return;

    merge(root, rhs.root);
    rhs.root = nullptr;
}

template<typename Comparable>
typename LeftistHeap<Comparable>::LeftistNode *LeftistHeap<Comparable>::merge(LeftistNode *h1, LeftistNode *h2) {
    if (h1 == nullptr)
        return h2;
    if (h2 == nullptr)
        return h1;
    if (h1->element < h2->element)
        return merge1(h1, h2);
    else
        return merge1(h2, h1);
}

template<typename Comparable>
typename LeftistHeap<Comparable>::LeftistNode *LeftistHeap<Comparable>::merge1(LeftistNode *h1, LeftistNode *h2) {
    if (h1->left == nullptr)
        h1->left = h2;
    else {
        h1->right = merge(h1->right, h2);
        if (h1->left->npl < h1->right->npl)
            swapChildren(h1);
        h1->npl = h1->right->npl + 1;
    }

    return h1;
}

template<typename Comparable>
void LeftistHeap<Comparable>::deleteMin() {
    if (isEmpty())
        return;

    LeftistNode *oldRoot = root;
    root = merge(root->left, root->right);
    delete oldRoot;
}

template<typename Comparable>
void LeftistHeap<Comparable>::deleteMin(Comparable &minItem) {
    minItem = findMin();

    deleteMin();
}

template<typename Comparable>
typename LeftistHeap<Comparable>::LeftistNode *LeftistHeap<Comparable>::clone(LeftistNode *t) const {
    return new LeftistNode{t->element, clone(t->right), clone(t->left), t->npl};
}

template<typename Comparable>
bool LeftistHeap<Comparable>::isEmpty() const {
    return root == nullptr;
}

template<typename Comparable>
void LeftistHeap<Comparable>::makeEmpty() {
    if (isEmpty())
        return;

    reclaimMemory(root);
    root = nullptr;
}

template<typename Comparable>
void LeftistHeap<Comparable>::swapChildren(LeftistNode *t) {
    LeftistNode *tmp;
    tmp = t->left;
    t->left = t->right;
    t->right = tmp;
}

template<typename Comparable>
const Comparable &LeftistHeap<Comparable>::findMin() const {
    return root->element;
}

template<typename Comparable>
void LeftistHeap<Comparable>::reclaimMemory(LeftistNode *t) {
    if (t == nullptr)
        return;
    reclaimMemory(t->left);
    reclaimMemory(t->right);
    delete t;
}

template<typename Comparable>
void LeftistHeap<Comparable>::printHeap(std::ostream &out) const {
    if (isEmpty())
        out << "Empty heap" << std::endl;
    else
        printHeap(root, out, 0);
}

template<typename Comparable>
void LeftistHeap<Comparable>::printHeap(LeftistNode *t, std::ostream &out, int indent) const {
    if (t != nullptr) {
        printHeap(t->right, out, indent + 4);
        out << std::setw(indent) << t->element << "(" << t->npl << ")" << std::endl;
        printHeap(t->left, out, indent + 4);
    }
}