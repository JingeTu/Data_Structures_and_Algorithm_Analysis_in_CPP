//
// Created by 涂金戈 on 01/11/2016.
//

#include <iomanip>

template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(): root{nullptr} {

}

template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree &rhs): root{nullptr} {
    root = clone(rhs.root);
}

template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(BinarySearchTree &&rhs): root{nullptr} {
    std::swap(root, rhs.root);
}

template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode* BinarySearchTree<Comparable>::clone(BinaryNode *t) const {
    if (t == nullptr)
        return nullptr;
    else
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
}

template <typename Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree() {
    makeEmpty();
};

template <typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty() {
    makeEmpty(root);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty(BinaryNode *&t) {
    if (t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

template <typename Comparable>
const Comparable & BinarySearchTree<Comparable>::findMin() const {
    return findMin(root)->element;
}

template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode * BinarySearchTree<Comparable>::findMin(BinaryNode *t) const { // non-recursive version
    if (t != nullptr)
        while (t->left != nullptr)
            t = t->left;
    return t;
}

//template <typename Comparable>
//BinaryNode<Comparable> * BinarySearchTree<Comparable>::findMin(BinaryNode *t) const { // recursive version
//    if (t == nullptr)
//        return nullptr;
//    else if (t->left == nullptr)
//        return t;
//    return findMin(t->left);
//}

template <typename Comparable>
const Comparable & BinarySearchTree<Comparable>::findMax() const {
    return findMax(root)->element;
}

template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode * BinarySearchTree<Comparable>::findMax(BinaryNode *t) const { // non-recursive version
    if (t != nullptr)
        while (t->right != nullptr)
            t = t->right;
    return t;
}

//template <typename Comparable>
//BinaryNode<Comparable> * BinarySearchTree<Comparable>::findMax(BinaryNode *t) const { // recursive version
//    if (t == nullptr)
//        return nullptr;
//    else if (t->right == nullptr)
//        return t;
//    return findMax(t->right);
//}

template <typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable &x) const {
    return contains(x, root);
}

template <typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable &x, BinaryNode *t) const {
    if (t == nullptr)
        return false;
    else if (x < t->element)
        return contains(x, t->left);
    else if (t->element < x) // if only use <, then do not need to define operator > for Comparable
        return contains(x, t->right);
    else
        return true;
}

template <typename Comparable>
bool BinarySearchTree<Comparable>::isEmpty() const {
    return root == nullptr;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable &x) {
    insert(x, root);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable &x, BinaryNode *&t) {
    if (t == nullptr)
        t = new BinaryNode{x, nullptr, nullptr};
    else if (x < t->element)
        insert(x, t->left);
    else if (t->element < x)
        insert(x, t->right);
    else
        ;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(Comparable &&x) {
    insert(x, root);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(Comparable &&x, BinaryNode *&t) {
    if (t == nullptr)
        t = new BinaryNode{std::move(x), nullptr, nullptr};
    else if (x < t->element)
        insert(x, t->left);
    else if (t->element < x)
        insert(x, t->right);
    else
        ;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable &x) {
    remove(x, root);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable &x, BinaryNode *&t) {
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

template <typename Comparable>
void BinarySearchTree<Comparable>::printTree(std::ostream &out) const {
    if (isEmpty())
        out << "Empty tree" << std::endl;
    else
        printTree(root, out, 0);
}

template <typename Comparable>
void BinarySearchTree<Comparable>::printTree(BinaryNode *t, std::ostream &out, int indent) const {
    if (t != nullptr) {
        printTree(t->right, out, indent + 4);
        out << std::setw(indent) << t->element << std::endl;
        printTree(t->left, out, indent + 4);
    }
}