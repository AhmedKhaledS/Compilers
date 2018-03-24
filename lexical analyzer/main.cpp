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



//using namespace std;
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

