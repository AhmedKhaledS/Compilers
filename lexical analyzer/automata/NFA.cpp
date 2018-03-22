//
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

/*
NFA NFA::oring(NFA x, NFA y) {

    int no_of_nodes = x.get_no_of_nodes() + y.get_no_of_nodes() + 2;

    NFA result;
    result.copy_prev_states(result);

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
 */

/*
NFA NFA::kleene_closuring(NFA x) {

    int no_of_nodes = x.get_no_of_nodes() + 2;

    NFA result;

    result.copy_prev_states(result, x.get_states());

    State s_1(0);
    State s_2(x.get_states().size() + 1);

    result.add_state(s_1);
    result.add_state(s_2);

    Transition t_1(1, EPSILON);
    Transition t_2(no_of_nodes - 1, EPSILON);
    result.get_states()[0].add_transition(t_1);
    result.get_states()[0].add_transition(t_2);
    Transition t_3(no_of_nodes - 1, EPSILON);
    Transition t_4(no_of_nodes - 1, EPSILON);
    //result.get_states()[no_of_nodes - 2].add_transition(t_3);
    //result.get_states()[no_of_nodes - 2].add_transition(t_4);

    return result;
}


void NFA::copy_prev_states(NFA nfa, std::vector<State> x) {

    for(unsigned int i = 0; i < x.size(); i++) {
        int pre_state_number = x[i].get_state_number();
        x[i].set_state_number(pre_state_number + 1);
        std::vector<Transition> transitions = x[i].get_transitions();
        for (int j = 0; j < transitions.size(); ++j) {
            int previous_destination = transitions[i].get_destination();
            transitions[i].set_destination(previous_destination + 1);
        }
    }

    nfa.add_state(x);


}

/*
void NFA::copy_prev_states(std::vector<State> x, std::vector<State> y, int offset) {

    for(unsigned int i = 0; i < x.size(); i++) {
        x[i].src++;
        x[i].dst++;
        edges.push_back(x[i]);
    }

    for(unsigned int i = 0; i < y.size(); i++) {
        y[i].src += offset + 1;
        y[i].dst += offset + 1;
        edges.push_back(y[i]);
    }

}
 */