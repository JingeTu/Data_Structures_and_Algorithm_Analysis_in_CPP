//
// Created by 涂金戈 on 01/11/2016.
//

#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree(): root{nullptr} {

}

BinarySearchTree::BinarySearchTree(const BinarySearchTree &rhs): root{nullptr} {
    root = clone(rhs.root);
}

BinarySearchTree::BinarySearchTree(BinarySearchTree &&rhs): root{nullptr} {
    std::swap(root, rhs.root);
}

BinarySearchTree* BinarySearchTree::clone(BinaryNode *t) const {
    if (t == nullptr)
        return nullptr;
    else
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
}

BinarySearchTree::~BinarySearchTree() {
    makeEmpty();
};

void BinarySearchTree::makeEmpty() {
    makeEmpty(root);
}

void BinarySearchTree::makeEmpty(BinaryNode *&t) {
    if (t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

const Comparable & findMin() const {
    return findMin(root)->element;
}

BinaryNode * BinarySearchTree::findMin(BinaryNode *t) const { // non-recursive version
    if (t != nullptr)
        while (t->left != nullptr)
            t = t->left;
    return t;
}

//BinaryNode * BinarySearchTree::findMin(BinaryNode *t) const { // recursive version
//    if (t == nullptr)
//        return nullptr;
//    else if (t->left == nullptr)
//        return t;
//    return findMin(t->left);
//}

const Comparable & BinarySearchTree::findMax() const {
    return findMax(root)->element;
}

BinaryNode * BinarySearchTree::findMax(BinaryNode *t) const { // non-recursive version
    if (t != nullptr)
        while (t->right != nullptr)
            t = t->right;
    return t;
}

//BinaryNode * BinarySearchTree::findMax(BinaryNode *t) const { // recursive version
//    if (t == nullptr)
//        return nullptr;
//    else if (t->right == nullptr)
//        return t;
//    return findMax(t->right);
//}

bool BinarySearchTree::contains(const Comparable &x) const {
    return contains(x, root);
}

bool BinarySearchTree::contains(const Comparable &x, BinaryNode *t) const {
    if (t == nullptr)
        return false;
    else if (x < t->element)
        return contains(x, t->left);
    else if (t->element < x) // if only use <, then do not need to define operator > for Comparable
        return contains(x, t->right);
    else
        return true;
}

bool BinarySearchTree::isEmpty() const {
    return root == nullptr;
}

void BinarySearchTree::insert(const Comparable &x) {
    insert(x, root);
}

void BinarySearchTree::insert(const Comparable &x, BinaryNode *&t) {
    if (t == nullptr)
        t = new BinaryNode{x, nullptr, nullptr};
    else if (x < t->element)
        insert(x, t->left);
    else if (t->element < x)
        insert(x, t->right);
    else
        ;
}

void BinarySearchTree::insert(Comparable &&x) {
    insert(x, root);
}

void BinarySearchTree::insert(Comparable &&x, BinaryNode *&t) {
    if (t == nullptr)
        t = new BinaryNode{std::move(x), nullptr, nullptr};
    else if (x < t->element)
        insert(x, t->left);
    else if (t->element < x)
        insert(x, t->right);
    else
        ;
}

void BinarySearchTree::remove(const Comparable &x) {
    remove(x, root);
}

void BinarySearchTree::remove(const Comparable &x, BinaryNode *&t) {
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
        BinaryNode *oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldNode;
    }
}

void BinarySearchTree::printTree(std::ostream &out) const {
    printTree(root, out);
}

void BinarySearchTree::printTree(BinaryNode *t, std::ostream &out) const {
    if(t != NULL) {
        if(t->left) postorder(t->left, indent+4);
        if(t->right) postorder(t->right, indent+4);
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        cout<< t->element << "\n ";
    }
}