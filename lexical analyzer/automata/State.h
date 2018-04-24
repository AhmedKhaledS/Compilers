//
// Created by hisham on 22/03/18.
//

#ifndef COMPILERS_STATE_H
#define COMPILERS_STATE_H

#include <vector>
#include <string>

using namespace std;

class State {

public:

    State(int state_number);
    State();


    void set_state_number(int state_number);

    int get_state_number();

    void set_acceptance_state(bool state);

    bool is_acceptance_state();

    void set_acceptance_state_name(string state_name);

    string get_acceptance_state_name();

    void add_transition(pair <State, string> transition);

    vector<pair <State, string>> *get_transitions();

private:

    int state_number;

    bool acceptance_state;

    string acceptance_state_name;

    vector<pair <State, string>> transitions;

};

#endif //COMPILERS_STATE_H