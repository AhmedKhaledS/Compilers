//
// Created by ahmed on 16/03/18.
//

#include "ReducedDFA.h"


Minimize_DFA::Minimize_DFA(std::vector<std::vector<DFANode>> dfa_graph)
{
    Graph = dfa_graph;
    set_up_bool_matrix();
}

void Minimize_DFA::set_up_bool_matrix()
{
    int rows = static_cast<int>(Graph.size());
    int cols = static_cast<int>(Graph[0].size());
    for(int x = 0 ; x <= rows ; x++){
        std::vector<bool> temp ;
        temp.resize(cols,false);
        Cells_to_be_marked.push_back(temp);
    }
}