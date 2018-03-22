//
// Created by ahmed on 22/03/18.
//

#ifndef LEXICAL_ANALYZER_DFANODE_H
#define LEXICAL_ANALYZER_DFANODE_H

#include <vector>
//#include <Node>

class DFANode
{
    public:
        //std::vector<Node> dfa_state;

        /* Identifying whether it's an acceptance state or not. */
        bool acceptance_state;
        /* Marking is responsible for termination of NFA to DFA Transformation. */
        bool marked;
        bool registered_in_transition_table;
        /* Every DFANode has a unique integer id. */
        int id;
};


#endif //LEXICAL_ANALYZER_DFANODE_H
