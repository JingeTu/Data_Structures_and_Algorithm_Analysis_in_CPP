//
// Created by 涂金戈 on 31/10/2016.
//

#include <iostream>
template <typename Comparable>
class OrderedCollection {
public:
    OrderedCollection (size_t size = 0): current_size{size} {
        current_capacity = 2 * current_size + 1;
        array = new Comparable[current_capacity];
    }

    ~OrderedCollection() {
        delete[] array;
    }

    OrderedCollection (const OrderedCollection & rhs): current_size{rhs.current_size}, current_capacity{rhs.current_capacity} {
        array = new Comparable[current_capacity];

        size_t i;

        for (i = 0; i < current_size; ++i) {
            array[i] = rhs.array[i];
        }
    }

    OrderedCollection (OrderedCollection && rhs): current_size{rhs.current_size}, current_capacity{rhs.current_capacity} {
        array = rhs.array;
        rhs.current_size = 0;
        rhs.current_capacity = 0;
        rhs.array = nullptr;
    }

    OrderedCollection & operator= (const OrderedCollection & rhs) {
        if (this != &rhs) {
            current_size = rhs.current_size;
            current_capacity = rhs.current_capacity;
            array = new Comparable[current_size];
            for (int i = 0;i < current_size; ++i) {
                array[i] = rhs.array[i];
            }
        }

        return *this;
    }

    OrderedCollection &operator= (OrderedCollection && rhs) {
        std::swap(*this, rhs);

        return *this;
    }

    bool isEmpty() const {
        return current_size == 0;
    }

    void makeEmpty() {
        current_size = 0;
    }

    void insert(const Comparable & obj) {
        if (current_size == current_capacity) {
            reverse(current_capacity * 2);
        }

        size_t i, index;

        for (index = 0; index < current_size; ++index) {
            if (array[index] > obj) {
                break;
            }
        }

        for (i = 0; i < current_size - index; ++i) {
            array[current_size - i] = array[current_size - i - 1];
        }
        array[index] = obj;
        current_size++;
    }

    bool remove(const Comparable & obj) {
        size_t index = contains(obj);
        for (size_t i = index; i < current_size - 1; ++i) {
            array[i] = array[i + 1];
        }
        current_size--;
        return true;
    }

    bool reverse(size_t new_capacity) {
        if (new_capacity < current_size)
            return false;

        Comparable *new_array = new Comparable[new_capacity];
        for (size_t i = 0; i < current_size; ++i) {
            new_array[i] = array[i];
        }
        std::swap(array, new_array);

        delete[] new_array;
        return true;
    }

    Comparable & findMax() {
        return array[current_size - 1];
    }

    Comparable & findMin() {
        return array[0];
    }

    void print() {
        for (size_t i = 0; i < current_size; ++i) {
            std::cout << array[i] << ", ";
        }
        std::cout << "\n";
    }

private:
    size_t contains(const Comparable & obj) const {
        size_t i;
        for (i = 0; i < current_size; ++i) {
            if (array[i] == obj) break;
        }
        if (i == current_size)
            return -1;
        else
            return i;
    }

    size_t current_size;
    size_t current_capacity;
    Comparable* array;
};

int main() {
    OrderedCollection<int> collection;

    collection.insert(0);
    collection.insert(1);
    collection.insert(2);
    collection.insert(3);
    collection.insert(4);
    collection.insert(5);
    collection.insert(6);
    collection.insert(7);
    collection.insert(8);
    collection.insert(9);

    collection.print();

    std::cout << collection.findMax() << "\n";

    collection.remove(9);

    std::cout << collection.findMax() << "\n";

    collection.print();

    return 0;
}