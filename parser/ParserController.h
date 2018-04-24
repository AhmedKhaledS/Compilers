//
// Created by ahmed on 24/04/18.
//

#ifndef COMPILERS_PARSERCONTROLLER_H
#define COMPILERS_PARSERCONTROLLER_H

#include <string>
#include <vector>

using namespace std;

class ParserController {

    public:

        vector<string> grammar_rules;
        vector<string> terminals;
        vector<string> non_terminals;

        void run_parser ();

        void add_grammar (string grammar_rule);
        void add_terminal (string terminal);
        void add_non_terminal (string non_terminal);


};


#endif //COMPILERS_PARSERCONTROLLER_H
