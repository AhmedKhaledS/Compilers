//
// Created by ahmed on 22/03/18.
//

#include "DFANode.h"

using namespace std;

DFANode::DFANode(bool acc_state, bool marked, bool reg_in_t_table, int id)
    : acceptance_state(acc_state), marked(marked), registered_in_transition_table(reg_in_t_table)
        , id(id)
{
}