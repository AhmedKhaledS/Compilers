//
// Created by hisham on 22/03/18.
//


#include "State.h"

State::State(int state_number)
{
    this->state_number = state_number;
    this->acceptance_state = false;
}

void State::set_state_number(int state_number) {
    this->state_number = state_number;
}

int State::get_state_number()
{
    return this->state_number;
}

void State::set_acceptance_state(bool state) {
    this->acceptance_state = state;
}

bool State::is_acceptance_state() {
    return this->acceptance_state;
}

void State::add_transition(pair <State, char> transition) {
    this->transitions.push_back(transition);
}

vector<pair <State, char>> *State::get_transitions() {
    return &this->transitions;
}

State::State() {

}
