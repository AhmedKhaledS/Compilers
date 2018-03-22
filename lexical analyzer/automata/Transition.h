//
// Created by hisham on 22/03/18.
//

#ifndef COMPILERS_TRANSITION_H
#define COMPILERS_TRANSITION_H


class Transition {

    public:

        Transition(int destination,char value);

        int get_destination();
        char get_value();


    private:

        int destination;
        char value;


};


#endif //COMPILERS_TRANSITION_H
