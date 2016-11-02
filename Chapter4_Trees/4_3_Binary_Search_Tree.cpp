//
// Created by 涂金戈 on 02/11/2016.
//

#include "BinarySearchTree.h"
#include <cstdlib>

int* Permutation3(int N) {
//    std::cout << "Alg3. permutate " << N << ".\n";
    int *a = new int[N], a_i;

//    clock_t start_clock, end_clock;
//    start_clock = clock();
    for (a_i = 0; a_i < N; ++a_i)
        a[a_i] = a_i + 1;

    for (a_i = 0; a_i < N; ++a_i) {
        std::swap(a[a_i], a[std::rand() % (a_i + 1)]);
    }
//    end_clock = clock();

//    std::cout << "Consumed " << double(end_clock - start_clock) / CLOCKS_PER_SEC * 1e6 <<" us.\n";

    return a;
}

int main() {

    int N = 10;
    int *nodes = Permutation3(N);

    BinarySearchTree<int> bt;

    for (int i = 0; i < N; ++i) {
        bt.insert(nodes[i]);
    }

    bt.printTree();

    delete[] nodes;

    return 0;
}