//
// Created by ahmed on 22/03/18.
//

#include "TransitionTable.h"
#include <vector>

using namespace std;

TransitionTable::TransitionTable()
{}

void TransitionTable::add(DFANode node, char input, DFANode *entry_node)
{
    t_table[{node.id, input}] = entry_node;
}

bool TransitionTable::search(DFANode *node)
{
    return node->registered_in_transition_table;
}

DFANode TransitionTable::get_entry(DFANode *dfa_node, char input)
{
    if (t_table.find({dfa_node->id, input}) != t_table.end());
        return *t_table[{dfa_node->id, input}];

    // Don't forget check for NULL value in the invoking function.
    return *t_table[{dfa_node->id, input}];
}
