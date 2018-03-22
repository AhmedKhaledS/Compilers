//
// Created by hisham on 22/03/18.
//

#include "NFA.h"


NFA::NFA() {

}

int NFA::get_no_of_nodes() {
    return this->no_of_states;
}

void NFA::add_state(State s) {
    this->states.push_back(s);
}

std::vector<State> NFA::get_states() {
    return this->states;
};



NFA NFA::create_NFA(char c) {

    NFA result;

    result.no_of_states = 2;

    State state_0(0);
    State state_1(1);

    Transition transition(1,c);
    state_0.add_transition(transition);

    state_1.set_accepted();

    result.add_state(state_0);
    result.add_state(state_1);

    return result;
}


NFA NFA::oring(NFA x, NFA y) {

    int no_of_nodes = x.get_no_of_nodes() + y.get_no_of_nodes() + 2;

    NFA result;
    result.create_nodes(no_of_nodes);

    result.copy_prev_transitions(x.get_transitions(), y.get_transitions(), x.get_no_of_nodes());

    result.add_transition(0, 1, EPSILON);
    result.add_transition(0, x.get_no_of_nodes() + 1, EPSILON);
    result.add_transition(x.get_no_of_nodes(), no_of_nodes - 1, EPSILON);
    result.add_transition(no_of_nodes - 2, no_of_nodes - 1, EPSILON);

    return result;
}

NFA NFA::concatenating(NFA x, NFA y) {

    int no_of_nodes = x.get_no_of_nodes() + y.get_no_of_nodes() + 2;

    NFA result;
    result.create_nodes(no_of_nodes);

    result.copy_prev_transitions(x.get_transitions(), y.get_transitions(), x.get_no_of_nodes());

    result.add_transition(0, 1, EPSILON);
    result.add_transition(x.get_no_of_nodes(), x.get_no_of_nodes() + 1, EPSILON);
    result.add_transition(no_of_nodes - 2, no_of_nodes - 1, EPSILON);

    return result;
}

NFA NFA::kleene_closuring(NFA x) {

    int no_of_nodes = x.get_no_of_nodes() + 2;

    NFA result;
    result.create_nodes(no_of_nodes);

    result.copy_prev_transitions(x.get_transitions());

    result.add_transition(0, 1, EPSILON);
    result.add_transition(0, no_of_nodes - 1, EPSILON);
    result.add_transition(no_of_nodes - 2, 1, EPSILON);
    result.add_transition(no_of_nodes - 2, no_of_nodes - 1, EPSILON);

    return result;
}


