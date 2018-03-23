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


#endif //LEXICAL_ANALYZER_UTILITIES_H
