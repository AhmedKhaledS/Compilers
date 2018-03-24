//
// Created by ahmed on 24/03/18.
//

#ifndef LEXICAL_ANALYZER_TOKENIZER_H
#define LEXICAL_ANALYZER_TOKENIZER_H

#include "DFANode.h"
#include "State.h"
#include <vector>

class Tokenizer
{
    private:

    public:
        std::vector<std::string> tokenize(
                std::vector< std::vector< std::pair<DFANode, string> > > *dfa_graph);
};

#endif //LEXICAL_ANALYZER_TOKENIZER_H
