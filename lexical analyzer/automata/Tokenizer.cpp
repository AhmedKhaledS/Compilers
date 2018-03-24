//
// Created by ahmed on 24/03/18.
//

#include "Tokenizer.h"

using namespace std;

Tokenizer::Tokenizer() {
    current_state = starting_state;
}

void Tokenizer::tokenize(char c)
{
    string s;
    if (isalpha(c))
    {
        if (islower(c))
        {
            s = "a-z";
        }
        else
        {
            s = "A-Z";
        }
    }
    s.push_back(c);
    DFANode ret_node = tr.normal_transition(*current_state, s);
    stk_node.push(ret_node);
    current_state = ret_node;
}

void Tokenizer::set_dfa_graph(std::vector<std::vector<std::pair<DFANode, string> > > *dfa) {
    this->dfa_graph = dfa;
}

void Tokenizer::set_starting_state(DFANode *st_state) {
    this->starting_state = st_state;
}
