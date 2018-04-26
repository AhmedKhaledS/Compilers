//
// Created by hisham on 24/04/18.
//

#ifndef COMPILERS_NONTERMINAL_H
#define COMPILERS_NONTERMINAL_H

#include <string>
#include <vector>
#include <set>

using namespace std;


class NonTerminal {

    public:

        NonTerminal();

        NonTerminal(string non_terminal_name);

        string non_terminal;
        vector<vector<pair<NonTerminal, string>>> productions;
        set<string> first;
        set<string> follow;
        vector<pair<vector<pair<NonTerminal,string>>, NonTerminal>> follow_helper;
        bool starting_state;
};


#endif //COMPILERS_NONTERMINAL_H
