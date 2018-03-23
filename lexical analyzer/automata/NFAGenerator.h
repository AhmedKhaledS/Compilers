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

class NFAGenerator
{
    public:
        NFAGenerator();

        void generate_grammar(string expression);

        NFA generate_machine();

        void handle_assignment();

        bool is_operation(char c);

        void perform_operation(stack<NFA>& operands, stack<char>& operations);

        NFA RE_to_NFA(string expression);

    protected:

    private:
        set <char , greater <char> > symbols;

        vector<NFA> grammar;

};


#endif //LEXICAL_ANALYZER_NFAGENERATOR_H
