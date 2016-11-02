//
// Created by 涂金戈 on 31/10/2016.
//

#include <iostream>

int main() {

    int N, count;
    std::cin >> N;

    count = 0;
    while (N > 0) {
        count += N % 2;
        N /= 2;
    }

    std::cout << count << std::endl;

    return 0;
}