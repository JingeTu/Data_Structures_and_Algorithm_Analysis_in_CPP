//
// Created by 涂金戈 on 02/11/2016.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_VECTOR_H
#define DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_VECTOR_H

#include <algorithm>

template <typename Object>
class Vector {
public:
    explicit Vector(int initSize = 0): theSize{initSize}, theCapacity{initSize + SPARE_CAPACITY} {
        objects = new Object[theCapacity];
    }

    Vector(const Vector & rhs): theSize{rhs.theSize}, theCapacity{rhs.theCapacity} {
        objects = new Object[theCapacity];
        for (int i = 0; i < theSize; ++i)
            objects[i] = rhs.objects[i];
    }

    Vector(Vector && rhs): theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, objects{rhs.objects} {
        rhs.objects = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }

    ~Vector() {
        delete[] objects;
    }

    // this is right, but it duplicates code.
//    Vector & operator= (const Vector & rhs): theSize{rhs.theSize}, theCapacity{rhs.theCapacity} {
//        objects = new Object[theCapacity];
//        for (int i = 0; i < theSize; ++i)
//            objects[i] = rhs.objects[i];
//        return *this;
//    }

    Vector & operator= (const Vector & rhs) {
        Vector copy(rhs);
        std::swap(*this, copy);
        return *this;
    }

    Vector & operator= (Vector && rhs) {
        std::swap(objects, rhs.objects);
        std::swap(theSize, rhs.theSize);
        std::swap(theCapacity, rhs.theCapacity);
        return *this;
    }

    void resize(int newSize) {
        if (newSize > theCapacity)
            reserve(2 * newSize);
        theSize = newSize;
    }

    void reserve(int newCapacity) {
        if (newCapacity < theSize) // I forgot to check the theSize.
            return;
        Object* new_objects = new Object[newCapacity];
        for (int i = 0; i < theSize; ++i)
//            new_objects[i] = objects[i]; // this is copy
            new_objects[i] = std::move(objects[i]); // this is move

        theCapacity = newCapacity; // I forgot to set the new capacity.
        std::swap(new_objects, objects);
        delete[] new_objects;
    }

    Object & operator[] (int index) {
        return objects[index];
    }

    const Object & operator[] (int index) const {
        return objects[index];
    }

    bool empty() const {
        return theSize == 0;
    }

    int size() const {
        return theSize;
    }

    int capacity() const {
        return theCapacity;
    }

    void push_back(const Object & x) {
        if (theSize == theCapacity)
            reserve(2 * theCapacity + 1);
        objects[theSize++] = x;
    }

    void push_back(Object && x) {
        if (theSize == theCapacity)
            reserve(2 * theCapacity + 1);
        objects[theSize++] = std::move(x);
    }

    void pop_back() {
        --theSize;
    }

    const Object & back() const {
        return objects[theSize - 1];
    }

    typedef Object * iterator;
    typedef const Object * const_iterator;

    iterator begin() {
        return &objects[0];
    }

    const_iterator begin() const {
        return &objects[0];
    }

    iterator end() {
        return &objects[theSize];
    }

    const_iterator end() const {
        return &objects[theSize];
    }

    static const int SPARE_CAPACITY = 16;

private:
    int theSize;
    int theCapacity;
    Object* objects;
};


#endif //DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_VECTOR_H
