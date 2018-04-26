//
// Created by ahmed on 16/03/18.
//

#ifndef LEXICAL_ANALYZER_REDUCEDDFA_H
#define LEXICAL_ANALYZER_REDUCEDDFA_H

#include <vector>
#include <string>
#include "DFANode.h"
#include "DFATransformer.h"
#include "EdgeLabel.h"

class Minimize_DFA
{
private:
    int marked_count = 0 ;
    DFANode start_node;
    std::vector<std::vector<std::pair<DFANode,EdgeLabel>>> Graph ;
    std::vector<std::vector<std::pair<DFANode,EdgeLabel>>> Reduced_Graph ;
    std::vector<std::vector<bool>> Cells_to_be_marked;
    std::vector<std::pair<int,int>> Unmatched_States;
    std::vector<DFANode> State_Nodes;
    void set_up_bool_matrix();
    void Myhill_Nerode();
    int Myhill_Nerode_Iteration();
    bool is_one_a_terminal_state(int i, int j);
    void determine_Final_Unmatched_States();
    std::vector<std::vector<std::pair<DFANode,char>>> merge_final_states();
    void trim_redundant_states();
    int trim_redundant_states_single_node(int index);

public:

    Minimize_DFA(std::vector<std::vector<std::pair<DFANode, EdgeLabel>>> dfa_graph,
                 DFANode start_node);
    std::vector<std::vector<std::pair<DFANode,char>>> Calculate_Minimum_DFA();
};

#endif //LEXICAL_ANALYZER_REDUCEDDFA_H
