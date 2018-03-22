// Created by hisham on 22/03/18.
//

#include "NFA.h"


NFA::NFA() {
    no_of_states = 0;
}

int NFA::get_no_of_nodes() {
    return this->no_of_states;
}

void NFA::add_state(State s) {
    no_of_states++;
    this->states.push_back(s);
}

void NFA::add_state(std::vector<State> s) {
    for (int i = 0; i < s.size(); ++i) {
        add_state(s[i]);
    }
}

std::vector<State> *NFA::get_states() {
    return &this->states;
};