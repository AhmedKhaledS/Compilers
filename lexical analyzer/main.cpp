#include <iostream>

#include <string>
#include <vector>
#include "file_services/FileWriter.h"
#include "file_services/GrammarReader.h"
#include "file_services/SourceProgramReader.h"
#include "SymbolTable.h"
#include "automata/DFATransformer.h"
#include <fstream>

#include "automata/Transition.h"
#include "automata/State.h"

//using namespace std;
//
//int main()
//{
//    std::cout << "Hello, World!" << std::endl;
////    vector<string> s;
////    s.push_back("ahmed");
////    s.push_back("Khaled");
////    s.push_back("Saad");
////    File_Writer fl;
////    fl.write("dataa", s);
////    Symbol_table::add_identifier("Name", "Ahmed");
////    cout << Symbol_table::search_identifier("Name");
//
////    Source_program_reader sr;
////    cout << sr.get_next_char_from_src_program("dataa.lan");
//
//    //DFATransformer dt;
////    TransitionTable t;
//    vector<State> x;
//    DFANode d_node(x, false, 1, true, true);
////
////    DFANode entry_node(true, 2, true, true);
////    t.add(d_node, 'b', &entry_node);
////
////    if (t.search(&d_node))
////        cout << "Found \n id= " << t.get_entry(&d_node, 'b')->id;
////    else
////        cout << "Error \n";
//
//    DFATransformer t;
//    t.add_dfa_node(&d_node, 1);
//    cout << t.get_dfa_node(1)->id << endl;
//
///*    Transition t_1;
//    t_1.destination = 2;
//    t_1.value = 'a';
//
//    Transition t_2;
//    t_2.destination = 3;
//    t_2.value = '$';
//
//    State s(1);
//    s.add_transition(t_1);
//    s.add_transition(t_2);
//
//    vector<Transition> x = s.get_transitions();
//
//    for (int i = 0; i < x.size(); ++i) {
//        cout << x[i].destination << endl;
//        cout << x[i].value << endl;
//    }
//*/
//    return 0;
//}