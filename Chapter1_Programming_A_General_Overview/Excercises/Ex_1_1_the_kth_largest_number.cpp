//
// Created by 涂金戈 on 30/10/2016.
//

#include <iostream>
#include <cstdlib>
#include <ctime>

template <typename Comparable>
const Comparable & ThekthLargestNumber(const Comparable * numbers, size_t N, size_t k) {
    int i, j, N_i, k_i;

    Comparable coming_number;

    Comparable *k_numbers = new Comparable[k], kth_number;

    for (i = 0; i < k; ++i) {
        k_numbers[i] = numbers[i];
    }

    for (i = 0; i < k - 1; ++i) {
        for (j = i + 1; j < k; ++j) {
            if (k_numbers[i] < k_numbers[j]) {
                std::swap(k_numbers[i], k_numbers[j]);
            }
        }
    }

    for (N_i = k; N_i < N; ++N_i) {
        coming_number = numbers[N_i];
        // insert to the right position
        for (k_i = 0; k_i < k; ++k_i) {
            if (coming_number > k_numbers[k_i]) { // insert to the position i
                for (i = k - 1; i > k_i; --i) {
                    k_numbers[i] = k_numbers[i - 1];
                }
                k_numbers[i] = coming_number;
                break;
            }
        }
    }

    coming_number = k_numbers[k - 1];
    delete[] k_numbers;
    return coming_number;
}

int main() {
    size_t N, i;
    std::cin >> N;

    size_t k = N / 2;

    int *numbers = new int[N];

    std::srand(std::time(0));
    for (i = 0; i < N; ++i) {
        numbers[i] = std::rand();
    }

    std::cout << "The " << k << "th largest number is " << ThekthLargestNumber(numbers, N, k) << "\n";

    std::sort(numbers, numbers + N, std::greater<int>());

    std::cout << "All Sort result:\n";
    for (i = 0; i < N; ++i) {
        std::cout << i + 1 << "th \t:\t" << numbers[i] << ((i + 1 == k) ? " <-" : "") << "\n";
    }

    delete[] numbers;
    return 0;
}