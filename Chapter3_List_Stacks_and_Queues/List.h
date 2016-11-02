//
// Created by 涂金戈 on 01/11/2016.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_LIST_H
#define DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_LIST_H


#include <algorithm>
#include <stdexcept>

template <typename Object>
class List {
private:
    struct Node {
        Node* prev;
        Node* next;
        Object data;

        Node(const Object & d = Object {}, Node* p = nullptr, Node* n = nullptr): data{d}, prev{p}, next{n} {}

        Node(Object && d, Node* p = nullptr, Node* n = nullptr): data{std::move(d)}, prev{p}, next{n} {}
    };

public:
    class const_iterator {
    public:
        const_iterator(): current {nullptr} {}

        const Object & operator* () const {
            return retrieve();
        }

        const_iterator & operator++ () {
            current = current->next;

            return *this;
        }

        const_iterator & operator++ (int) {
            const_iterator old = current;
            ++(*this);
            return old;
        }

        const_iterator & operator-- () {
            current = current->prev;

            return *this;
        }

        const_iterator & operator-- (int) {
            const_iterator old = current;
            --(*this);
            return old;
        }

    protected:
        const List<Object> *theList;
        Node* current;

        Object & retrieve() const {
            return current->data;
        }

        const_iterator(const List<Object> & lst, Node* p): theList{&lst}, current{p} {}

        void assertIsValid() const {
            if (theList == nullptr || current == nullptr || current == theList->head)
//                throw IteratorOutOfBoundsException{};
                throw std::overflow_error("iterator error");
        }

        friend class List<Object>;
    };

    class iterator: public const_iterator {
    public:
        iterator() {}

        Object & operator* () {
            return const_iterator::retrieve();
        }

        const Object & operator* () const {
            return const_iterator::operator*();
        }

        iterator & operator++ () {
//            current = current->next; // this is wrong, in Child Class, must use pointer this to access Parent Class's member
            this->current = this->current->next;

            return *this;
        }

        iterator & operator++ (int) {
            iterator old = this->current;
            ++(*this);

            return old;
        }

        iterator & operator-- () {
            this->current = this->current->prev;

            return *this;
        }

        iterator & operator-- (int) {
            iterator old = this->current;
            --(*this);

            return old;
        }

    protected:
        iterator(const List<Object> & lst, Node *p): const_iterator{lst, p} {}
        friend class List<Object>;
    };

public:
    List() {
        init();
    }

    List(const List & rhs) {
        init();
        for (auto & x : rhs)
            push_back(x);
    }

    ~List() {
        clear();
        delete head;
        delete tail;
    }

    List & operator= (const List & rhs) {
        List copy{rhs};
        std::swap(*this, copy);

        return *this;
    }

    List (List && rhs): theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail} {
        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }

    List & operator= (List && rhs) {
        std::swap(theSize, rhs.theSize);
        std::swap(head, rhs.head);
        std::swap(tail, rhs.tail);

        return *this;
    }


    iterator begin() {
        return iterator{*this, head->next};
    }

    const_iterator begin() const {
        return const_iterator{*this, head->next};
    }

    iterator end() {
        return iterator{*this, tail};
    }

    const_iterator end() const {
        return const_iterator{*this, tail};
    }


    int size() const {
        return theSize;
    }

    bool empty() const {
        return size() == 0;
    }


    void clear() {
        while(!empty()) {
            pop_front();
        }
    }

    Object & front() {
        return *begin();
    }

    const Object & front() const {
        return *begin();
    }

    Object & back() {
        return *--end();
    }

    const Object & back() const {
        return *--end();
    }

    void push_front(const Object & x) {
        insert(begin(), x);
    }

    void push_front(Object && x) {
        insert(begin(), std::move(x));
    }

    void push_back(const Object & x) {
        insert(end(), x);
    }

    void push_back(Object && x) {
        insert(end(), std::move(x));
    }

    void pop_front() {
        erase(begin());
    }

    void pop_back() {
        erase(--end());
    }


    iterator insert(iterator itr, const Object & x) {
        itr.assertIsValid();
        Node* p = itr.current;
        ++theSize; // do not forget modify theSize
        return iterator{*this, p->prev = p->prev->next = new Node{x, p->prev, p}};
    }

    iterator insert(iterator itr, Object&& x) {
        itr.assertIsValid();
        Node* p = itr.current;
        ++theSize;
        return iterator{*this, p->prev = p->prev->next = new Node{std::move(x), p->prev, p}};
    }


    iterator erase(iterator itr) {
        itr.assertIsValid();
        Node* p = itr.current;
        Node* q = itr.current->next;
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        --theSize; // do not forget modify theSize

        return iterator{*this, q};
    }

    iterator erase(iterator from, iterator to) {
        from.assertIsValid();
        to.assertIsValid();
        iterator itr = from;
        while (itr != to)
//            erase(itr++); // erase itself will move itr to itr->next
            erase(itr);

        return to;
    }

private:
    int theSize;
    Node* head;
    Node* tail;

    void init() {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }
};


#endif //DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_LIST_H
