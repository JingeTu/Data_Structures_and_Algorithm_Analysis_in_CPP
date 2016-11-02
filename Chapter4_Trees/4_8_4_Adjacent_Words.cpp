//
// Created by 涂金戈 on 02/11/2016.
//

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

bool oneCharOff(const string & word1, const string & word2);

map<string, vector<string>> computeAdjacentWords1(const vector<string> & words);

map<string, vector<string>> computeAdjacentWords2(const vector<string> & words);

map<string, vector<string>> computeAdjacentWords3(const vector<string> & words);

bool oneCharOff(const string & word1, const string & word2) {
    if (word1.length() != word2.length())
        return false;

    int diffs = 0;

    for (int i = 0; i < word1.length(); ++i)
        if (word1[i] != word2[i])
            if (++diffs > 1)
                return false;

    return diffs == 1;
}

map<string, vector<string>> computeAdjacentWords1(const vector<string> & words) {
    clock_t start_clock, end_clock;

    cout << "Start Algorithm 1. \n";

    start_clock = clock();

    map<string, vector<string>> adjWords;

    for (int i = 0; i < words.size(); ++i)
        for (int j = i + 1; j < words.size(); ++j)
            if (oneCharOff(words[i], words[j])) {
                adjWords[words[i]].push_back(words[j]);
                adjWords[words[j]].push_back(words[i]);
            }

    end_clock = clock();

    cout << "End Algorithm 1, TIME elapsed: " << double(end_clock - start_clock) / CLOCKS_PER_SEC << "s\n";

    return adjWords;
}

map<string, vector<string>> computeAdjacentWords2(const vector<string> & words) {
    clock_t start_clock, end_clock;

    cout << "Start Algorithm 2. \n";

    start_clock = clock();

    map<string, vector<string>> adjWords;
    map<int, vector<string>> wordsByLength;

    for (auto & thisWord : words)
        wordsByLength[thisWord.length()].push_back(thisWord);

    for (auto & entry : wordsByLength) {
        const vector<string> & groupsWords = entry.second;

        for (int i = 0; i < groupsWords.size(); ++i)
            for (int j = i + 1; j < groupsWords.size(); ++j)
                if (oneCharOff(groupsWords[i], groupsWords[j])) {
                    adjWords[groupsWords[i]].push_back(groupsWords[j]);
                    adjWords[groupsWords[j]].push_back(groupsWords[i]);
                }
    }

    end_clock = clock();

    cout << "End Algorithm 2, TIME elapsed: " << double(end_clock - start_clock) / CLOCKS_PER_SEC << "s.\n";

    return adjWords;
}

map<string, vector<string>> computeAdjacentWords3(const vector<string> & words) {
    clock_t start_clock, end_clock;

    cout << "Start Algorithm 3. \n";

    start_clock = clock();

    map<string, vector<string>> adjWords;
    map<int, vector<string>> wordsByLength;

    for (auto & str : words)
        wordsByLength[str.length()].push_back(str);

    for (auto & entry : wordsByLength) {
        const vector<string> & groupsWords = entry.second;
        int groupNum = entry.first;

        for (int i = 0; i < groupNum; ++i) {
            map<string, vector<string>> repToWord;

            for (auto & str : groupsWords) {
                string rep = str;
                rep.erase(i, 1);
                repToWord[rep].push_back(str);
            }

            for (auto & entry : repToWord) {
                const vector<string> & clique = entry.second;
                if (clique.size() >= 2)
                    for (int p = 0; p < clique.size(); ++p)
                        for (int q = p + 1; q < clique.size(); ++q) {
                            adjWords[clique[p]].push_back(clique[q]);
                            adjWords[clique[q]].push_back(clique[p]);
                        }
            }
        }
    }

    end_clock = clock();

    cout << "End Algorithm 3, TIME elapsed: " << double(end_clock - start_clock) / CLOCKS_PER_SEC << "s.\n";

    return adjWords;
}

int main(int argc, char *argv[]) {
    stringstream ss_file_name;
    ss_file_name << argv[1] << '/' << "Chapter4_Trees/corncob_lowercase.txt";

    vector<string> words;
    ifstream in_file;

    in_file.open(ss_file_name.str());

    if (!in_file.is_open()) {
        cout << "Open File failed.\n";
        return 1;
    }

    string word;
    while (!in_file.eof()) {
        in_file >> word;
        words.push_back(word);
    }

    in_file.close();

    computeAdjacentWords1(words);

    computeAdjacentWords2(words);

    computeAdjacentWords3(words);

    return 0;
}