//
// Created by hisham on 22/03/18.
//

#ifndef COMPILERS_NFA_H
#define COMPILERS_NFA_H

#include "State.h"
#include "Transition.h"

class NFA {

    public:
        NFA();

        void add_state(State s);

        NFA create_NFA(char c);

        NFA oring(NFA x, NFA y);

        NFA concatenating(NFA x, NFA y);

        NFA kleene_closuring(NFA x);

        int get_no_of_nodes();
        std::vector<State> get_states();

    private:
        int no_of_states;
        std::vector<State> states;
};


#endif //COMPILERS_NFA_H
