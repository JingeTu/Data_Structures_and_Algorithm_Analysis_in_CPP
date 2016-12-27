//
// Created by 涂金戈 on 27/12/2016.
//

#include "DisjSetsSize.h"

DisjSetsSize::DisjSetsSize(const int &element_num) : VirtualDisjSets(element_num) {}

void DisjSetsSize::UnionSetsHelper(const int &root1, const int &root2) {
    if (root1 == root2)
        return;
    if (-s[root1] < -s[root2])
        return UnionSets(root2, root1);
    s[root1] -= -s[root2];
    s[root2] = root1;
}