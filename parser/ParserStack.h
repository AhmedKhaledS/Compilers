//
// Created by ahmed on 4/24/18.
//

#ifndef COMPILERS_PARSERSTACK_H
#define COMPILERS_PARSERSTACK_H

#include "ParserTable.h"
#include <stack>

enum ERROR_ROUTINE {Synch , Panic , Reject , Correct};

class ParserStack{

private:

    std::stack<std::string> input_parsing_stack ;
    ParserTable predictive_parse_table ;
    void match_next(std::string input);
    void error_logger(ERROR_ROUTINE err);

public:
    ParserStack(ParserTable table ,
                std::string initial_state);
    void run_string_matcher();

};

#endif //COMPILERS_PARSERSTACK_H
