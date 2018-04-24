//
// Created by ahmed on 16/03/18.
//

#include "LexicalController.h"
#include "automata/Tokenizer.h"

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#define MAX_NO_OF_LINES 100

using namespace std;

Lexical_controller::Lexical_controller()
{
    token_count = 0;
}

void Lexical_controller::run_(const string grammar_rule_file, const string src_program_file)
{

    // Reading and constructing automata from Grammar::
    Grammar_Reader g_reader;
    NFAGenerator generator;
    for (int i = 1; i <= MAX_NO_OF_LINES; ++i)
    {
        string current_rule = g_reader.read_next_grammar_rule_line(grammar_rule_file, i);
        if (current_rule == "~")
            break;
        generator.generate_grammar(current_rule);
    }
    NFA machine = generator.generate_machine();


    // Contains NFA-states
    vector<State> states = (*machine.get_states());
//    cout << "NFA machine: \n";
    /*for (int i = 0; i < states.size(); i++)
    {
        vector<pair <State, string>> transitions = *states[i].get_transitions();
        for (int j = 0; j < transitions.size(); j++)
        {
            cout << states[i].get_state_number() << " " << transitions[j].first.get_state_number()
                 << " " << transitions[j].second
                 << " " << states[i].is_acceptance_state() << endl;
        }
    }*/


    vector<State> st_nfa_node;
    st_nfa_node.push_back(states[0]);
    DFATransformer transformer(DFANode(st_nfa_node, states[0].is_acceptance_state(),
                                       false, false, -1, states[0].get_acceptance_state_name()));
    transformer.set_nfa_graph(states);
    transformer.transform();

    vector<DFANode> tmp = *transformer.get_dfa_nodes();

    /*cout << "After running NFA-to-DFA transformation, these nodes are mapped to :\n";
    for (DFANode x : tmp)
    {
        cout << "New Dfa node id: " << x.id << "  consists of states: ";
        for (State y : x.dfa_state) {
            cout << y.get_state_number() << " ";
        }
        cout <<  " acceptance state: " << x.acceptance_state << " state name: " << x.acceptance_state_name << endl;
        cout << endl;
    }*/

    /*cout << "New DFA graph: \n";
    vector< vector< pair<DFANode, EdgeLabel> > > *transformed_graph = transformer.get_dfa_graph();
    for (int i = 0; i < transformer.get_dfa_graph_size(); i++)
    {
        for (pair<DFANode, EdgeLabel> x : (*transformed_graph)[i])
        {
//            cout << "State: " << i << "  goes to state: " << x.first.id << " under input: ";
            cout << i << " " << x.first.id << " ";
            string label = x.second.get_input();
            set<string> disc_set = x.second.get_discarded_char();
            if (!disc_set.empty())
                label += "-{";
            for (auto it = disc_set.begin(); it != disc_set.end(); ++it)
            {
                label += *it;
                label += ",";
            }
            if (!disc_set.empty())
                label += "}";
            cout << label << endl;
        }
    }*/


    // Reading source programs::
    // Revise starting state of DFA Node.
    Tokenizer tokenizer(transformer.get_starting_dfa_state(), &transformer, transformer.get_dfa_graph());
    Source_program_reader src_prog_reader;
    src_prog_reader.set_src_file_name(src_program_file);
    Grammar_Reader src_reader;
    stack<DFANode> stk_node;
    DFANode starting_state = *transformer.get_starting_dfa_state();
    DFANode current_state = starting_state;
    for (int i = 1; i <= MAX_NO_OF_LINES; ++i)
    {
        string current_rule = src_reader.read_next_grammar_rule_line(src_program_file, i);

        for(int ii = 0; ii < current_rule.length(); ii++)
        {
            while (current_rule[ii] == ' ')
                current_rule.erase(ii,1);

        }
        if (current_rule == "~") {
            break;
        }
        tokenizer.tokenize(current_rule, &current_state, cached_tokens);
    }
}

string Lexical_controller::next_token()
{
    if (cached_tokens.size() == token_count)
        return "";
    return cached_tokens[token_count++];
}