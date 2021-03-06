//
// Created by hisham on 22/03/18.
//


#include "State.h"

State::State(int state_number) {
    this->state_number = state_number;
    this->acceptance_state = false;
    this->acceptance_state_name = "";
}

void State::set_state_number(int state_number) {
    this->state_number = state_number;
}

int State::get_state_number() {
    return this->state_number;
}

void State::set_acceptance_state(bool state) {
    this->acceptance_state = state;
}

bool State::is_acceptance_state() {
    return this->acceptance_state;
}

void State::set_acceptance_state_name(string state_name) {
    this->acceptance_state_name = state_name;
}

string State::get_acceptance_state_name() {
    return this->acceptance_state_name;
}

void State::add_transition(pair <State, string> transition) {
    this->transitions.push_back(transition);
}

vector<pair <State, string>> *State::get_transitions() {
    return &this->transitions;
}

State::State() {

}


