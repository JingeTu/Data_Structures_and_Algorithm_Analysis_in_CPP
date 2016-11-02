//
// Created by 涂金戈 on 31/10/2016.
//

#include <vector>
using namespace std;

template <typename Object>
class matrix {
public:
    matrix(int rows = 0, int cols = 0): array(rows) {
        for (auto & thisRow: array)
            thisRow.resize(cols);
    }

    matrix(vector<vector<Object>> v): array{v} {}
    matrix(vector<vector<Object>> && v): array{std::move(v)} {}

    const vector<Object> &operator[] (int row) const {
        return array[row];
    }
    vector<Object> &operator[] (int row) {
        return array[row];
    }

    int numrows() const {
        return array.size();
    }
    int numcols() const {
        return numrows() ? array[0].size() : 0;
    }

    bool resize(int newrow, int newcol) {
        if (newrow < numrows() || newcol < numcols()) {
            return false;
        }

        array.resize(newrow);
        for (auto & thisRow: array)
            thisRow.resize(newcol);

        return true;
    }


private:
    vector<vector<Object>> array;
};