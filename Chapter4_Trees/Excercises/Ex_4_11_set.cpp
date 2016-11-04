//
// Created by 涂金戈 on 02/11/2016.
//

#include <algorithm>
#include <iostream>
#include <stack>
#include <utility> // pair

template <typename Comparable>
class BinarySearchTree {
protected:
    struct BinaryNode {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        BinaryNode *parent;

        BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt, BinaryNode *pt)
                : element{theElement}, left{lt}, right{rt}, parent{pt} {}
        BinaryNode(Comparable && theElement, BinaryNode *lt, BinaryNode *rt, BinaryNode *pt)
                : element{std::move(theElement)}, left{lt}, right{rt}, parent{pt} {}
    };

public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree & rhs);
    BinarySearchTree(BinarySearchTree && rhs);
    ~BinarySearchTree();

    class const_iterator {
    public:
        const_iterator(): current {nullptr} {}

        const Comparable & operator* () const {
            return retrieve();
        }

        const_iterator & operator++ () {
            current = next();

            return *this;
        }

        const_iterator & operator++ (int) {
            const_iterator old = current;
            ++(*this);
            return old;
        }

        const_iterator & operator-- () {
            current = prev();

            return *this;
        }

        const_iterator & operator-- (int) {
            const_iterator old = current;
            --(*this);
            return old;
        }

        bool operator!= (const_iterator & rhs) {
            return current != rhs.current;
        }

        bool operator== (const_iterator & rhs) {
            return current == rhs.current;
        }

        bool hasNext() {
            return !next_stk.empty();
        }

        bool hasPrev() {
            return !prev_stk.empty();
        }

    protected:
        BinaryNode* current;
        std::stack<BinaryNode*> next_stk;
        std::stack<BinaryNode*> prev_stk;

        Comparable & retrieve() const {
            return current->element;
        }

        const_iterator(BinaryNode* p): current{p} {
            while (!prev_stk.empty())
                prev_stk.pop();
            while (!next_stk.empty())
                next_stk.pop();

            BinaryNode* next_p = p;
            // First, add seeds down up, up to root. If not, lose all the data except p's subtree.
            next_p = next_p->parent;
            while (next_p) {
                if (next_p->element > p->element)
                    next_stk.push(next_p);
                next_p = next_p->parent;
            }
            std::stack<BinaryNode*> reversed_next_stk;
            while (!next_stk.empty()) {
                reversed_next_stk.push(next_stk.top());
                next_stk.pop();
            }
            std::swap(reversed_next_stk, next_stk);
            // Then, add seeds of p's right subtree.
            next_p = p;
            if (next_p->right != nullptr) {
                next_p = next_p->right;
                while (next_p) {
                    next_stk.push(next_p);
                    next_p = next_p->left;
                }
            }

            BinaryNode* prev_p = p;

            prev_p = prev_p->parent;
            while (prev_p) {
                if (prev_p->element < p->element)
                    prev_stk.push(prev_p);
                prev_p = prev_p->parent;
            }
            std::stack<BinaryNode*> reversed_prev_stk;
            while (!prev_stk.empty()) {
                reversed_prev_stk.push(prev_stk.top());
                prev_stk.pop();
            }
            std::swap(reversed_prev_stk, prev_stk);

            prev_p = p;
            if (prev_p->left != nullptr) {
                prev_p = prev_p->left;
                while (prev_p) {
                    prev_stk.push(prev_p);
                    prev_p = prev_p->right;
                }
            }
        }

        BinaryNode* & next() {
            BinaryNode* tmp = next_stk.top();
            next_stk.pop();
            BinaryNode* ret = tmp;
            tmp = tmp->right;
            while(tmp) {
                next_stk.push(tmp);
                tmp = tmp->left;
            }

            return ret;
        }

        BinaryNode* & prev() {
            BinaryNode* tmp = prev_stk.top();
            prev_stk.pop();
            BinaryNode* ret = tmp;
            tmp = tmp->left;
            while(tmp) {
                prev_stk.push(tmp);
                tmp = tmp->right;
            }

            return ret;
        }

        friend class BinarySearchTree<Comparable>;
    };

    class iterator: public const_iterator {
    public:
        iterator() {}

        Comparable & operator* () {
            return const_iterator::retrieve();
        }

        const Comparable & operator* () const {
            return const_iterator::operator*();
        }

        iterator & operator++ () {
            if (this->hasNext())
                this->current = this->next();

            return *this;
        }

        iterator & operator++ (int) {
            iterator old = this->current;
            ++(*this);

            return old;
        }

        iterator & operator-- () {
            if (this->hasPrev())
                this->current = this->prev();

            return *this;
        }

        iterator & operator-- (int) {
            iterator old = this->current;
            --(*this);

            return old;
        }

        bool operator!= (const iterator & rhs) {
            return this->current != rhs.current;
        }

        bool operator== (const iterator &rhs) {
            return this->current == rhs.current;
        }

    protected:
        iterator(BinaryNode* p): const_iterator{p} {}
        friend class BinarySearchTree<Comparable>;
    };

    const Comparable & findMin() const;
    const Comparable & findMax() const;
    bool contains(const Comparable & x) const;
    iterator find(const Comparable & x) const;
    bool isEmpty() const;
    void printTree(std::ostream & out = std::cout) const;

    void makeEmpty();
