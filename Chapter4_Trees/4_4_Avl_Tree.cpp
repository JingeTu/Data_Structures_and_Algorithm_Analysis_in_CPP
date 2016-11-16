//
// Created by 涂金戈 on 01/11/2016.
//

#include "AvlTree.h"
#include "../Common_Tools/permutation.h"

int main() {

    std::srand(std::time(0));

    int N = 50;
    int *nodes = Permutation3(N);

    AvlTree<int> at;

    for (int i = 0; i < N; ++i) {
        at.insert(nodes[i]);
    }

    at.printTree();

    delete[] nodes;

    return 0;
}