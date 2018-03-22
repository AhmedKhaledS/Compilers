//
// Created by ahmed on 16/03/18.
//

#include "NFAGenerator.h"
#include "NFAOperations.h"

#define EMPTY_OPERAND ""

NFAGenerator::NFAGenerator()
{

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
                if (operations.size() != 0 && expression[i] != '.') {
                    while (operations.size() > 0 && operations.top() == '.') {
                        perform_operation(operands, operations);
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