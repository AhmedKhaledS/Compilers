//
// Created by ahmed on 24/04/18.
//

#ifndef COMPILERS_PARSERCONTROLLER_H
#define COMPILERS_PARSERCONTROLLER_H

#include <string>
#include <vector>
#include <map>
#include "NonTerminal.h"

using namespace std;

class ParserController {

    public:

        vector<string> grammar_rules;

        vector<string> terminals;
        vector<string> non_terminals;

        map<string, NonTerminal*> non_terminals_classes;


        void construct_grammar();
        void construct_non_terminals();
        void construct_terminals();
        void construct_non_terminals_classes();
        void construct_productions();
        void construct_follow_helper();


        void run_parser ();


        void add_grammar_rule (string grammar_rule);
        void add_terminal (string terminal);
        void add_non_terminal (string non_terminal);

        bool is_terminal(string token);
        bool is_epsilon(string token);
        bool is_non_terminal(NonTerminal nonTerminal);


        void print_productions();
        void print_follow_helper();
        void print_current_follow_helper(string non_terminal);

};


#endif //COMPILERS_PARSERCONTROLLER_H