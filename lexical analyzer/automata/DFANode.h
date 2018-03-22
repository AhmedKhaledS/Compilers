//
// Created by ahmed on 22/03/18.
//

#ifndef LEXICAL_ANALYZER_DFANODE_H
#define LEXICAL_ANALYZER_DFANODE_H

#include <vector>
#include "State.h"

class DFANode
{
    public:
        std::vector<State> dfa_state;
        /* Identifying whether it's an acceptance state or not. */
        bool acceptance_state;
        /* Marking is responsible for termination of NFA to DFA Transformation. */
        bool marked;
        /* Detects whether this node is in the transition table or not. */
        bool registered_in_transition_table;
        /* Every DFANode has a unique integer id. */
        int id;

        DFANode(std::vector<State> dfa_state_, bool acc_state, bool marked, bool reg_in_t_table, int id);
};


#endif //LEXICAL_ANALYZER_DFANODE_H
