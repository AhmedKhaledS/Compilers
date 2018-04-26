//
// Created by ahmed on 4/24/18.
//

#ifndef COMPILERS_PARSERTABLE_H
#define COMPILERS_PARSERTABLE_H

#include <map>
#include <string>
#include <vector>
#include "NonTerminal.h"

using namespace std ;

class ParserTable{
private:

    map< pair<string,string>, vector<pair<NonTerminal,string>> > predictive_parse_table;

    void insert_into_parse_table(string non_term, string term, vector<pair<NonTerminal, string>> Trans);


public:

    void build_parse_table( vector<NonTerminal> grammar_rules);
    vector<pair<NonTerminal,string>> fetch_from_parse_table( string non_term ,  string term );

};

#endif //COMPILERS_PARSERTABLE_H
