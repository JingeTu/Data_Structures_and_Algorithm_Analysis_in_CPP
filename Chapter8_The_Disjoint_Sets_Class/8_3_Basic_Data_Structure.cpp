//
// Created by 涂金戈 on 22/11/2016.
//

#include <iostream>
#include <vector>


class DisjSets {
public:
    explicit DisjSets(int numElements);

    int find(int x) const;

    void unionSets(int root1, int root2);

    void prints();

private:
    std::vector<int> s;
};

DisjSets::DisjSets(int numElements) : s(numElements, -1) {}

void DisjSets::unionSets(int root1, int root2) {
    s[root2] = root1;
}

int DisjSets::find(int x) const {
    if (s[x] < 0)
        return x;
    else
        return find(s[x]);
}

void DisjSets::prints() {
    for (int i = 0; i < s.size(); ++i)
        std::cout << "i: " << i << "\tvalue: " << s[i] << std::endl;
}

int main() {

    DisjSets ds(8);

    ds.unionSets(4, 5);
    ds.unionSets(6, 7);
    ds.unionSets(4, 6);

    ds.prints();

    return 0;
}