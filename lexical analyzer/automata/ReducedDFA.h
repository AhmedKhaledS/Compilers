//
// Created by ahmed on 16/03/18.
//

#ifndef LEXICAL_ANALYZER_REDUCEDDFA_H
#define LEXICAL_ANALYZER_REDUCEDDFA_H

#include <vector>
#include <string>
#include "DFANode.h"
#include "DFATransformer.h"

class Minimize_DFA
{
    private:
    int marked_count = 0 ;
    std::vector<std::vector<bool>> Cells_to_be_marked;
    std::vector<std::vector<std::pair<DFANode,char>>> Graph ;
    std::vector<DFANode> State_Nodes;
    std::vector<std::pair<int,int>> Unmatched_States;
    void set_up_bool_matrix();
    void Myhill_Nerode();
    int Myhill_Nerode_Iteration();
    bool check_pair_compatibility(int i , int j);
    void determine_Final_Unmatched_States();
    std::vector<std::vector<DFANode>> merge_final_states();

    public:

    Minimize_DFA(/*std::vector<std::vector<std::pair<DFANode,char>>> dfa_graph*/);
    std::vector<std::vector<DFANode>> Calculate_Minimum_DFA();
};

#endif //LEXICAL_ANALYZER_REDUCEDDFA_H
