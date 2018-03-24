//
// Created by ahmed on 16/03/18.
//

#include "DFATransformer.h"
#include <stack>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

#define NODES_SZ 1000
#define DFA_NODES 300
#define EPSILON "$"


DFATransformer::DFATransformer()
{
    functional_id = 0;
    parent = vector<int>(NODES_SZ, -1);
//    transitions.resize(NODES_SZ);
//    for (int i = 0; i < nfa_graph.size(); ++i)
//    {
//        for (pair<State, string> x : *nfa_graph[i].get_transitions())
//        {
//            transitions[i][x.second].push_back(x.first);
//        }
//    }
}

DFANode* DFATransformer::get_dfa_node(int id)
{
    return id_to_node[id];
}

void DFATransformer::add_dfa_node(DFANode *node, int id)
{
    id_to_node[id] = node;
}

void DFATransformer::transform()
{
    dfa_graph.resize(DFA_NODES);
    vector<State> starting_nfa_state;
    starting_nfa_state.push_back(nfa_graph[0]);
    DFANode starting_nfa_node(starting_nfa_state, false, false, false, 0);
    DFANode starting_dfa_node = normal_transition(starting_nfa_node, EPSILON);
    starting_dfa_node.id = functional_id++;
    dfa_nodes.push_back(starting_dfa_node);
    set<string> inputs = NFAGenerator::get_symbols();


    while (exist_unmarked_state(&dfa_nodes))
    {
        DFANode *current_dfa_node = get_unmarked_node(&dfa_nodes);
        DFANode sss = *current_dfa_node;
        current_dfa_node->marked = true;
        int node_id = current_dfa_node->id;
        for (set<string>::iterator it = inputs.begin();
             it != inputs.end(); it++)
        {
            DFANode result_node_without_eps = normal_transition(sss, *it);
            DFANode dfa_state = normal_transition(result_node_without_eps, EPSILON);
//            if (current_dfa_node->id == 0)
//                int debug = -1;
            if (!already_inserted_dfa_node(&dfa_state))
            {
                dfa_state.marked = false;
                dfa_state.id = functional_id++;
                dfa_nodes.push_back(dfa_state);
            }
            if (*it != EPSILON)
                dfa_graph[node_id].push_back({dfa_state, *it});
        }
    }
}

DFANode DFATransformer::normal_transition(DFANode dfa_state, string input)
{
    vector<State> dfa_trans;
    stack<State> stk_states;
    bool res_acceptance_state = false;

    /////////////////////////////////
    ////////////////////////////////

    for (State curr : dfa_state.dfa_state)
    {
        stk_states.push(curr);
        if (input == EPSILON)
            dfa_trans.push_back(curr);
        res_acceptance_state |= curr.is_acceptance_state();
    }
    while (!stk_states.empty())
    {
        State top = stk_states.top();
        stk_states.pop();
        for (pair<State, string> trans : *top.get_transitions())
        {
            if (trans.second == input)
            {
                if (!already_inserted(&dfa_trans, trans.first))
                {
                    res_acceptance_state |= trans.first.is_acceptance_state();
                    dfa_trans.push_back(nfa_graph[trans.first.get_state_number()]);
                    stk_states.push(nfa_graph[trans.first.get_state_number()]);
                }
            }
        }
    }
    DFANode new_dfa_node(dfa_trans, res_acceptance_state, false, false, -1);
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

bool DFATransformer::already_inserted(vector<State> *vec, State s) {
    for (State x : *vec)
    {
        if (x.get_state_number() == s.get_state_number())
            return true;
    }
    return false;
}

void DFATransformer::set_nfa_graph(std::vector<State> nfa)
{
    this->nfa_graph = nfa;
}

bool DFATransformer::exist_unmarked_state(std::vector<DFANode> *dfa_combined_nodes)
{
    for (DFANode x : *dfa_combined_nodes)
    {
        if (!x.marked)
            return true;
    }
    return false;
}

DFANode *DFATransformer::get_unmarked_node(std::vector<DFANode> *dfa_combined_nodes)
{
    for (int i = 0; i < (*dfa_combined_nodes).size(); ++i)
    {
        if (!(*dfa_combined_nodes)[i].marked)
            return &((*dfa_combined_nodes)[i]);
    }
}

bool DFATransformer::already_inserted_dfa_node(DFANode *dfa_node)
{
    set<int> st2;
    for (State y : dfa_node->dfa_state)
    {
        st2.insert(y.get_state_number());
    }
    for (DFANode x : dfa_nodes)
    {
        set<int> st1;
        for (State y : x.dfa_state)
        {
            st1.insert(y.get_state_number());
        }
        if (st1 == st2)
        {
            dfa_node->id = x.id;
            return true;
        }
    }
    return false;
}

std::vector<DFANode> *DFATransformer::get_dfa_nodes() {
    return &dfa_nodes;
}

vector< vector< pair<DFANode, string> > > *DFATransformer::get_dfa_graph()
{
    return &dfa_graph;
}

int DFATransformer::get_dfa_graph_size() {
    return functional_id;
};

