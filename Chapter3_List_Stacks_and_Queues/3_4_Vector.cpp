//
// Created by 涂金戈 on 31/10/2016.
//

#include "Vector.h"
#include <iostream>

using namespace std;

int main() {

    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);

    Vector<int>::iterator it = v.begin();
    while (it != v.end()) {
        cout << " " << *it;
        ++it;
    }
    cout << endl;
    cout << v.size() << "/" << v.capacity() << endl;

    return 0;
}