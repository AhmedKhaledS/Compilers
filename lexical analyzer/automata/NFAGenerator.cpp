//
// Created by ahmed on 16/03/18.
//

#include "NFAGenerator.h"
#include "NFAOperations.h"

#include <regex>

#include <iostream>
#include "Helper.h"

#define EXPRSSION "(.)*:(.)*"
#define PUNCS "\\[(.)*\\]"
#define KEY_WORDS "\\{(.)*\\}"
#define EMPTY_OPERAND ""


#define EPSILON '$'

set <char> NFAGenerator::symbols;

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
        cout << "--KEY_WORDS" << endl;
        string key_words = expanded_version.substr(1,expanded_version.length() - 2);
        cout << "--KEY_WORDS:" << key_words << endl;
        std::vector<std::string> tokens =
                helper.tokenaize(key_words, ' ');
        for (int i = 0; i < tokens.size(); ++i) {
            if(tokens[i] == "") continue;
            tokens[i] = helper.insert_concatination(tokens[i]);
            cout << i << "K:" << tokens[i] << endl;
            NFA result = RE_to_NFA(tokens[i]);
            grammar.push_back(result);
        }

    } else if(is_type(expanded_version, PUNCS)) {
        cout << "--PUNCS" << endl;
        string puncs_1 = expanded_version.substr(1,expanded_version.length() - 2);
        cout << "--PUNCS#" << puncs_1 << endl;



        std::vector<std::string> tokens =
                helper.tokenaize(puncs_1, ' ');
        for (int i = 0; i < tokens.size(); ++i) {
            if(tokens[i] == "") continue;
            // tokens[i] = helper.insert_concatination(tokens[i]);
            cout << i << "P#" << tokens[i] << "#" << endl;
            NFA result = RE_to_NFA(tokens[i]);
            grammar.push_back(result);
        }


    } else if (is_type(expanded_version, EXPRSSION)) {

        cout << "EXPRSSION" << endl;


        std::vector<std::string> tokens = helper.tokenaize(expanded_version, ':');

        NFA result = RE_to_NFA(tokens[1]);
        grammar.push_back(result);

    } else {
        cout << "-- DEFINITION" << endl;

        std::vector<std::string> tokens = helper.tokenaize(expanded_version, '=');

        NFA result = RE_to_NFA(tokens[1]);
        nfa_pool.push_back(result);
        defined_grammar[tokens[0]] = nfa_pool[nfa_pool.size()-1];

        cout << "-- " << tokens[0] << " pushed to map as " << tokens[1] << endl;
    }
}

NFA NFAGenerator::generate_machine() {

    NFAOperations helper;
    NFA result;
    result = helper.oring_all(grammar);
    return result;
}

bool NFAGenerator::is_operation(char c)
{
    return c == '(' || c == ')' || c == '@' || c == '|' || c == '*' || c == '+';
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
        case ('@'):
            operands.push(nfa_operation.concatenating(y, x));
            break;
    }
}


void NFAGenerator::add_operand(stack<NFA>& operands, stack<char>& operations,
                               string operand, bool duplicate)
{
    NFAOperations nfa_operation;

    if(duplicate == true) {
        while (operations.size() > 0 && operations.top() == '@') {
            perform_operation(operands, operations);
        }
        operations.push('@');
    }

    if(operand.length() == 1) {
        if(operand[0] == 'L')   {
            operands.push(nfa_operation.create_NFA('$'));
        } else {
            operands.push(nfa_operation.create_NFA(operand[0]));
        }
    } else {
            cout << "HASH MAP" << endl;
            cout << "HM:" << operand << endl;
            operands.push(defined_grammar[operand]);
    }

}

NFA NFAGenerator::RE_to_NFA(string expression)
{

    NFAOperations nfa_operation;

    stack<NFA> operands;
    stack<char> operations;
    string operand = EMPTY_OPERAND;

    bool consecutive_tokens = false;

    for (unsigned int i = 0; i < expression.length(); i++) {

        if(expression[i] == ' ') {
            if(operand != EMPTY_OPERAND) {
                add_operand(operands,operations,operand,consecutive_tokens);
                operand = EMPTY_OPERAND;
                consecutive_tokens = true;
            }
            continue;
        }

        if(expression[i] == '\\') {

            if(operand != EMPTY_OPERAND) {
                add_operand(operands,operations,operand,consecutive_tokens);
                operand = EMPTY_OPERAND;
                consecutive_tokens = true;
            }

            i++;
            operand += expression[i];
            add_operand(operands,operations,operand,consecutive_tokens);
            operand = EMPTY_OPERAND;
            consecutive_tokens = true;

        } else if (!is_operation(expression[i])) {
            operand += expression[i];
        }
        else {

            if (operand != EMPTY_OPERAND) {
                add_operand(operands,operations,operand,consecutive_tokens);
                operand = EMPTY_OPERAND;
            }



            if (expression[i] == '(') {

                ///EXTRA///
                if(consecutive_tokens == true) {
                    while (operations.size() > 0 && operations.top() == '@') {
                        perform_operation(operands, operations);
                    }
                    operations.push('@');
                }
                consecutive_tokens = false;



                operations.push(expression[i]);
            }
            else if (expression[i] == ')') {
                consecutive_tokens = false;


                while (operations.top() != '(') {
                    perform_operation(operands, operations);
                }
                operations.pop();
            }
            else if (expression[i] == '*' || expression[i] == '+') {
                consecutive_tokens = false;
                NFA x = operands.top();
                operands.pop();
                if(expression[i] == '*') {
                    operands.push(nfa_operation.kleene_closuring(x));
                } else {
                    operands.push(nfa_operation.positive_closuring(x));
                }
            }
            else {
                consecutive_tokens = false;
                if (operations.size() != 0) {
                    if(expression[i] == '|') {
                        while (operations.size() > 0 && operations.top() == '@') {
                            perform_operation(operands, operations);
                        }
                    } else {
                        while (operations.size() > 0 && operations.top() == '@') {
                            perform_operation(operands, operations);
                        }
                    }
                }
                operations.push(expression[i]);
            }
        }
    }

    if (operand != EMPTY_OPERAND) {
        add_operand(operands,operations,operand,consecutive_tokens);
        operand = EMPTY_OPERAND;
    }

    while (operations.size() != 0) {
        perform_operation(operands, operations);
    }

    return operands.top();
}

void NFAGenerator::add_symbol(char s) {
    symbols.insert(s);
}

set <char> NFAGenerator::get_symbols() {
    return symbols;
}
