//
// Created by hisham on 22/03/18.
//

#ifndef COMPILERS_NFA_H
#define COMPILERS_NFA_H

#include "State.h"

class NFA {

public:

    NFA();

    int get_no_of_nodes();

    void add_state(State s);
    void add_state(std::vector<State> s);
    std::vector<State> *get_states();

private:

    int no_of_states;
    std::vector<State> states;
};


#endif //COMPILERS_NFA_H