//
// Created by ahmed on 22/03/18.
//

#include "DFANode.h"

using namespace std;

DFANode::DFANode(vector<State> dfa_state_, bool acc_state,
                 bool marked, bool reg_in_t_table, int id, string acc)
    : dfa_state(dfa_state_), acceptance_state(acc_state), marked(marked),
      registered_in_transition_table(reg_in_t_table), id(id), acceptance_state_name(acc)
{
}