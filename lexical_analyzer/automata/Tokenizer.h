//
// Created by ahmed on 24/03/18.
//

#ifndef LEXICAL_ANALYZER_TOKENIZER_H
#define LEXICAL_ANALYZER_TOKENIZER_H

#include "DFANode.h"
#include "State.h"
#include <vector>
#include <stack>
#include "DFATransformer.h"
#include "Helper.h"
#include <fstream>

class Tokenizer
{
private:
    std::vector< std::vector< std::pair<DFANode, EdgeLabel> > > *dfa_graph;
    std::string character_pool;
    std::vector<std::string> tokens;
    stack<DFANode> stk_node;
    DFANode *starting_state;
    DFANode *current_state;
    DFATransformer *tr;
    std::ofstream lexical_output_file;
public:
    Tokenizer(DFANode *st_state, DFATransformer *dfa_trans, std::vector< std::vector< std::pair<DFANode, EdgeLabel> > > *dfa);
    void tokenize(string input_line, DFANode *current_state, vector<string> &cached);
    void set_starting_state(DFANode *st_state);
    // void set_dfa_graph(std::vector< std::vector< std::pair<DFANode, string> > > *dfa);

};

#endif //LEXICAL_ANALYZER_TOKENIZER_H
