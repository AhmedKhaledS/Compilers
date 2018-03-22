//
// Created by ahmed on 16/03/18.
//

#ifndef LEXICAL_ANALYZER_NFAGENERATOR_H
#define LEXICAL_ANALYZER_NFAGENERATOR_H

#include "NFA.h"
#include <stack>
#include <string>

class NFAGenerator
{
    public:
        NFAGenerator();

        void handle_assignment();

        bool is_operation(char c);

        void perform_operation(stack<NFA>& operands, stack<char>& operations);

        NFA RE_to_NFA(string expression);

protected:
private:
};


#endif //LEXICAL_ANALYZER_NFAGENERATOR_H
