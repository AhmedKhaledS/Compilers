//
// Created by ahmed on 4/24/18.
//

#ifndef COMPILERS_PARSERTABLE_H
#define COMPILERS_PARSERTABLE_H

#include <map>
#include <string>
#include <vector>
#include "NonTerminal.h"


class ParserTable{
private:
    std::map< std::pair<std::string,std::string>, std::vector<std::string> > predictive_parse_table;
    void insert_into_parse_table(std::string , std::string , std::vector<std::string> );
public:
    void build_parse_table(std::vector<NonTerminal> grammar_rules);
    std::vector<std::string> fetch_from_parse_table(std::string , std::string );
};

#endif //COMPILERS_PARSERTABLE_H
