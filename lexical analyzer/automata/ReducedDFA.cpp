//
// Created by ahmed on 16/03/18.
//

#include <algorithm>
#include "ReducedDFA.h"


Minimize_DFA::Minimize_DFA(std::vector<std::vector<DFANode>> dfa_graph)
{
    Graph = dfa_graph;
    set_up_bool_matrix();
}

void Minimize_DFA::set_up_bool_matrix()
{
    int rows = static_cast<int>(Graph.size());
    int cols = static_cast<int>(Graph.size());
    for(int x = 0 ; x <= rows ; x++){
        std::vector<bool> temp ;
        temp.resize(cols,false);
        Cells_to_be_marked.push_back(temp);
    }
    for(int x = 0 ; x <= Graph.size() ; x ++){
        States ; //get_dfa_node(int id)
    }
}


void Minimize_DFA::Myhill_Nerode()
{
    int previous_marked_count ;
    do{
        previous_marked_count = marked_count;
       marked_count =  Myhill_Nerode_Iteration();
    }while(marked_count != previous_marked_count );
    determine_Final_Unmatched_States();
}


int Minimize_DFA::Myhill_Nerode_Iteration()
{
    if(marked_count == 0){
        for (int i = 0 ; i <= Graph.size() ; i++){
            for(int j = 0 ; j < i ; j++){
                if(Cells_to_be_marked[i][j] == false ||
                    (int)States[i].acceptance_state + (int)States[j].acceptance_state == 1){
                    Cells_to_be_marked[i][j] = true;
                    marked_count++;
                }
            }
        }
    }
    else{
        for (int i = 0 ; i <= Graph.size() ; i++){
            for(int j = 0 ; j < i ; j++){
                if(Cells_to_be_marked[i][j] == false){
                    Cells_to_be_marked[i][j] = check_pair_compatibility( i ,  j);
                }
            }
        }
    }
    return marked_count;
}


bool Minimize_DFA::check_pair_compatibility(int i , int j)
{
    std::vector<char> Common_Transitions;
    std::vector<char> Transitions_i;
    std::vector<char> Transitions_j;


    for(int x = 0 ; x <= Graph[i].size() ; x++){
        Transitions_i.push_back(Graph[i][x].second);
    }
    for(int y = 0 ; y <= Graph[j].size() ; y++){
        Transitions_i.push_back(Graph[i][y].second);
    }


    std::sort(Transitions_i.begin(), Transitions_i.end());
    std::sort(Transitions_j.begin(), Transitions_j.end());

    std::set_intersection(Transitions_i.begin(), Transitions_i.end(),
                          Transitions_j.begin(), Transitions_j.end(),
                          std::back_inserter(Common_Transitions));


    for(char x : Common_Transitions){
        DFANode temp1 /* = Next_State(i , x)*/;
        DFANode temp2 /* = Next_State(j , x)*/;
        if( Cells_to_be_marked[temp1.id][temp2.id] == true ||
                Cells_to_be_marked[temp2.id][temp1.id] == true ){

            return true;
        }
    }
    return false;
}


void Minimize_DFA::determine_Final_Unmatched_States()
{
    for (int i = 0 ; i <= Graph.size() ; i++){
        for(int j = 0 ; j < i ; j++){
            if(Cells_to_be_marked[i][j] == false){
                std::pair temporary ;
                temporary.first = i;
                temporary.second = j;
                Unmatched_States.(temporary);
            }
        }
    }
}

std::vector<std::vector> Minimize_DFA::Calculate_Minimum_DFA()
{
    Myhill_Nerode();
    return merge_final_states();

}