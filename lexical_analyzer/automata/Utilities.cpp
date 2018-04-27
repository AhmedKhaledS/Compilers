//
// Created by ahmed on 3/23/18.
//



#include "Utilities.h"
#include "EdgeLabel.h"

DFANode* get_dfa_node(std::vector<std::vector<std::pair<DFANode,EdgeLabel>>> graph ,
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


DFANode* get_next_node(std::vector<std::vector<std::pair<DFANode,EdgeLabel>>> graph ,
                       int current_index ,
                       EdgeLabel input)
{
    DFANode* receiver ;
    for(int j = 0 ; j < graph[current_index].size() ; j++){
        if(graph[current_index][j].second.get_input() == input.get_input()){
            receiver = &graph[current_index][j].first;
            return receiver;
        }
    }
}


int findParent(int node,std::vector<int> parent)
{
    if(parent[node] == node)return node;
    return parent[node] = findParent(parent[node],parent);
}

bool mergeNodes(std::vector<std::vector<std::pair<DFANode,char>>> graph,
                int a ,
                int b ,
                std::vector<int> *parent ,
                std::vector<int> *times_previously_merged )
{
    int parentA = findParent(a,*parent);
    int parentB = findParent(b,*parent);
    if(parentA == parentB)return false;
    if (get_dfa_node(graph,parentA)->acceptance_state){
        if(get_dfa_node(graph,parentB) -> acceptance_state){

            if(times_previously_merged[a] > times_previously_merged[b])
                (*parent)[parentB] = parentA;
            else
                (*parent)[parentA] = parentB;

        }else{

            (*parent)[parentB] = parentA;
        }
    } else {
        if(get_dfa_node(graph,parentB) -> acceptance_state){
            (*parent)[parentA] = parentB;
        }else{

            if((*times_previously_merged)[b] > (*times_previously_merged)[a])
                (*parent)[parentA] = parentB;
            else
                (*parent)[parentB] = parentA;

        }
    }

    (*times_previously_merged)[a] ++;
    (*times_previously_merged)[b] ++;
    return true;
}