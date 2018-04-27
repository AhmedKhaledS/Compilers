//
// Created by ahmed on 4/24/18.
//

#ifndef COMPILERS_PARSERSTACK_H
#define COMPILERS_PARSERSTACK_H

#include "ParserTable.h"
#include "../lexical_analyzer/LexicalController.h"
#include <stack>
using namespace std ;

enum ERROR_ROUTINE {Synch , Panic , Reject , Correct};

class ParserStack{

private:

    stack<string> input_parsing_stack ;
    ParserTable predictive_parse_table ;
    string initial_parse_state ;
    void match_next(string input);
    void error_logger(ERROR_ROUTINE err);

public:
    ParserStack(ParserTable table , string initial_state);
    void run_string_matcher(Lexical_controller input);

};

#endif //COMPILERS_PARSERSTACK_H
