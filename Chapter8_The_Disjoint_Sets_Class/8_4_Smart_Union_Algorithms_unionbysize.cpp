//
// Created by 涂金戈 on 22/11/2016.
//

#include "../Common_Tools/DisjSets/DisjSetsSize.h"

int main() {

    DisjSetsSize disjSets(8);

    disjSets.UnionSets(6, 7);
    disjSets.UnionSets(4, 3);
    disjSets.UnionSets(4, 5);
    disjSets.UnionSets(7, 4);

    disjSets.Print();

    return 0;
}