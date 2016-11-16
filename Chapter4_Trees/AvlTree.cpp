//
// Created by 涂金戈 on 01/11/2016.
//

#include <iomanip>

template <typename Comparable>
AvlTree<Comparable>::AvlTree(): root{nullptr} {
}

template <typename Comparable>
AvlTree<Comparable>::AvlTree(const AvlTree &rhs) {
    clone(rhs);
}

template <typename Comparable>
typename AvlTree<Comparable>::AvlNode* AvlTree<Comparable>::clone(AvlNode *t) const {
    if (t == nullptr)
        return nullptr;
    else
        return new AvlNode{t->element, clone(t->right), clone(t->left), t->height};
}

template <typename Comparable>
AvlTree<Comparable>::AvlTree(AvlTree &&rhs): root{nullptr} {
    std::swap(root, rhs.root);
}

template <typename Comparable>
AvlTree<Comparable>::~AvlTree() {
    makeEmpty();
}

template <typename Comparable>
void AvlTree<Comparable>::makeEmpty() {
    makeEmpty(root);
}

template <typename Comparable>
void AvlTree<Comparable>::makeEmpty(AvlNode *&t) {
    if (t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete[] t;
    }

    t = nullptr;
}

template <typename Comparable>
const Comparable & AvlTree<Comparable>::findMax() const {
    return findMax(root)->element;
}

template <typename Comparable>
typename AvlTree<Comparable>::AvlNode* AvlTree<Comparable>::findMax(const AvlNode *t) const {
    if (t != nullptr)
        while (t->left != nullptr)
            t = t->left;
    return t;
}

template <typename Comparable>
const Comparable & AvlTree<Comparable>::findMin() const {
    return findMin(root)->element;
}

template <typename Comparable>
typename AvlTree<Comparable>::AvlNode* AvlTree<Comparable>::findMin(const AvlNode *t) const {
    if (t != nullptr)
        while (t->right != nullptr)
            t = t->left;
    return t;
}

template <typename Comparable>
bool AvlTree<Comparable>::contains(const Comparable &x) const {
    return contains(x, root);
}

template <typename Comparable>
bool AvlTree<Comparable>::contains(const Comparable &x, AvlNode *t) const {
    if (t == nullptr)
        return false;
    else if (x < t->element)
        return contains(x, t->right);
    else if (t->element < x)
        return contains(x, t->left);
    else
        return true;
}

template <typename Comparable>
bool AvlTree<Comparable>::isEmpty() const {
    return root == nullptr;
}

template <typename Comparable>
void AvlTree<Comparable>::insert(const Comparable &x) {
    insert(x, root);
}

template <typename Comparable>
void AvlTree<Comparable>::insert(const Comparable &x, AvlNode *&t) {
    if (t == nullptr)
        t = new AvlNode{x, nullptr, nullptr};
    else if (x < t->element)
        insert(x, t->left);
    else if (t->element < x)
        insert(x, t->right);
    else
        ;

    balance(t);
}

template <typename Comparable>
void AvlTree<Comparable>::insert(Comparable &&x) {
    insert(x, root);
}

template <typename Comparable>
void AvlTree<Comparable>::insert(Comparable &&x, AvlNode *&t) {
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

template <typename Comparable>
void AvlTree<Comparable>::remove(const Comparable &x) {
    remove(x, root);
}

template <typename Comparable>
void AvlTree<Comparable>::remove(const Comparable &x, AvlNode *&t) {
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

template <typename Comparable>
int AvlTree<Comparable>::height(AvlNode *t) const {
    return t == nullptr ? -1 : t->height;
}

template <typename Comparable>
void AvlTree<Comparable>::balance(AvlNode *&t) {
    if (t == nullptr)
        return;

    if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) {
        if (height(t->left->left) >= height(t->left->right))
            rotateWithLeftChild(t);
        else
            doubleWithLeftChild(t);
    }
    else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) {
        if (height(t->right->right) >= height(t->right->left))
            rotateWithRightChild(t);
        else
            doubleWithRightChild(t);
    }

    t->height = std::max(height(t->left), height(t->right)) + 1;
}

template <typename Comparable>
void AvlTree<Comparable>::rotateWithLeftChild(AvlNode *&k2) {
    AvlNode* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = std::max(height(k2->left), height(k2->right)) + 1;
    k1->height = std::max(height(k1->left), height(k1->right)) + 1;
    k2 = k1;
}

template <typename Comparable>
void AvlTree<Comparable>::rotateWithRightChild(AvlNode *&k2) {
    AvlNode* k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k2->height = std::max(height(k2->left), height(k2->right)) + 1;
    k1->height = std::max(height(k1->left), height(k1->right)) + 1;
    k2 = k1;
}

template <typename Comparable>
void AvlTree<Comparable>::doubleWithLeftChild(AvlNode *&k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

template <typename Comparable>
void AvlTree<Comparable>::doubleWithRightChild(AvlNode *&k3) {
    rotateWithLeftChild(k3->right);
    rotateWithRightChild(k3);
}

template <typename Comparable>
void AvlTree<Comparable>::printTree(std::ostream &out) const {
    if (isEmpty())
        out << "Empty tree" << std::endl;
    else
        printTree(root, out, 0);
}

template <typename Comparable>
void AvlTree<Comparable>::printTree(AvlNode *t, std::ostream &out, int indent) const {
    if (t != nullptr) {
        printTree(t->right, out, indent + 4);
        out << std::setw(indent) << t->element << std::endl;
        printTree(t->left, out, indent + 4);
    }
}