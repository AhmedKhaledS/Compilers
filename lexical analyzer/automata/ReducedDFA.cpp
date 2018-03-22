//
// Created by ahmed on 16/03/18.
//

#include "ReducedDFA.h"


Minimize_DFA::Minimize_DFA(std::vector<std::vector<std::string>> dfa_graph)
{
    Graph = dfa_graph;
    set_up_bool_matrix();
}

void Minimize_DFA::set_up_bool_matrix()
{
    int rows = static_cast<int>(Graph.size());
    int cols = static_cast<int>(Graph[0].size());

    for(int x = 0 ; x <= rows ; x++){
        for(int y = 0 ; y <= cols; ; y++){




        }
    }




}