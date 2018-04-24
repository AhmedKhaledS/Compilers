//
// Created by ahmed on 24/04/18.
//

#include "ParserController.h"

#include <iostream>

void ParserController::run_parser() {

    // 1. Reading the grammar line by line
    add_grammar("A = B C | X Y");
    add_grammar("B = \\L | X Y");
    add_grammar("C = B C | X Y");

    for (int i = 0; i < grammar_rules.size(); ++i) {
        cout << grammar_rules[i] << endl;
    }


    // 2. Getting terminals and non-terminals

    //  3. Create classes non terminals
        // productions .. follow_helper..

    // call first .. follow

    // call construct table

    // simulate stack and o/p

}

void ParserController::add_grammar(string grammar_rule) {
    grammar_rules.push_back(grammar_rule);
}

void ParserController::add_terminal(string terminal) {
    terminals.push_back(terminal);
}

void ParserController::add_non_terminal(string non_terminal) {
    non_terminals.push_back(non_terminal);
}