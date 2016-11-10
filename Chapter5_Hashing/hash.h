//
// Created by 涂金戈 on 09/11/2016.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_HASH_H
#define DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_HASH_H


// function template
template<typename Key>
class hash {
public:
    size_t operator()(const Key &k) const;
};

template<>
class hash<std::string> {
public:
    size_t operator()(const std::string &Key) {
        size_t hashVal = 0;
        for (char ch : Key)
            hashVal = 37 * hashVal + ch;
        return hashVal;
    }
};

template<>
class hash<int> {
public:
    size_t operator()(const int &Key) {
        size_t hashVal = Key;
        return hashVal;
    }
};

template<typename Key>
class hash2 {
public:
    int operator()(const Key &k) const;
};

template<>
class hash2<std::string> {
public:
    int operator()(const std::string &Key) {
        int hashVal = 0;

        for (char ch : Key)
            hashVal += ch;

        return 7 - (hashVal % 7);
    }
};

#include "hash.cpp"

#endif //DATA_STRUCTURES_AND_ALGORITHM_ANALYSIS_IN_CPP_HASH_H
