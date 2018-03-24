//
// Created by ahmed on 16/03/18.
//

#ifndef LEXICAL_ANALYZER_DFATRANSFORMER_H
#define LEXICAL_ANALYZER_DFATRANSFORMER_H

#include <vector>
#include <map>
#include "DFANode.h"
#include "TransitionTable.h"
#include "NFAGenerator.h"

class DFATransformer
{

    private:
        int functional_id;
        std::map<int, DFANode*> id_to_node;
        std::vector<int> parent;
        std::vector<State> nfa_graph;
        std::vector<DFANode> dfa_nodes;
        std::vector< std::vector< std::pair<DFANode, string> > > dfa_graph;
        int find_parent(int node);
        bool merge_nodes(int node1, int node2);
        bool already_inserted(std::vector<State> *vec, State s);
        bool exist_unmarked_state(std::vector<DFANode> *dfa_combined_nodes);
        bool already_inserted_dfa_node(DFANode *dfa_node);
        DFANode *get_unmarked_node(std::vector<DFANode> *dfa_combined_nodes);
        DFANode *starting_dfa_state;
//        std::vector< std::map<char, std::vector<State> > > transitions;

public:
        DFATransformer();
        DFANode normal_transition(DFANode dfa_state, std::string input);
        void transform();
        DFANode* get_dfa_node(int id);
        void add_dfa_node(DFANode *node, int id);
        std::vector<DFANode>* get_dfa_nodes();
        void set_nfa_graph(std::vector<State> nfa);
        std::vector< std::vector< std::pair<DFANode, std::string> > > *get_dfa_graph();
        int get_dfa_graph_size();
        DFANode* get_starting_dfa_state();
};
#endif //LEXICAL_ANALYZER_DFATRANSFORMER_H
