#include <iostream>

#include <string>
#include <vector>
#include "file_services/FileWriter.h"
#include "file_services/GrammarReader.h"
#include "file_services/SourceProgramReader.h"
#include "LexicalController.h"
#include "SymbolTable.h"
#include "automata/DFATransformer.h"
#include <fstream>

#include "automata/NFAOperations.h"
#include "automata/NFA.h"
#include "automata/NFAGenerator.h"


using namespace std;

int main()
{
    //std::cout << "Hello, World!" << std::endl;
//    vector<string> s;
//    s.push_back("ahmed");
//    s.push_back("Khaled");
//    s.push_back("Saad");
//    File_Writer fl;
//    fl.write("dataa", s);
//    Symbol_table::add_identifier("Name", "Ahmed");
//    cout << Symbol_table::search_identifier("Name");

//    Source_program_reader sr;
//    cout << sr.get_next_char_from_src_program("dataa.lan");

    DFATransformer dt;
//    TransitionTable t;

//    NFA n;
//    State s0(0);
//    State s1(1);
//    State s2(2);
//    State s3(3);
//    State s4(4);
//    State s5(5);
//
//    n.add_state(s0);
//    n.add_state(s1);
//    n.add_state(s2);
//    n.add_state(s3);
//    n.add_state(s4);
//    n.add_state(s5);
//    vector<State> *v = n.get_states();
//    pair<State, char> t0 = {(*v)[1], 'a'};
//    pair<State, char> t1 = {(*v)[2], 'a'};
//    pair<State, char> t2 = {(*v)[3], 'a'};
//    pair<State, char> t3 = {(*v)[4], 'a'};
//    pair<State, char> t4 = {(*v)[5], 'a'};
//
//    (*v)[0].add_transition(t0);
//    (*v)[0].add_transition(t1);
//    (*v)[2].add_transition(t2);
//    (*v)[2].add_transition(t3);
//    (*v)[2].add_transition(t4);
//
//    vector<State> x;
//    x.push_back((*v)[0]);
//   // x.push_back(s2);
//    DFANode d_node(x, false, 1, true, true);
//    DFANode res = dt.normal_transition(&d_node, 'a');
//    cout << "States: ";
//    for (State curr : res.dfa_state)
//    {
//        cout << curr.get_state_number() << " ";
//    }
//
//    DFANode entry_node(true, 2, true, true);
//    t.add(d_node, 'b', &entry_node);
//
//    if (t.search(&d_node))
//        cout << "Found \n id= " << t.get_entry(&d_node, 'b')->id;
//    else
//        cout << "Error \n";

//    DFATransformer t;
//    t.add_dfa_node(&d_node, 1);
//    cout << t.get_dfa_node(1)->id << endl;


/*    Transition t_1;
    t_1.destination = 2;
    t_1.value = 'a';

    Transition t_2;
    t_2.destination = 3;
    t_2.value = '$';

    State s(1);
    s.add_transition(t_1);
    s.add_transition(t_2);

    vector<Transition> x = s.get_transitions();

    for (int i = 0; i < x.size(); ++i) {
        cout << x[i].destination << endl;
        cout << x[i].value << endl;
    }
*/
//    vector<State> states = (*result.get_states());
//    for (int i = 0; i < states.size(); i++) {
//        vector<pair <State, char>> transitions = *states[i].get_transitions();
//        for (int j = 0; j < transitions.size(); j++) {
//            cout << states[i].get_state_number() << " " << transitions[j].first.get_state_number()
//                                     << " " << transitions[j].second << endl;
//        }
//    }


//    NFAGenerator generator;
//    generator.generate_grammar("id=a|b");
//    generator.generate_grammar("id=a|b");
//    generator.generate_grammar("id=a|b");
//    NFA machine = generator.generate_machine();
//    vector<State> states = (*machine.get_states());
//    for (int i = 0; i < states.size(); i++) {
//        vector<pair <State, char>> transitions = *states[i].get_transitions();
//        for (int j = 0; j < transitions.size(); j++) {
//            cout << states[i].get_state_number() << " " << transitions[j].first.get_state_number()
//                                     << " " << transitions[j].second << endl;
//        }
//    }

//    NFAGenerator generator;
//    generator.generate_grammar("id=(a|b)*.a.b.b");
//    NFA machine = generator.generate_machine();
//
//    vector<State> states = (*machine.get_states());
//    for (int i = 0; i < states.size(); i++) {
//        vector<pair <State, char>> transitions = *states[i].get_transitions();
//        for (int j = 0; j < transitions.size(); j++) {
//            cout << states[i].get_state_number() << " " << transitions[j].first.get_state_number()
//                                     << " " << transitions[j].second << endl;
//        }
//    }

    Lexical_controller l;
    l.run_("test.txt", "");

//    NFAGenerator generator;
//    generator.generate_grammar("letter = a-b | A-B");
//    generator.generate_grammar("digit = 1-2");
//    generator.generate_grammar("id: letter(digit|letter)");
//    NFA machine = generator.generate_machine();

//    set<char> symbol = NFAGenerator::get_symbols();
//
//    for (set<char>::iterator  i = symbol.begin(); i != symbol.end(); i++) {
//        cout << *i << endl;
//    }


//    vector<State> states = (*machine.get_states());
//    for (int i = 0; i < states.size(); i++) {
//        vector<pair <State, char>> transitions = *states[i].get_transitions();
//        for (int j = 0; j < transitions.size(); j++) {
//            cout << states[i].get_state_number() << " " << transitions[j].first.get_state_number()
//                 << " " << transitions[j].second << endl;
//        }
//    }


    return 0;
}