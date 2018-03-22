//
// Created by hisham on 22/03/18.
//

#include "Transition.h"


Transition::Transition(int destination,char value) {
    this->destination = destination;
    this-> value = value;
}


int Transition::get_destination() {
    return this->destination;
}

char Transition::get_value() {
    return this->value;
}
