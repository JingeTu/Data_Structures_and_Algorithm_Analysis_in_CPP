//
// Created by 涂金戈 on 27/12/2016.
//

#include "DisjSetsHeight.h"

DisjSetsHeight::DisjSetsHeight(const int &element_num) : VirtualDisjSets(element_num) {}

void DisjSetsHeight::UnionSetsHelper(const int &root1, const int &root2) {
    // If the two sets are the same, just return.
    if (root1 == root2)
        return;
    // If root2 is deeper.
    if (s[root2] < s[root1])
        // Make root1 as a subtree of root2.
        s[root1] = root2;
    else {
        // If root1 and root2 have the same depth.
        if (s[root1] == s[root2])
            --s[root1];
        // Make root2 as a subtree of root1.
        s[root2] = root1;
    }
}