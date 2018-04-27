//
// Created by ahmed on 3/23/18.
//

#ifndef LEXICAL_ANALYZER_UTILITIES_H
#define LEXICAL_ANALYZER_UTILITIES_H


#include "DFANode.h"

DFANode* get_dfa_node(std::vector<std::vector<std::pair<DFANode,char>>> graph ,
                      int index );

DFANode* get_next_node(std::vector<std::vector<std::pair<DFANode,char>>> graph ,
                       int current_index ,
                       char input);

int findParent(int node , std::vector<int> parent);

bool mergeNodes(std::vector<std::vector<std::pair<DFANode,char>>> graph,
                int a ,
                int b ,
                std::vector<int> *parent,
                std::vector<int> *times_previously_merged);


#endif //LEXICAL_ANALYZER_UTILITIES_H
