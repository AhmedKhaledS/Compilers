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

        string non_terminal;
        vector<vector<pair<NonTerminal, string>>> productions;
        set<string> first;
        set<string> follow;
        vector<pair<vector<pair<NonTerminal,string>>, NonTerminal>> follow_helper;

};


#endif //COMPILERS_NONTERMINAL_H
