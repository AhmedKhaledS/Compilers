//
// Created by ahmed on 16/03/18.
//

#include "DFATransformer.h"
#include <vector>

using namespace std;
DFATransformer::DFATransformer()
{}

DFANode DFATransformer::get_dfa_node(int id)
{
    return id_to_node[id];
}