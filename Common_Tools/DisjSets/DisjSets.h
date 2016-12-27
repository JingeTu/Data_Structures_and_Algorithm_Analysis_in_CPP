//
// Created by 涂金戈 on 27/12/2016.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_DISJSETS_H
#define DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_DISJSETS_H

#include "VirtualDisjSets.h"

class DisjSets : public VirtualDisjSets {
public:

    DisjSets(const int &element_num);

private:

    void UnionSetsHelper(const int &root1, const int &root2);

};

#include "DisjSets.cpp"

#endif //DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_DISJSETS_H
