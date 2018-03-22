//
// Created by ahmed on 16/03/18.
//

#ifndef LEXICAL_ANALYZER_DFATRANSFORMER_H
#define LEXICAL_ANALYZER_DFATRANSFORMER_H

#include <vector>
#include <map>
#include "DFANode.h"
#include "TransitionTable.h"

class DFATransformer
{

    private:
        std::map<int, DFANode*> id_to_node;


    public:
        DFATransformer();
        std::vector< std::vector<DFANode> > transform(std::vector<Transition> nfa_graph);
        DFANode* get_dfa_node(int id);
};
#endif //LEXICAL_ANALYZER_DFATRANSFORMER_H
