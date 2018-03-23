//
// Created by ahmed on 16/03/18.
//

#include "NFAGenerator.h"
#include "NFAOperations.h"

#include <regex>

#include <iostream>
#include "Helper.h"

#define EMPTY_OPERAND ""
#define EXPRSSION "(.)*=(.)*"
#define KEY_WORDS "\\[(.)*\\]"
#define PUNCS "\\{(.)*\\}"

#define EPSILON '$'

NFAGenerator::NFAGenerator()
{

}

bool is_type(string a, string regex_value) {

    regex b(regex_value);

    return  regex_match(a, b);
}

void NFAGenerator::generate_grammar(string expression) {

    string expanded_version = "";

    // 1. Expand Classes
    Helper helper;
    expanded_version = helper.normalize_classes(expression);

    cout << "HELLO: " << expanded_version << endl;

    // 2. Find Type
    if(is_type(expanded_version, KEY_WORDS)) {
        cout << "KEY_WORDS" << endl;

    } else if(is_type(expanded_version, PUNCS)) {
        cout << "PUNCS" << endl;

    } else if (is_type(expanded_version, EXPRSSION)) {

        cout << "EXPRSSION" << endl;

        std::stringstream test(expanded_version);
        std::string segment;
        std::vector<std::string> tokens;

        while(std::getline(test, segment, '='))
        {
            tokens.push_back(segment);
        }

        NFA result = RE_to_NFA(tokens[1]);

        grammar.push_back(result);

    } else {
        cout << "DEFINITION" << endl;

    }
}

NFA NFAGenerator::generate_machine() {

    NFAOperations helper;
    NFA result;
    result = helper.oring_all(grammar);
    return result;
}

void NFAGenerator::handle_assignment()
{

}

bool NFAGenerator::is_operation(char c)
{
    return c == '(' || c == ')' || c == '.' || c == '|' || c == '*';
}

void NFAGenerator::perform_operation(stack<NFA>& operands, stack<char>& operations)
{
    NFAOperations nfa_operation;

    char operation = operations.top();
    operations.pop();
    NFA x = operands.top();
    operands.pop();
    NFA y = operands.top();
    operands.pop();

    switch (operation) {
        case ('|'):
            operands.push(nfa_operation.oring(y, x));
            break;
        case ('.'):
            operands.push(nfa_operation.concatenating(y, x));
            break;
    }
}

NFA NFAGenerator::RE_to_NFA(string expression)
{

    NFAOperations nfa_operation;

    stack<NFA> operands;
    stack<char> operations;
    string operand = EMPTY_OPERAND;

    for (unsigned int i = 0; i < expression.length(); i++) {

        if (!is_operation(expression[i])) {
            /// TO BE EDITED: Operand collection depends on context
            operand += expression[i];
        }
        else {

            if (operand != EMPTY_OPERAND) {
                /// TO BE EDITED: Adding a hash map for predefined operands
                operands.push(nfa_operation.create_NFA(operand[0]));
                operand = EMPTY_OPERAND;
            }

            if (expression[i] == '(') {

                operations.push(expression[i]);
            }
            else if (expression[i] == ')') {

                while (operations.top() != '(') {
                    perform_operation(operands, operations);
                }
                operations.pop();
            }
            else if (expression[i] == '*') {

                NFA x = operands.top();
                operands.pop();
                operands.push(nfa_operation.kleene_closuring(x));
            }
            else {
                if (operations.size() != 0) {
                    if(expression[i] == '|') {
                        while (operations.size() > 0 && operations.top() == '.') {
                            perform_operation(operands, operations);
                        }
                    } else {
                        while (operations.size() > 0) {
                            perform_operation(operands, operations);
                        }
                    }
                }
                operations.push(expression[i]);
            }
        }
    }

    if (operand != EMPTY_OPERAND) {
        operands.push(nfa_operation.create_NFA(operand[0]));
        operand = EMPTY_OPERAND;
    }

    while (operations.size() != 0) {
        perform_operation(operands, operations);
    }

    return operands.top();
}