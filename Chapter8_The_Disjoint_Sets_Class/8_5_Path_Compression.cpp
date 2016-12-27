//
// Created by 涂金戈 on 22/11/2016.
//

#include "../Common_Tools/DisjSets/DisjSetsPathCompression.h"

int main() {

    DisjSetsPathCompression disjSets(16);

    disjSets.UnionSets(0, 1);
    disjSets.UnionSets(2, 3);
    disjSets.UnionSets(0, 2);
    disjSets.UnionSets(6, 7);
    disjSets.UnionSets(4, 5);
    disjSets.UnionSets(4, 6);
    disjSets.UnionSets(0, 4);
    disjSets.UnionSets(8, 9);
    disjSets.UnionSets(10, 11);
    disjSets.UnionSets(8, 10);
    disjSets.UnionSets(12, 13);
    disjSets.UnionSets(14, 15);
    disjSets.UnionSets(12, 14);
    disjSets.UnionSets(8, 12);
    disjSets.UnionSets(0, 8);

    disjSets.Print();

    disjSets.Find(14);

    std::cout << "After Find(14):\n";

    disjSets.Print();

    return 0;
}