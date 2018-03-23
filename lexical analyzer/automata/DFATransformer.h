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
        int functional_id;
        std::map<int, DFANode*> id_to_node;
        std::vector<int> parent;
        int find_parent(int node);
        bool merge_nodes(int node1, int node2);
        std::vector<DFANode> dfa_nodes;
        bool already_inserted(std::vector<State> vec, State s);

    public:
        DFATransformer();
        DFANode normal_transition(DFANode *dfa_state, char input);
        std::vector< std::vector<std::pair <DFANode, char> > > transform(std::vector<State> nfa_graph);
        DFANode* get_dfa_node(int id);
        void add_dfa_node(DFANode *node, int id);
        std::vector<DFANode>* get_dfa_nodes();
};
#endif //LEXICAL_ANALYZER_DFATRANSFORMER_H
