//
// Created by 涂金戈 on 30/10/2016.
//

#include <iostream>

#define PUZZLE_HEIGHT 4
#define PUZZLE_WIDTH 4
#define WORD_LIST_LENGTH 4
#define WORD_MAX_LENGTH 4

struct CaseTuple {
    int start_row_num;
    int start_col_num;
    int orientation_x;
    int orientation_y;
    CaseTuple(int start_row_Num, int start_col_Num, int orientation_X, int orientation_Y) :
            start_row_num(start_row_Num), start_col_num(start_col_Num), orientation_x(orientation_X), orientation_y(orientation_Y) {}

};

int CheckPuzzle(const char puzzle[PUZZLE_HEIGHT][PUZZLE_WIDTH], const CaseTuple & case_tuple, const char word_list[WORD_LIST_LENGTH][WORD_MAX_LENGTH + 1],
                 const int & word_max_length) {
    int function_final_result = -1;
    int i, j;
    char searched_word[word_max_length];
    int row_num, col_num, searched_word_length;

    for (i = 0; i < word_max_length; ++i) {
        row_num = case_tuple.start_row_num + i * case_tuple.orientation_y;
        col_num = case_tuple.start_col_num + i * case_tuple.orientation_x;
        if (row_num < 0 || row_num > PUZZLE_HEIGHT - 1 || col_num < 0 || col_num > PUZZLE_WIDTH - 1) {
            break;
        }
        else {
            searched_word[i] = puzzle[row_num][col_num];
        }
    }
    searched_word_length = i;

    for (i = 0; i < WORD_LIST_LENGTH; ++i) {
        if (searched_word_length < strlen(word_list[i])) {
            continue;
        }
        else {
            for (j = 0; j < strlen(word_list[i]); ++j) {
                if (word_list[i][j] != searched_word[j]) {
                    break;
                }
                if (j == strlen(word_list[i]) - 1) {
                    function_final_result = i;
                }
            }
        }
    }

    return function_final_result;
}

int main() {
//    const static int PUZZLE_HEIGHT = 4;
//    const static int PUZZLE_WIDTH = 4;
//    const static int WORD_LIST_LENGTH = 4;
//    const static int WORD_MAX_LENGTH = 4;

    int row_i, col_i, x_i, y_i, word_max_length, check_result;

    char puzzle[PUZZLE_HEIGHT][PUZZLE_WIDTH] = {{'t', 'h', 'i', 's'},
                                                {'w', 'a', 't', 's'},
                                                {'o', 'a', 'h', 'h'},
                                                {'f', 'g', 'd', 't'}};

    char word_list[WORD_LIST_LENGTH][WORD_MAX_LENGTH + 1] = {"this", "two", "fat", "that"};

    word_max_length = strlen(word_list[0]);
    for (row_i = 1; row_i < WORD_LIST_LENGTH; ++row_i) {
        if (strlen(word_list[row_i]) > word_max_length) {
            word_max_length = strlen(word_list[row_i]);
        }
    }

    for (row_i = 0; row_i < PUZZLE_HEIGHT; ++row_i) {
        for (col_i = 0; col_i < PUZZLE_WIDTH; ++col_i) {
            for (x_i = -1; x_i <= 1; ++x_i) {
                for (y_i = -1; y_i <= 1; ++y_i) {
                    check_result = CheckPuzzle(puzzle, CaseTuple(row_i, col_i, x_i, y_i), word_list, word_max_length);
                    if (check_result != -1) {
                        std::cout << "Find word \'" << word_list[check_result] << "\' in (" << row_i << ", " << col_i << ", " << x_i << ", " << y_i << "). \n";
                    }
                }
            }
        }
    }

    printDigit(4);

    return 0;
}