//    void insert(const Comparable & x);
//    void insert(Comparable && x);
    std::pair<iterator, bool> insert(const Comparable & x);
    std::pair<iterator, bool> insert(iterator hint, const Comparable & x);
    std::pair<iterator, bool> insert(Comparable && x);
    void remove(const Comparable & x);

    BinarySearchTree & operator= (const BinarySearchTree & rhs);
    BinarySearchTree & operator= (BinarySearchTree && rhs);

    const size_t size() const {
        return theSize;
    }

    const_iterator begin() const {
        BinaryNode* p = root;
        while (p != nullptr && p->left != nullptr)
            p = p->left;

        return const_iterator{p};
    }

    iterator begin() {
        BinaryNode* p = root;
        while (p != nullptr && p->left != nullptr)
            p = p->left;

        return iterator{p};
    }

    const_iterator end() const {
        BinaryNode* p = root;
        while (p != nullptr && p->right != nullptr)
            p = p->right;

        return const_iterator{p};
    }

    iterator end() {
        BinaryNode* p = root;
        while (p != nullptr && p->right != nullptr)
            p = p->right;

        return iterator{p};
    }

protected:

    BinaryNode *root;
    size_t theSize;

//    void insert(const Comparable & x, BinaryNode * & t, BinaryNode * pt);
//    void insert(Comparable && x, BinaryNode * & t, BinaryNode * pt);
    std::pair<iterator, bool> insert(const Comparable & x, BinaryNode * & t, BinaryNode * pt);
    std::pair<iterator, bool> insert(Comparable && x, BinaryNode * & t, BinaryNode * pt);
    void remove(const Comparable & x, BinaryNode * & t);
    BinaryNode * findMin(BinaryNode *t) const;
    BinaryNode * findMax(BinaryNode *t) const;
    bool contains(const Comparable & x, BinaryNode *t) const;
    iterator find(const Comparable & x, BinaryNode *t) const;
    void makeEmpty(BinaryNode * & t);
    void printTree(BinaryNode *t, std::ostream & out, int indent = 0) const;
    BinaryNode * clone(BinaryNode *t) const;

};

#include <iomanip>

template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(): root{nullptr}, theSize{0} {

}

