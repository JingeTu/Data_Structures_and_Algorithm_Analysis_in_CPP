//
// Created by 涂金戈 on 22/11/2016.
//


#include <iostream>
#include <vector>

class DisjSets {
public:
    DisjSets(int numElements);

    int find(int x);

    void unionSets(int root1, int root2);

    void prints();

private:
    std::vector<int> s;
};

DisjSets::DisjSets(int numElements) : s(numElements, -1) {}

int DisjSets::find(int x) {
    if (s[x] < 0)
        return x;
    else
        return s[x] = find(s[x]);
}

void DisjSets::unionSets(int root1, int root2) {
    if (s[root2] < s[root1])
        s[root1] = root2;
    else {
        if (s[root1] == s[root2])
            --s[root1];
        s[root2] = root1;
    }
}

void DisjSets::prints() {
    for (int i = 0; i < s.size(); ++i)
        std::cout << "i: " << i << "\tvalue: " << s[i] << std::endl;
}

int main() {

    DisjSets ds(16);

    ds.unionSets(0, 1);
    ds.unionSets(2, 3);
    ds.unionSets(0, 2);
    ds.unionSets(6, 7);
    ds.unionSets(4, 5);
    ds.unionSets(4, 6);
    ds.unionSets(0, 4);
    ds.unionSets(8, 9);
    ds.unionSets(10, 11);
    ds.unionSets(8, 10);
    ds.unionSets(12, 13);
    ds.unionSets(14, 15);
    ds.unionSets(12, 14);
    ds.unionSets(8, 12);
    ds.unionSets(0, 8);

    ds.prints();

    ds.find(14);

    std::cout << "after find(14):\n";

    ds.prints();

    return 0;
}