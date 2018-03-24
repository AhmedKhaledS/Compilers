//
// Created by ahmed on 16/03/18.
//

#include "LexicalController.h"

#include <string>
#include <vector>
#include <iostream>

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
    for (int i = 0; i < states.size(); i++) {
        vector<pair <State, string>> transitions = *states[i].get_transitions();
        for (int j = 0; j < transitions.size(); j++) {
            cout << states[i].get_state_number() << " " << transitions[j].first.get_state_number()
                 << " " << transitions[j].second << endl;
        }
    }
    DFATransformer transformer;
    transformer.set_nfa_graph(states);
    transformer.transform();


    // Reading source programs::
    Source_program_reader src_prog_reader;
    src_prog_reader.set_src_file_name(src_program_file);
    char c;
    while ((c = src_prog_reader.get_next_char_from_src_program()) != '~')
    {

    }




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
    vector< vector< pair<DFANode, string> > > *transformed_graph = transformer.get_dfa_graph();
    for (int i = 0; i < transformer.get_dfa_graph_size(); i++)
    {
        for (pair<DFANode, string> x : (*transformed_graph)[i])
        {
            cout << "State: " << i << "  goes to state: " << x.first.id << " under input: " << x.second << endl;
        }
    }




//    cout << "States: ";
//    for (State curr : res.dfa_state)
//    {
//        cout << curr.get_state_number() << " " << "acceptance: " << curr.is_acceptance_state() << endl;
//    }
//    cout << "\nacceptance state: " << res.acceptance_state << endl;


}