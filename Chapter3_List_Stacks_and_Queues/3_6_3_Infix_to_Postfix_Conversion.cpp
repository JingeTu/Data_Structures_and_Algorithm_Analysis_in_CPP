//
// Created by 涂金戈 on 29/10/2016.
//
/*
6*(5+(2+3)*8+3)
 */

#include <iostream>
#include "Stack.h"

using namespace std;

int PrecedenceLevel(const char & oper) {
    int level;
    switch (oper) {
        case '+':
            level = 0;
            break;
        case '-':
            level = 0;
            break;
        case '*':
            level = 1;
            break;
        case '/':
            level = 1;
            break;
        case '(':
            level = 2;
            break;
        case ')':
            level = 3;
            break;
        default:
            level = -1;
            break;
    }
    return level;
}

int main() {
    Stack<char> operator_stack;

    char infix[256];
    cin >> infix;

    size_t infix_len = strlen(infix), postfix_len;

    char postfix[256], top_operator;
    int level;

    size_t infix_i, postfix_i;

    for (infix_i = 0, postfix_i = 0; infix_i < infix_len; ++infix_i) {
        level = PrecedenceLevel(infix[infix_i]);
        if (level == -1) { // operand
            postfix[postfix_i++] = infix[infix_i];
        }
        else { // operator
            if (level == 3) { // )
                top_operator = operator_stack.top();
                while (top_operator != '(' && operator_stack.size() != 0) {
                    operator_stack.pop_back();
                    postfix[postfix_i++] = top_operator;
                    if (operator_stack.size() == 0) break;
                    top_operator = operator_stack.top();
                }
                operator_stack.pop_back(); // pop_back (
            }
            else if (level == 2) { // (
                operator_stack.push_back(infix[infix_i]);
            }
            else if (level == 1 || level == 0) { // + - * /
                // check if top operator is higher
                if (operator_stack.size() != 0) {
                    top_operator = operator_stack.top();
                    if (PrecedenceLevel(top_operator) <= level) {
                        operator_stack.push_back(infix[infix_i]);
                    }
                    else {
                        while (PrecedenceLevel(top_operator) >= level && top_operator != '(') {
                            operator_stack.pop_back();
                            postfix[postfix_i++] = top_operator;
                            if (operator_stack.size() == 0) break;
                            top_operator = operator_stack.top();
                        }
                        operator_stack.push_back(infix[infix_i]);
                    }
                }
                else {
                    operator_stack.push_back(infix[infix_i]);
                }

            }
        }
    }

    top_operator = operator_stack.top();
    while (operator_stack.size() != 0) {
        postfix[postfix_i++] = top_operator;
        operator_stack.pop_back();
        if (operator_stack.size() == 0) break;
        top_operator = operator_stack.top();
    }
    cout << postfix << "\n";

    Stack<int> cal_stack;
    postfix_len = strlen(postfix);
    int r_operand, l_operand, rl_result;
    // check if any non-number
    // store postfix in Stack first
    for (postfix_i = 0; postfix_i < postfix_len; ++postfix_i) {
        level = PrecedenceLevel(postfix[postfix_i]);
        if (level == -1) { // is a number
            cal_stack.push_back(postfix[postfix_i] - '0');
        }
        else { // is not a number
            r_operand = cal_stack.top();
            cal_stack.pop_back();
            l_operand = cal_stack.top();
            cal_stack.pop_back();
            switch (postfix[postfix_i]) {
                case '+':
                    rl_result = l_operand + r_operand;
                    break;
                case '-':
                    rl_result = l_operand - r_operand;
                    break;
                case '*':
                    rl_result = l_operand * r_operand;
                    break;
                case '/':
                    rl_result = l_operand / r_operand;
                    break;
            }
            cal_stack.push_back(rl_result);
        }
    }

    cout << cal_stack.top() << "\n";


    return 0;
}