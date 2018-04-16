//
// Created by ahmed on 24/03/18.
//

#include <iostream>
#include "Tokenizer.h"

using namespace std;

Tokenizer::Tokenizer(DFANode st_state, DFATransformer dfa_trans, vector< vector< pair<DFANode, string> > > dfa)
    : tr(dfa_trans), dfa_graph(dfa)
{
    starting_state = &st_state;
    current_state = &st_state;
     stk_node.push(*starting_state);
}

void Tokenizer::tokenize(string input_line)
{
    Helper helper;
    string lexeme = "";
    for (int i = 0; i < input_line.length(); i++)
    {
        bool found = false;
        for (pair<DFANode, string> x : dfa_graph[current_state->id])
        {
            string expanded_string = helper.normalize_classes(x.second);
            if (expanded_string.find(input_line) !=  string::npos)
            {
                found = true;
                DFANode reached_node = x.first;
                stk_node.push(reached_node);
                lexeme.push_back(input_line[i]);
                break;
            }
        }

        if (!found)
        {
            while (!stk_node.empty())
            {
                if (stk_node.top().acceptance_state)
                {
                    current_state = starting_state;
                    while (!stk_node.empty())
                        stk_node.pop();
                    cout << "Current lexeme: "<< lexeme << endl;
                }
                else
                {
                    lexeme.pop_back();
                    stk_node.pop();
                    --i;
                }
            }
        }

    }
}

//void Tokenizer::set_dfa_graph(std::vector<std::vector<std::pair<DFANode, string> > > *dfa) {
//    this->dfa_graph = dfa;
//}

//void Tokenizer::set_starting_state(DFANode *st_state) {
//    this->starting_state = st_state;
//}
