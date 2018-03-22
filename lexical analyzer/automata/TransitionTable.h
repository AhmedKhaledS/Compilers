//
// Created by ahmed on 22/03/18.
//

#ifndef LEXICAL_ANALYZER_TRANSITIONTABLE_H
#define LEXICAL_ANALYZER_TRANSITIONTABLE_H

#include <vector>
#include <map>
#include <utility>
#include "DFANode.h"

class TransitionTable
{
    private:
        std::map< std::pair<int, char>, DFANode> t_table;
        std::vector<DFANode> d_states;

    public:
        TransitionTable();
        void add(DFANode node, char input, DFANode entry_node);
        DFANode get_entry(DFANode dfa_node, char input);
        bool search(DFANode node);
};


#endif //LEXICAL_ANALYZER_TRANSITIONTABLE_H
