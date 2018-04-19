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
    cout << "NFA machine: \n";
    for (int i = 0; i < states.size(); i++)
    {
        vector<pair <State, string>> transitions = *states[i].get_transitions();
        for (int j = 0; j < transitions.size(); j++)
        {
            cout << states[i].get_state_number() << " " << transitions[j].first.get_state_number()
                 << " " << transitions[j].second
                 << " " << states[i].is_acceptance_state() << endl;
        }
    }


    vector<State> st_nfa_node;
    st_nfa_node.push_back(states[0]);
    DFATransformer transformer(DFANode(st_nfa_node, states[0].is_acceptance_state(), false, false, -1));
    transformer.set_nfa_graph(states);
    transformer.transform();

    vector<DFANode> tmp = *transformer.get_dfa_nodes();

    cout << "After running NFA-to-DFA transformation, these nodes are mapped to :\n";
    for (DFANode x : tmp)
    {
        cout << "New Dfa node id: " << x.id << "  consists of states: ";
        for (State y : x.dfa_state) {
            cout << y.get_state_number() << " ";
        }
        cout <<  " acceptance state: " << x.acceptance_state << endl;
        cout << endl;
    }

    cout << "New DFA graph: \n";
    vector< vector< pair<DFANode, EdgeLabel> > > *transformed_graph = transformer.get_dfa_graph();
    for (int i = 0; i < transformer.get_dfa_graph_size(); i++)
    {
        for (pair<DFANode, EdgeLabel> x : (*transformed_graph)[i])
        {
            cout << "State: " << i << "  goes to state: " << x.first.id << " under input: ";
            string label = x.second.get_input();
            set<string> disc_set = x.second.get_discarded_char();
            if (!disc_set.empty())
                label += "-{";
            for (auto it = disc_set.begin(); it != disc_set.end(); ++it)
            {
                label += *it;
                label += ", ";
            }
            if (!disc_set.empty())
                label += "}";
            cout << label << endl;
        }
    }


    // Reading source programs::
    //Revise starting state of DFA Node.
    //Tokenizer tokenizer(*transformer.get_starting_dfa_state(), transformer, *transformer.get_dfa_graph());
    //tokenizer.set_dfa_graph(transformer.get_dfa_graph());
    Source_program_reader src_prog_reader;
    src_prog_reader.set_src_file_name(src_program_file);
    Grammar_Reader src_reader;
    stack<DFANode> stk_node;
    DFANode starting_state = *transformer.get_starting_dfa_state();
    DFANode current_state = starting_state;
    for (int i = 1; i <= MAX_NO_OF_LINES; ++i)
    {
        string current_rule = src_reader.read_next_grammar_rule_line(src_program_file, i);
        std::string::iterator end_pos = std::remove(current_rule.begin(), current_rule.end(), ' ');
        current_rule.erase(end_pos, current_rule.end());
        if (current_rule == "~") {
            break;
        }
        Helper helper;
        string lexeme = "";
        for (int j = 0; j < current_rule.length(); j++)
        {
            bool found = false;
            for (pair<DFANode, EdgeLabel> x : (*transformer.get_dfa_graph())[(current_state).id])
            {
                string expanded_string = helper.normalize_classes(x.second.get_input());
                if (expanded_string.find(current_rule[j]) !=  string::npos)
                {
                    found = true;
                    DFANode reached_node = x.first;
                    current_state = x.first;
                    stk_node.push(reached_node);
                    lexeme.push_back(current_rule[j]);
                    break;
                }
            }

            if (!found || (j == current_rule.size() - 1 && !stk_node.empty()))
            {
                if (!found)
                    --j;
                while (!stk_node.empty())
                {
                    if (stk_node.top().acceptance_state)
                    {
                        current_state = starting_state;
                        while (!stk_node.empty()) {
                            stk_node.pop();
                        }
                        cout << "Current lexeme: "<< lexeme << endl;
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
                current_state = starting_state;
                j = 0;
            }


        }

    }









//    cout << "States: ";
//    for (State curr : res.dfa_state)
//    {
//        cout << curr.get_state_number() << " " << "acceptance: " << curr.is_acceptance_state() << endl;
//    }
//    cout << "\nacceptance state: " << res.acceptance_state << endl;


}