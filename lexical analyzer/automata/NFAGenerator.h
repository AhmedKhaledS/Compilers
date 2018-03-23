//
// Created by ahmed on 16/03/18.
//

#ifndef LEXICAL_ANALYZER_NFAGENERATOR_H
#define LEXICAL_ANALYZER_NFAGENERATOR_H

#include "NFA.h"
#include "State.h"
#include <stack>
#include <string>
#include <set>
#include <map>

class NFAGenerator
{
    public:
        NFAGenerator();

        void generate_grammar(string expression);

        NFA generate_machine();

        bool is_operation(char c);

        void perform_operation(stack<NFA>& operands, stack<char>& operations);

        void add_operand(stack<NFA>& operands, stack<char>& operations, string operand, bool duplicate);

        static void add_symbol(char s);

        static set <char> get_symbols();


    NFA RE_to_NFA(string expression);

    protected:

    private:
        NFA result;
        static set <char> symbols;
        vector<NFA> grammar;
        std::map<string, NFA*> defined_grammar;

};


#endif //LEXICAL_ANALYZER_NFAGENERATOR_H
