//
// Created by 涂金戈 on 31/10/2016.
//

#include <iostream>
#include <ctime>
#include <cstdlib>

void PrintPermutation(const int * a, int N) {
    std::cout << "[ ";

    for (int i = 0; i < N - 1; ++i)
        std::cout << a[i] << ", ";

    std::cout << a[N - 1] << " ]\n";
}

int* Permutation1 (int N) {
    std::cout << "Alg1. permutate " << N << ".\n";
    int *a = new int[N], a_i, temp_a_i, j;

    clock_t start_clock, end_clock;
    start_clock = clock();
    a[0] = std::rand() % N + 1;
    for (a_i = 1; a_i < N; ++a_i) {
        while (true) {
            temp_a_i = std::rand() % N + 1;
            // check if in a[0, i - 1]
            for (j = 0; j < a_i; ++j) {
                if (temp_a_i == a[j])
                    break;
            }

            if (j == a_i) {
                a[a_i] = temp_a_i;
                break;
            }
            else
                continue;
        }
    }
    end_clock = clock();

    std::cout << "Consumed " << double(end_clock - start_clock) / CLOCKS_PER_SEC * 1e6 <<" us.\n";

    return a;
}

int* Permutation2 (int N) {
    std::cout << "Alg2. permutate " << N << ".\n";
    int *a = new int[N], a_i, temp_a_i, j;
    bool *used = new bool[N]{false};

    clock_t start_clock, end_clock;
    start_clock = clock();
    a[0] = std::rand() % N + 1;
    used[a[0] - 1] = true;
    for (a_i = 1; a_i < N; ++a_i) {
        while (true) {
            temp_a_i = std::rand() % N + 1;
            // check if in a[0, i - 1]
            if (used[temp_a_i - 1] == false) {
                a[a_i] = temp_a_i;
                used[temp_a_i - 1] = true;
                break;
            }
        }
    }
    end_clock = clock();

    std::cout << "Consumed " << double(end_clock - start_clock) / CLOCKS_PER_SEC * 1e6 <<" us.\n";

    return a;
}

int* Permutation3(int N) {
    std::cout << "Alg3. permutate " << N << ".\n";
    int *a = new int[N], a_i;

    clock_t start_clock, end_clock;
    start_clock = clock();
    for (a_i = 0; a_i < N; ++a_i)
        a[a_i] = a_i + 1;

    for (a_i = 0; a_i < N; ++a_i) {
        std::swap(a[a_i], a[std::rand() % (a_i + 1)]);
    }
    end_clock = clock();

    std::cout << "Consumed " << double(end_clock - start_clock) / CLOCKS_PER_SEC * 1e6 <<" us.\n";

    return a;
}

int main() {

    std::srand(std::time(0));

    int N = 20000;

    int *a;

    a = Permutation1(2000);
//    PrintPermutation(a, N);
    delete[] a;

    a = Permutation2(800000);
//    PrintPermutation(a, N);
    delete[] a;

    a = Permutation3(6400000);
//    PrintPermutation(a, N);
    delete[] a;

    return 0;
}