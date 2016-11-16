//
// Created by 涂金戈 on 12/11/2016.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_PERMUTATION_H
#define DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_PERMUTATION_H

#include <ctime>
#include <cstdlib>


int *Permutation3(int N) {

    int *a = new int[N], a_i;

    for (a_i = 0; a_i < N; ++a_i)
        a[a_i] = a_i + 1;

    for (a_i = 0; a_i < N; ++a_i) {
        std::swap(a[a_i], a[std::rand() % (a_i + 1)]);
    }

    return a;
}

#endif //DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_PERMUTATION_H
