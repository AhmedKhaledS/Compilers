//
// Created by ahmed on 16/03/18.
//

#ifndef LEXICAL_ANALYZER_REDUCEDDFA_H
#define LEXICAL_ANALYZER_REDUCEDDFA_H

#include <vector>
#include <string>
#include "DFANode.h"


class Minimize_DFA
{
    private:
    int marked_count;
    std::vector<std::vector<bool>> Cells_to_be_marked;
    std::vector<std::vector<DFANode>> Graph ;
    std::vector<DFANode> States;
    std::vector<DFANode> Final_Unmarked_States;
    // here we will need a boolean Myhill_Nerode;
    void Myhill_Nerode_Iteration(int it);
    void set_up_bool_matrix();
    void merge_final_states();

    public:

    Minimize_DFA(std::vector<std::vector<DFANode>> dfa_graph);
    std::vector<std::vector> Calculate_Minimum_DFA();
};

#endif //LEXICAL_ANALYZER_REDUCEDDFA_H
