//
// Created by 涂金戈 on 31/10/2016.
//

#include <iostream>

void permute(const std::string & str, int low, int high) {

    int i;
    std::string cpy_str = str;

    if (low == high) {
        std::cout << str << "\n";
    }

    for (i = low; i <= high; ++i) {
        std::swap(cpy_str[i], cpy_str[low]);
        permute(cpy_str, low + 1, high);
        std::swap(cpy_str[low], cpy_str[i]); // swap back to the original string and move into next iteration
    }
}

void permute(const std::string & str) {
    permute(str, 0, str.size() - 1);
}

int main() {
    std::string str = "wos";
    permute(str);

    return 0;
}