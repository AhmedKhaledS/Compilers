//
// Created by ahmed on 16/03/18.
//

#include "DFATransformer.h"
#include <stack>
#include <set>

using namespace std;

#define NODES_SZ 1000

DFATransformer::DFATransformer()
{
    functional_id = 0;
    parent = vector<int>(NODES_SZ, -1);
}

DFANode* DFATransformer::get_dfa_node(int id)
{
    return id_to_node[id];
}

void DFATransformer::add_dfa_node(DFANode *node, int id)
{
    id_to_node[id] = node;
}

vector< vector<pair <DFANode, char> > > DFATransformer::transform(vector<Transition> nfa_graph)
{
//    set<DFANode> unmarked_states;
//    //DFANode starting_node = normal_transition(starting_state), '$');
//    //unmarked_states.insert(starting_node);
//    stack<DFANode> marked_dfa_states;
//    /// (Important) unmarked_dfa_states.push(starting_node);
//    while (!unmarked_dfa_states.empty())
//    {
//        DFANode current = unmarked_dfa_states.top();
//        unmarked_dfa_states.pop();
//        //for (every input)
//        {
//            //DFANode dfa_state = normal_transition(normal_transition(current, nfa_state.), '$');
//            //if (unmarked_states.find(dfa_state) != unmarked_states.end())
//            {
//                //unmarked_states.insert(dfa_state);
                  //dfa_nodes.push_back(dfa_state);
//            }
//            //add(, input,dfa_state);
//        }
//    }
}

DFANode DFATransformer::normal_transition(DFANode *dfa_state, char input)
{
    vector<State> dfa_trans;
    stack<State> stk_states;
    bool res_acceptance_state = false;
    for (State curr : dfa_state->dfa_state)
    {
        stk_states.push(curr), dfa_trans.push_back(curr);
        res_acceptance_state |= curr.is_acceptance_state();
    }
    while (!stk_states.empty())
    {
        State top = stk_states.top();
        stk_states.pop();
     //   for (vector< pair<State, char> > trans : top.get_transitions())
        {
            if (trans.get_value() == input)
            {
                //if (dfa_trans.find(trans.get_destination()))
                {
                    //res_acceptance_state |= trans.get_destination().is_acceptance_state();
                    //dfa_trans.push_back(trans.get_destination());
                    stk_states.push(trans.get_destination());
                }
            }
        }
    }
    DFANode new_dfa_node(dfa_trans, res_acceptance_state, false, false, functional_id++);
    return new_dfa_node;
}

int DFATransformer::find_parent(int node)
{
    if(parent[node] == -1)
        return node;
    return parent[node] = find_parent(parent[node]);
}

bool DFATransformer::merge_nodes(int node1, int node2)
{
    int parentA = find_parent(node1);
    int parentB = find_parent(node2);
    if(parentA == parentB)
        return false;
    parent[parentB] = parentA;
    return true;
}