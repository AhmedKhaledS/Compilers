//
// Created by hisham on 22/03/18.
//

#ifndef COMPILERS_NFAOPERATIONS_H
#define COMPILERS_NFAOPERATIONS_H

#include "NFA.h"


class NFAOperations {

    public:

        NFA create_NFA();
        NFA create_NFA(char c);

        NFA oring(NFA x, NFA y);
        NFA concatenating(NFA x, NFA y);
        NFA kleene_closuring(NFA x);

        void copy_prev_states(NFA *nfa, std::vector<State> x);
        void copy_prev_states(NFA *nfa, std::vector<State> x, std::vector<State> y, int offset);

};


#endif //COMPILERS_NFAOPERATIONS_H
