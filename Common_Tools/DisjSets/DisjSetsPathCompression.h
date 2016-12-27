//
// Created by 涂金戈 on 27/12/2016.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_DISJSETSPATHCOMPRESSION_H
#define DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_DISJSETSPATHCOMPRESSION_H

#include "DisjSetsHeight.h"

class DisjSetsPathCompression : public DisjSetsHeight {
public:

    DisjSetsPathCompression(const int &element_num);

    int Find(const int &e);

};

#include "DisjSetsPathCompression.cpp"

#endif //DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_DISJSETSPATHCOMPRESSION_H
