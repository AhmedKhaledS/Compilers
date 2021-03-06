//
// Created by ahmed on 24/04/18.
//

#ifndef COMPILERS_UTILITY_H
#define COMPILERS_UTILITY_H

#include <vector>
#include <string>
#include <set>
#include <map>
#include "NonTerminal.h"

class Utility {
private:
    static std::map<std::string, bool> cyclic_checker;

public:
    static void compute_first_terminals(NonTerminal *non_terminal, std::set<std::string> &first_set);

    static void compute_follow_terminals(NonTerminal *non_terminal, std::set<std::string> &follow_set);
};

#endif