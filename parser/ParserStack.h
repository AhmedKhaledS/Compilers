//
// Created by ahmed on 4/24/18.
//

#ifndef COMPILERS_PARSERSTACK_H
#define COMPILERS_PARSERSTACK_H

#include "ParserTable.h"
#include "../lexical_analyzer/LexicalController.h"
#include <stack>
using namespace std ;

enum ERROR_ROUTINE {Synch , Missing , Reject};

class ParserStack{

private:
    NonTerminal empty;
    stack<pair<NonTerminal*, string>> input_parsing_stack;
    ParserTable predictive_parse_table ;
    pair<NonTerminal*, string> initial_parse_state ;
    vector<string> left_most_derivation;
    void initialize_stack();
    void error_logger(ERROR_ROUTINE err);
    void print_stack();
public:

    ParserStack(ParserTable table, pair<NonTerminal*, string> initial_state);
    void match_tokens(string current_token, Lexical_controller *input);

};

#endif //COMPILERS_PARSERSTACK_H
