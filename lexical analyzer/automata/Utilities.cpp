//
// Created by ahmed on 3/23/18.
//



#include "Utilities.h"

DFANode* get_dfa_node(std::vector<std::vector<std::pair<DFANode,char>>> graph ,
                      int index )
{
    DFANode* receiver ;
    for(int i = 0 ; i < graph.size(); i++){
        for(int j = 0 ; j < graph[i].size() ; j++){
            if(graph[i][j].first.id == index){
                receiver = &graph[i][j].first;
                return receiver;
            }
        }
    }
}


DFANode* get_next_node(std::vector<std::vector<std::pair<DFANode,char>>> graph ,
                       int current_index ,
                       char input)
{
    DFANode* receiver ;
    for(int j = 0 ; j < graph[current_index].size() ; j++){
        if(graph[current_index][j].second == input){
            receiver = &graph[current_index][j].first;
            return receiver;
        }
    }
}
