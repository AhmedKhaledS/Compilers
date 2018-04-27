//
// Created by ahmed on 24/03/18.
//

#include <iostream>
#include "Tokenizer.h"
#include <algorithm>

using namespace std;

Tokenizer::Tokenizer(DFANode *st_state, DFATransformer *dfa_trans, vector< vector< pair<DFANode, EdgeLabel> > > *dfa)
        : tr(dfa_trans), dfa_graph(dfa)
{
    lexical_output_file.open("tokens.l", std::ios_base::out);
    starting_state = st_state;
    current_state = st_state;
    stk_node.push(*starting_state);
}

void Tokenizer::tokenize(string input_line, DFANode *current_state, vector<string> &cached)
{
    Helper helper;
    string lexeme = "";
    vector<string> inputs = NFAGenerator::get_symbols();
    for (int j = 0; j < input_line.length(); j++)
    {
        string tmp = "";
        tmp.push_back(input_line[j]);
        if (input_line[j] == '\r')
        {
            if (stk_node.size() == 0) continue;
            string accepted_state_name = stk_node.top().acceptance_state_name;
            *current_state = *starting_state;
            while (!stk_node.empty()) {
                stk_node.pop();
            }
//            cout << "Current lexeme: "<< lexeme << " type: " << accepted_state_name << "\n";
            lexical_output_file << accepted_state_name << "\n";
            cached.push_back(accepted_state_name);
            lexeme = "";
            continue;
        }
        if (find(inputs.begin(), inputs.end(), tmp) == inputs.end() && !isalpha(input_line[j])
            && !isdigit(input_line[j]))
        {
            cout << "Error detected!!\n";
            continue;
        }

        bool found = false;
        vector< pair<DFANode, EdgeLabel> > transitions = (*dfa_graph)[(*current_state).id];
        for (pair<DFANode, EdgeLabel> x : transitions)
        {
            string expanded_string = helper.normalize_classes(x.second.get_input());
            // Erase all characters found in the discarded set.
            set<string> dis_chars = x.second.get_discarded_char();
            for (auto it = dis_chars.begin(); it != dis_chars.end(); ++it)
            {
                if (isalpha((*it)[0]))
                    expanded_string.erase(remove(expanded_string.begin(), expanded_string.end(),
                                                 (*it)[0]), expanded_string.end()) ;
            }
            if (expanded_string.find(input_line[j]) !=  string::npos)
            {
                found = true;
                DFANode reached_node = x.first;
                *current_state = x.first;
                stk_node.push(reached_node);
                lexeme.push_back(input_line[j]);
                break;
            }
        }

        if (!found || (j == input_line.size() - 1 && !stk_node.empty()) || current_state->dfa_state.empty())
        {
            if (!found)
                --j;
            while (!stk_node.empty())
            {
                if (stk_node.top().acceptance_state)
                {
                    string accepted_state_name = stk_node.top().acceptance_state_name;
                    *current_state = *starting_state;
                    while (!stk_node.empty()) {
                        stk_node.pop();
                    }
//                    cout << "Current lexeme: "<< lexeme << " type: " << accepted_state_name << "\n";
                    lexical_output_file << accepted_state_name << "\n";
                    cached.push_back(accepted_state_name);
                    lexeme = "";
                }
                else
                {
                    lexeme.pop_back();
                    stk_node.pop();
                    --j;
                }
            }
        }

        if(j==-1) {
            lexeme = "";
            *current_state = *starting_state;
            j = 0;
        }
    }
}