template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree &rhs): root{nullptr} {
    root = clone(rhs.root);
    theSize = rhs.theSize;
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
        return new BinaryNode{t->element, clone(t->left), clone(t->right), t->parent};
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
typename BinarySearchTree<Comparable>::iterator BinarySearchTree<Comparable>::find(const Comparable &x) const {
    return find(x, root);
}

template <typename Comparable>
typename BinarySearchTree<Comparable>::iterator BinarySearchTree<Comparable>::find(const Comparable &x, BinaryNode *t) const {
    if (t == nullptr)
        return iterator{};
    else if (x < t->element)
        return find(x, t->left);
    else if (t->element < x)
        return find(x, t->right);
    else
        return iterator{t};
}

template <typename Comparable>
bool BinarySearchTree<Comparable>::isEmpty() const {
    return root == nullptr;
}

//template <typename Comparable>
//void BinarySearchTree<Comparable>::insert(const Comparable &x) {
//    insert(x, root, nullptr);
//}

//template <typename Comparable>
//void BinarySearchTree<Comparable>::insert(const Comparable &x, BinaryNode *&t, BinaryNode *pt) {
//    if (t == nullptr)
//        t = new BinaryNode{x, nullptr, nullptr, pt};
//    else if (x < t->element)
//        insert(x, t->left, t);
//    else if (t->element < x)
//        insert(x, t->right, t);
//    else
//        ;
//}

//template <typename Comparable>
//void BinarySearchTree<Comparable>::insert(Comparable &&x) {
//    insert(x, root, nullptr);
//}

//template <typename Comparable>
//void BinarySearchTree<Comparable>::insert(Comparable &&x, BinaryNode *&t, BinaryNode *pt) {
//    if (t == nullptr)
//        t = new BinaryNode{std::move(x), nullptr, nullptr, pt};
//    else if (x < t->element)
//        insert(x, t->left, t);
//    else if (t->element < x)
//        insert(x, t->right, t);
//    else
//        ;
//}

template <typename Comparable>
std::pair<typename BinarySearchTree<Comparable>::iterator, bool> BinarySearchTree<Comparable>::insert(const Comparable &x) {
    return insert(x, root, nullptr);
}

template <typename Comparable>
std::pair<typename BinarySearchTree<Comparable>::iterator, bool> BinarySearchTree<Comparable>::insert(iterator hint,
                                                                                             const Comparable &x) {
    std::pair<typename BinarySearchTree<Comparable>::iterator, bool> & p = insert(x, hint.current, nullptr);
    if (!p.second)
        return insert(x, root, nullptr);
    else
        return p;
}

template <typename Comparable>
std::pair<typename BinarySearchTree<Comparable>::iterator, bool> BinarySearchTree<Comparable>::insert(const Comparable &x, BinaryNode *&t, BinaryNode *pt) {
    if (t == nullptr) {
        t = new BinaryNode{x, nullptr, nullptr, pt};
        ++theSize;
        return std::make_pair(iterator{t}, true);
    }
    else if (x < t->element)
        return insert(x, t->left, t);
    else if (t->element < x)
        return insert(x, t->right, t);
    else
        return std::make_pair(iterator{}, false);
}

template <typename Comparable>
std::pair<typename BinarySearchTree<Comparable>::iterator, bool> BinarySearchTree<Comparable>::insert(Comparable &&x) {
    return insert(x, root, nullptr);
}

template <typename Comparable>
std::pair<typename BinarySearchTree<Comparable>::iterator, bool> BinarySearchTree<Comparable>::insert(Comparable &&x,
                                                                                             BinaryNode *&t,
                                                                                             BinaryNode *pt) {
    if (t == nullptr) {
        t = new BinaryNode{std::move(x), nullptr, nullptr, pt};
        ++theSize;
        return std::make_pair(iterator{t}, true);
    }
    else if (x < t->element)
        return insert(x, t->left, t);
    else if (t->element < x)
        return insert(x, t->right, t);
    else
        return std::make_pair(iterator{}, false);
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
        if (t->left != nullptr)
            t->left->parent = t->parent;
        if (t->right != nullptr)
            t->right->parent = t->parent;
        t = (t->left != nullptr) ? t->left : t->right;
        --theSize;
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

template <typename Comparable>
class Set {
public:
    Set(): theTree{} {}
    Set(const Set & rhs) {
        theTree = std::move(rhs.theTree);
    }
    Set(Set && rhs): theTree{} {
        std::swap(theTree, rhs.theTree);
    }
    ~Set() {
    }

    typedef typename BinarySearchTree<Comparable>::iterator iterator;
    typedef typename BinarySearchTree<Comparable>::const_iterator const_iterator;

    iterator begin() {
        return theTree.begin();
    }
    const_iterator beign() const {
        return theTree.begin();
    }
    iterator end() {
        return theTree.end();
    }
    const_iterator end() const {
        return theTree.end();
    }
    std::pair<iterator, bool> insert(const Comparable & x) {
        return theTree.insert(x);
    }
    std::pair<iterator, bool> insert(iterator hint, const Comparable & x) {
        return theTree.insert(hint, x);
    }
    iterator erase(iterator itr) {
        theTree.remove(*itr);
    }
    iterator erase(iterator start, iterator end) {
        while (start != end) {
            theTree.remove(*start);
            ++start;
        }
    }
    iterator find(const Comparable & x) const {
        return theTree.find(x);
    }
    size_t size() const {
        return theTree.size();
    }
    void printTree() const {
        theTree.printTree();
    }

private:
    BinarySearchTree<Comparable> theTree;
};

int* Permutation3(int N) {
    int *a = new int[N], a_i;

    for (a_i = 0; a_i < N; ++a_i)
        a[a_i] = a_i + 1;

    for (a_i = 0; a_i < N; ++a_i) {
        std::swap(a[a_i], a[std::rand() % (a_i + 1)]);
    }

    return a;
}

#include <cstdlib>
#include <ctime>

int main() {
    Set<int> st;

    std::srand(std::time(0));

    int N = 10;
    int *nodes = Permutation3(N);

    std::cout << "Insert order: ";
    for (int i = 0; i < N; ++i) {
        st.insert(nodes[i]);
        std::cout << nodes[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Tree structure:\n";
    st.printTree();

    Set<int>::iterator it = st.begin();

    std::cout << "Set(ascending): ";
    while (it !=  st.end()) {
        std::cout << *it << " ";
        it++;
    }
    std::cout << *it;
    std::cout << std::endl;

    st.erase(it);
    Set<int>::iterator it_start = st.find(5);
    Set<int>::iterator it_end = st.find(9);
    st.erase(it_start, it_end);
    std::cout << "Set's size(after erasing): " << st.size() << std::endl;

    std::cout << "Tree structures:\n";
    st.printTree();

    it = st.end();

    std::cout << "Set(descending): ";
    while (it != st.begin()) {
        std::cout << *it-- << " ";
    }
    std::cout << *it;
    std::cout << std::endl;

    delete[] nodes;

//    Set<std::string> st;
//
//    st.insert("hello");
//    st.insert("Hello");
//    std::cout << st.size() << std::endl;
//
//    Set<std::string>::iterator it = st.begin();
//    while (it !=  st.end()) {
//        std::cout << *it << " ";
//        it++;
//    }
//    std::cout << *it;
//    std::cout << std::endl;

    return 0;
}