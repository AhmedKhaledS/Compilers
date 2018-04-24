
//
// Created by ahmed on 3/22/18.
//

#include "automata/ReducedDFA.h"
#include "automata/State.h"
#include "automata/DFANode.h"

//int main (){

//    State st(0);
//    std::vector<State> v1;
//    v1.push_back(st);
//    DFANode s2(v1, false, false, false, 0);
//
//    Minimize_DFA *test = new Minimize_DFA(s2,
//                                          DFANode(std::vector<State>(), false, false, false, 0));
//    test->Calculate_Minimum_DFA();



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
    Lexical_controller l;
    l.run_("test.txt", "test_1.txt");

return 0;
}