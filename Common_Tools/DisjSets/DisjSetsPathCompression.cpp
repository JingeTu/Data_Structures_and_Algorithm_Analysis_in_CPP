//
// Created by 涂金戈 on 27/12/2016.
//

#include "DisjSetsPathCompression.h"

DisjSetsPathCompression::DisjSetsPathCompression(const int &element_num) : DisjSetsHeight(element_num) {}

int DisjSetsPathCompression::Find(const int &e) {
    if (s[e] < 0)
        return e;
    else
        return s[e] = Find(s[e]);
}