//
// Created by hisham on 22/03/18.
//

#include "State.h"

State::State(int state_number){
    this->state_number = state_number;
    this->acceptance_state = false;
}

void State::add_transition(Transition T) {
    transitions.push_back(T);
}

std::vector<Transition> State::get_transitions() {
    return transitions;
}

int State::get_state_number() {
    return this->state_number;
}

void State::set_accepted() {
    this->acceptance_state = true;
}

bool State::is_acceptance_state() {
    return this->acceptance_state;
}