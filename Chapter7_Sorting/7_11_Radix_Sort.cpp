//
// Created by 涂金戈 on 14/11/2016.
//

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "../Common_Tools/permutation.h"

void radixSortA(std::vector<std::string> &arr, int stringLen) {
    const int BUCKETS = 256;
    std::vector<std::vector<std::string>> buckets(BUCKETS);
    int i, j;

    for (i = stringLen - 1; i >= 0; --i) {
        for (auto &str : arr)
            buckets[str[i]].push_back(str);

        j = 0;
        for (auto &thisBucket : buckets) {
            for (auto &str : thisBucket)
                arr[j++] = std::move(str);
            thisBucket.clear();
        }
    }
}

void countingRadixSort(std::vector<std::string> &arr, int stringLen) {
    const int BUCKETS = 256;

    int N = arr.size(), i;
    std::vector<std::string> buffer(N);

    std::vector<std::string> *in = &arr;
    std::vector<std::string> *out = &buffer;

    for (int pos = stringLen - 1; pos >= 0; --pos) {
        std::vector<int> count(BUCKETS + 1);

        for (auto &str : (*in))
            ++count[str[pos] + 1];

        for (i = 1; i <= BUCKETS; ++i)
            count[i] += count[i - 1];

        for (i = 0; i < N; ++i)
            (*out)[count[(*in)[i][pos]]++] = std::move((*in)[i]);

        std::swap(in, out);
    }

    if (stringLen % 2 == 1)
        for (i = 0; i < N; ++i)
            arr[i] = std::move(buffer[i]);
}

void radixSort(std::vector<std::string> &arr, int maxLen) {
    const int BUCKETS = 256;

    std::vector<std::vector<std::string>> wordsByLength(maxLen + 1);
    std::vector<std::vector<std::string>> buckets(BUCKETS);

    for (std::string &s : arr)
        wordsByLength[s.length()].push_back(std::move(s));

    int idx = 0, i, pos;
    for (auto &wordList : wordsByLength)
        for (std::string &s : wordList)
            arr[idx++] = std::move(s);

    int startingIndex = arr.size();
    for (pos = maxLen - 1; pos >= 0; --pos) {
        startingIndex -= wordsByLength[pos + 1].size();

        for (i = startingIndex; i < arr.size(); ++i)
            buckets[arr[i][pos]].push_back(std::move(arr[i]));

        idx = startingIndex;
        for (auto &thisBucket : buckets) {
            for (std::string &s : thisBucket)
                arr[idx++] = std::move(s);

            thisBucket.clear();
        }
    }
}

void radixSortVariableLength(std::vector<std::string> &arr, int maxLen) {
    const int BUCKETS = 256;

    std::vector<std::vector<std::string>> wordsByLength(maxLen + 1);
    std::vector<std::vector<std::string>> buckets(BUCKETS);

    for (std::string &s : arr)
        wordsByLength[s.length()].push_back(std::move(s));

    int idx = 0;
    for (auto &wordList : wordsByLength)
        for (std::string &s : wordList)
            arr[idx++] = std::move(s);

    int startingIndex = arr.size();
    for (int pos = maxLen - 1; pos >= 0; --pos) {
        startingIndex -= wordsByLength[pos + 1].size();

        for (int i = startingIndex; i < arr.size(); ++i)
            buckets[arr[i][pos]].push_back(std::move(arr[i]));

        idx = startingIndex;
        for (auto &thisBucket : buckets) {
            for (std::string &s : thisBucket)
                arr[idx++] = std::move(s);

            thisBucket.clear();
        }
    }
}

void permute(const std::string &str, int low, int high, std::vector<std::string> &permuteStrings) {

    int i;
    std::string cpy_str = str;

    if (low == high) {
        permuteStrings.push_back(str);
    }

    for (i = low; i <= high; ++i) {
        std::swap(cpy_str[i], cpy_str[low]);
        permute(cpy_str, low + 1, high, permuteStrings);
        std::swap(cpy_str[low], cpy_str[i]); // swap back to the original string and move into next iteration
    }
}

void permute(const std::string &str, std::vector<std::string> &permuteStrings) {
    permute(str, 0, str.size() - 1, permuteStrings);
}

int main(int argc, char *argv[]) {

    std::vector<std::string> per_vec;
    permute("today", per_vec);

    std::srand(std::time(0));
    int *nums = Permutation3(per_vec.size());
    int i;

    std::vector<std::string> copy_vec(per_vec);
    for (i = 0; i < per_vec.size(); ++i) {
        per_vec[i] = std::move(copy_vec[nums[i] - 1]);
    }

//    radixSortA(per_vec, 5);
//    countingRadixSort(per_vec, 5);
    radixSort(per_vec, 5);

    for (i = 0; i < per_vec.size(); ++i) {
        std::cout << per_vec[i] << "\n";
    }

    delete[] nums;

    std::stringstream ss_file_name;
    ss_file_name << argv[1] << '/' << "Chapter4_Trees/corncob_lowercase.txt";

    std::vector <std::string> words;
    std::ifstream in_file;

    in_file.open(ss_file_name.str());

    if (!in_file.is_open()) {
        std::cout << "Open File failed.\n";
        return 1;
    }

    std::string word;
    int maxLen = 0;
    while (!in_file.eof()) {
        in_file >> word;
        if (word.length() > maxLen)
            maxLen = word.length();
        words.push_back(word);
    }

    in_file.close();

    radixSortVariableLength(words, maxLen);

    return 0;
}