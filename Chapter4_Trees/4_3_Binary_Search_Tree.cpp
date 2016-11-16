//
// Created by 涂金戈 on 02/11/2016.
//

#include "BinarySearchTree.h"
#include "../Common_Tools/permutation.h"

int main() {

    std::srand(std::time(0));

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