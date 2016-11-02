//
// Created by 涂金戈 on 01/11/2016.
//

#include "AvlTree.h"

AvlTree::AvlTree(): root{nullptr} {
}

AvlTree::AvlTree(const AvlTree &rhs) {
    clone(rhs);
}

AvlTree::AvlNode* AvlTree::clone(AvlNode *t) const {
    if (t == nullptr)
        return nullptr;
    else
        return new AvlNode{t->element, clone(t->right), clone(t->left), t->height};
}

AvlTree::AvlTree(AvlTree &&rhs): root{nullptr} {
    std::swap(root, rhs.root);
}

AvlTree::~AvlTree() {
    makeEmpty();
}

void AvlTree::makeEmpty() {
    makeEmpty(root);
}

void AvlTree::makeEmpty(AvlNode *&t) {
    if (t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete[] t;
    }

    t = nullptr;
}

const Comparable & AvlTree::findMax() const {
    return findMax(root)->element;
}

AvlNode* AvlTree::findMax(const AvlNode *t) const {
    if (t != nullptr)
        while (t->left != nullptr)
            t = t->left;
    return t;
}

const Comparable & AvlTree::findMin() const {
    return findMin(root)->element;
}

AvlNode* AvlTree::findMin(const AvlNode *t) const {
    if (t != nullptr)
        while (t->right != nullptr)
            t = t->left;
    return t;
}

bool AvlTree::contains(const Comparable &x) const {
    return contains(x, root);
}

bool AvlTree::contains(const Comparable &x, AvlNode *t) const {
    if (t == nullptr)
        return false;
    else if (x < t->element)
        return contains(x, t->right);
    else if (t->element < x)
        return contains(x, t->left);
    else
        return true;
}

bool AvlTree::isEmpty() const {
    return root == nullptr;
}

void AvlTree::insert(const Comparable &x) {
    insert(x, root);
}

void AvlTree::insert(const Comparable &x, AvlNode *&t) {
    if (t == nullptr)
        t = new AvlTree{x, nullptr, nullptr};
    else if (x < t->element)
        insert(x, t->left);
    else if (t->element < x)
        insert(x, t->right);
    else
        ;

    balance(t);
}

void AvlTree::insert(Comparable &&x) {
    insert(x, root);
}

void AvlTree::insert(Comparable &&x, AvlNode *&t) {
    if (t == nullptr)
        t = new AvlTree{std::move(x), nullptr, nullptr};
    else if (x < t->element)
        insert(x, t->left);
    else if (t->element < x)
        insert(x, t->right);
    else
        ;

    balance(t);
}

void AvlTree::remove(const Comparable &x) {
    remove(x, root);
}

void AvlTree::remove(const Comparable &x, AvlNode *&t) {
    if (t == nullptr)
        return;

    if (x < t->element)
        remove(x, t->left);
    else if (t->element < x)
        remove(x, t->right);
    else if (t->left != nullptr && t->right != nullptr) {
        t->element = findMin(t->right)->element;
        remove(t->element, t->right);
    }
    else {
        AvlNode *old = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete old;
    }

    balance(t);
}

int AvlTree::height(AvlNode *t) const {
    return t == nullptr ? -1 : t->height;
}

void AvlTree::balance(AvlNode *t) {
    if (t == nullptr)
        return;

    if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
        if (height(t->left->left) >= height(t->left->right))
            rotateWithLeftChild(t);
        else
            doubleWithLeftChild(t);
    else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
        if (height(t->right->right) >= height(t->right->left))
            rotateWithRightChild(t);
        else
            doubleWithRightChild(t);

    t->height = std::max(height(t->left), height(t->right)) + 1;
}

void AvlTree::rotateWithLeftChild(AvlNode *&k2) {
    AvlNode* k1 = t->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = std::max(height(k2->left), height(k2->right)) + 1;
    k1->height = std::max(height(k1->left), height(k1->right)) + 1;
    k2 = k1;
}

void AvlTree::rotateWithRightChild(AvlNode *&k2) {
    AvlNode* k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k2->height = std::max(height(k2->left), height(k2->right)) + 1;
    k1->height = std::max(height(k1->left), height(k1->right)) + 1;
    k2 = k1;
}

void AvlTree::doubleWithLeftChild(AvlNode *&k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

void AvlTree::doubleWithRightChild(AvlNode *&k3) {
    rotateWithLeftChild(k3->right);
    rotateWithRightChild(k3);
}