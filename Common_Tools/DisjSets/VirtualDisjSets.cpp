//
// Created by 涂金戈 on 27/12/2016.
//

#include "VirtualDisjSets.h"

bool VirtualDisjSets::SameSet(const int &e1, const int &e2) const {
    return Find(e1) == Find(e2);
}

void VirtualDisjSets::UnionSets(const int &e1, const int &e2) {
    // Find the sets of e1 and e2, respectively.
    int root1 = Find(e1);
    int root2 = Find(e2);

    // Union the set of e1 and the set of e2.
    UnionSetsHelper(root1, root2);
}

void VirtualDisjSets::Print() const {
    for (int i = 0; i < s.size(); ++i)
        std::cout << "i: " << i << "\tvalue: " << s[i] << std::endl;
}

int VirtualDisjSets::Find(const int &e) const {
    // If the find the root of the tree,
    // just return the root index.
    if (s[e] < 0)
        return e;
    else
        return Find(s[e]);
};
