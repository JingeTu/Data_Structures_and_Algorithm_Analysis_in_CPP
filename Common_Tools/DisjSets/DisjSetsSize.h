//
// Created by 涂金戈 on 27/12/2016.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_DISJSETSSIZE_H
#define DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_DISJSETSSIZE_H

#include "VirtualDisjSets.h"

class DisjSetsSize : public VirtualDisjSets {
public:

    DisjSetsSize(const int &element_num);

private:

    void UnionSetsHelper(const int &root1, const int &root2);

};

#include "DisjSetsSize.cpp"

#endif //DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_DISJSETSSIZE_H
