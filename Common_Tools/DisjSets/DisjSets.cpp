//
// Created by 涂金戈 on 27/12/2016.
//

#include "DisjSets.h"

DisjSets::DisjSets(const int &element_num) : VirtualDisjSets(element_num) {}

void DisjSets::UnionSetsHelper(const int &root1, const int &root2) {
    s[root2] = root1;
}
