//
// Created by hisham on 22/03/18.
//

#ifndef COMPILERS_STATE_H
#define COMPILERS_STATE_H

#include "Transition.h"
#include <vector>

class State {

    public:

        State(int state_number);

        void add_transition(Transition T);
        std::vector<Transition> get_transitions();

        int get_state_number();

        void set_accepted();
        bool is_acceptance_state();

    private:
        int state_number;
        bool acceptance_state;
        std::vector<Transition> transitions;

};


#endif //COMPILERS_STATE_H