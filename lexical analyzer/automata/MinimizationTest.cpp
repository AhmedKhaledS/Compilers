//
// Created by ahmed on 3/22/18.
//

#include "ReducedDFA.h"

int main (){

    State st(0);
    std::vector<State> v1;
    v1.push_back(st);
    DFANode s2(v1, false, false, false, 0);

    Minimize_DFA *test = new Minimize_DFA(s2,
                                          DFANode(std::vector<State>(), false, false, false, 0));
    test->Calculate_Minimum_DFA();

    return 0;
}