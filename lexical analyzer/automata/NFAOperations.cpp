//
// Created by hisham on 22/03/18.
//

#include "NFAOperations.h"
#include <iostream>

#define EPSILON '$'

#include "NFAGenerator.h"


NFA NFAOperations::create_NFA(char c) {

    NFAGenerator::add_symbol(c);

    NFA result;

    State state_0(0);
    State state_1(1);

    state_0.add_transition(make_pair(state_1, c));
    state_1.set_acceptance_state(true);

    result.add_state(state_0);
    result.add_state(state_1);

    return result;
}

NFA NFAOperations::oring(NFA x, NFA y) {

    int nodes_count = x.get_no_of_nodes() + y.get_no_of_nodes();

    NFA result;

    copy_prev_states(&result, (*x.get_states()), (*y.get_states()), x.get_no_of_nodes());

    State s_1(0);
    State s_2(nodes_count + 1);


    s_2.set_acceptance_state(true);


    s_1.add_transition(make_pair((*result.get_states())[0], EPSILON));
    s_1.add_transition(make_pair((*result.get_states())[x.get_no_of_nodes()], EPSILON));
    (*result.get_states())[x.get_no_of_nodes() - 1].add_transition(make_pair(s_2, EPSILON));
    (*result.get_states())[nodes_count - 1].add_transition(make_pair(s_2, EPSILON));


    result.add_state(s_1, 0);
    result.add_state(s_2);

    return result;
}

NFA NFAOperations::concatenating(NFA x, NFA y) {
    int nodes_count = x.get_no_of_nodes() + y.get_no_of_nodes();

    NFA result;

    copy_prev_states(&result, (*x.get_states()), (*y.get_states()), x.get_no_of_nodes());

    State s_1(0);
    State s_2(nodes_count + 1);
    s_2.set_acceptance_state(true);

    s_1.add_transition(make_pair((*result.get_states())[0], EPSILON));
    (*result.get_states())[x.get_no_of_nodes() - 1].add_transition
            (make_pair((*result.get_states())[x.get_no_of_nodes()], EPSILON));
    (*result.get_states())[nodes_count - 1].add_transition(make_pair(s_2, EPSILON));

    result.add_state(s_1, 0);
    result.add_state(s_2);

    return result;
}

NFA NFAOperations::kleene_closuring(NFA x) {

    int nodes_count = x.get_no_of_nodes();

    NFA result;

    copy_prev_states(&result, (*x.get_states()), 1, true);

    State s_1(0);
    State s_2(nodes_count + 1);
    s_2.set_acceptance_state(true);


    s_1.add_transition(make_pair((*result.get_states())[0], EPSILON));
    s_1.add_transition(make_pair(s_2, EPSILON));
    (*result.get_states())[nodes_count - 1].add_transition(make_pair((*result.get_states())[0], EPSILON));
    (*result.get_states())[nodes_count - 1].add_transition(make_pair(s_2, EPSILON));

    result.add_state(s_1, 0);
    result.add_state(s_2);

    return result;
}

void NFAOperations::copy_prev_states(NFA* nfa, std::vector<State> states, int offset, bool clear) {

    for(int i = 0; i < states.size(); i++) {

        int pre_state_number = states[i].get_state_number();
        states[i].set_state_number(pre_state_number + offset);

        if(clear == true) states[i].set_acceptance_state(false);

        for (int j = 0; j < states[i].get_transitions()->size(); j++) {

            int previous_destination = (*states[i].get_transitions())[j].first.get_state_number();
            (*states[i].get_transitions())[j].first.set_state_number(previous_destination + offset);
        }
    }



    (*nfa).add_state(states);

}

void NFAOperations::copy_prev_states(NFA *nfa, std::vector<State> x, std::vector<State> y, int offset) {

    for(int i = 0; i < x.size(); i++) {

        int pre_state_number = x[i].get_state_number();
        x[i].set_state_number(pre_state_number + 1);
        x[i].set_acceptance_state(false);

        for (int j = 0; j < x[i].get_transitions()->size(); j++) {

            int previous_destination = (*x[i].get_transitions())[j].first.get_state_number();
            (*x[i].get_transitions())[j].first.set_state_number(previous_destination + 1);
        }
    }

    for(int i = 0; i < y.size(); i++) {

        int pre_state_number = y[i].get_state_number();
        y[i].set_state_number(pre_state_number + offset + 1);
        y[i].set_acceptance_state(false);


        for (int j = 0; j < y[i].get_transitions()->size(); j++) {

            int previous_destination = (*y[i].get_transitions())[j].first.get_state_number();
            (*y[i].get_transitions())[j].first.set_state_number(previous_destination + offset + 1);
        }
    }



    (*nfa).add_state(x);
    (*nfa).add_state(y);
}

NFA NFAOperations::positive_closuring(NFA x) {
    NFA kleen = kleene_closuring(x);
    NFA result = concatenating(x , kleen);


    //(*result.get_states())[10].set_acceptance_state(true);

    return result;
}

NFA NFAOperations::oring_all(vector<NFA> all) {

    NFA result;
    int count = 1;

    State s_1(0);

    for (int i = 0; i < all.size(); i++) {
            copy_prev_states(&result, (*all[i].get_states()) , count, false);
            s_1.add_transition(make_pair((*result.get_states())[count - 1], EPSILON));
            count += (*all[i].get_states()).size();
    }

    result.add_state(s_1, 0);

    return result;
}


NFA NFAOperations::solver(string expression) {

    vector<NFA> all;

    for (int i = 0; i < expression.length(); i++) {
        if(expression[i] != '|' && expression[i] != ' ') {
            cout << expression[i] << endl;
            all.push_back(create_NFA(expression[i]));
        }
    }

    NFA result;


    int count = 1;
    for (int i = 0; i < all.size(); i++) {
        count += (*all[i].get_states()).size();
    }

    State s_1(0);
    State s_2(count + 1);

    count = 1;
    for (int i = 0; i < all.size(); i++) {
        copy_prev_states(&result, (*all[i].get_states()) , count, true);
        s_1.add_transition(make_pair((*result.get_states())[count - 1], EPSILON));
        count += (*all[i].get_states()).size();
        (*result.get_states())[count - 2].add_transition(make_pair(s_2, EPSILON));
    }

    result.add_state(s_1, 0);
    result.add_state(s_2);

    return result;
}