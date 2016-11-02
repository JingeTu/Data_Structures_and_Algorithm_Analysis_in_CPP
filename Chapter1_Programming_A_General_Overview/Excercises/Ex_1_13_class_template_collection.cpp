//
// Created by 涂金戈 on 31/10/2016.
//

#include <algorithm> // std::swap

template <typename Object>
class Collection {
public:
    Collection (size_t size = 0): current_size{size} {
        current_capacity = 2 * current_size + 1;
        array = new Object[current_capacity];
    }

    ~Collection() {
        delete[] array;
    }

    Collection (const Collection & rhs): current_size{rhs.current_size}, current_capacity{rhs.current_capacity} {
        array = new Object[current_capacity];

        size_t i;

        for (i = 0; i < current_size; ++i) {
            array[i] = rhs.array[i];
        }
    }

    Collection (Collection && rhs) {
        std::swap(current_size, rhs.current_size);
        std::swap(current_capacity, rhs.current_capacity);
        std::swap(array, rhs.array);
    }

    Collection & operator= (const Collection & rhs) {
        if (this != &rhs) {
            current_size = rhs.current_size;
            current_capacity = rhs.current_capacity;
            array = new Object[current_size];
            for (int i = 0;i < current_size; ++i) {
                array[i] = rhs.array[i];
            }
        }

        return *this;
    }

    Collection &operator= (Collection && rhs) {
        std::swap(*this, rhs);

        return *this;
    }

    bool isEmpty() const {
        return current_size == 0;
    }

    void makeEmpty() {
        current_size = 0;
    }

    bool insert(const Object & obj, size_t index) {

        if (current_size == 0 && index == 0) {
            array[index] = obj;
            current_size++;
            return true;
        }

        if (index >= current_size)
            return false;
        if (current_size == current_capacity) {
            reverse(current_capacity * 2);
        }

        size_t i;
        for (i = 0; i < current_size - index; ++i) {
            array[current_size - i] = array[current_size - i - 1];
        }
        array[index] = obj;
        current_size++;
        return true;
    }

    bool remove(size_t index) {
        if (index >= current_size)
            return false;
        for (size_t i = index; i < current_size - 1; ++i) {
            array[i] = array[i + 1];
        }
        current_size--;
        return true;
    }

    bool contains(const Object & obj) const {
        size_t i;
        for (i = 0; i < current_size; ++i) {
            if (array[i] == obj) break;
        }
        if (i == current_size)
            return false;
        else
            return true;
    }

    bool reverse(size_t new_capacity) {
        if (new_capacity < current_size)
            return false;

        Object *new_array = new Object[new_capacity];
        for (size_t i = 0; i < current_size; ++i) {
            new_array[i] = array[i];
        }
        std::swap(array, new_array);

        delete[] new_array;
        return true;
    }

    void print() {
        for (size_t i = 0; i < current_size; ++i) {
            std::cout << array[i] << ", ";
        }
        std::cout << "\n";
    }

private:
    size_t current_size;
    size_t current_capacity;
    Object* array;
};

int main() {
    Collection<int> collection;

    collection.insert(0, 0);
    collection.insert(1, 0);
    collection.insert(2, 0);
    collection.insert(3, 0);
    collection.insert(4, 0);
    collection.insert(5, 0);
    collection.insert(6, 0);
    collection.insert(7, 0);
    collection.insert(8, 0);
    collection.insert(9, 0);

    collection.print();

    std::cout << collection.contains(0) << "\n";

    collection.remove(9);

    std::cout << collection.contains(0) << "\n";

    collection.print();

    return 0;
}