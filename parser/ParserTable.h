//
// Created by ahmed on 4/24/18.
//

#ifndef COMPILERS_PARSERTABLE_H
#define COMPILERS_PARSERTABLE_H

#include <map>
#include <string>


class ParserTable{
private:
    std::map< std::pair<std::string,std::string>, std::string > predictive_parse_table;
    void insert_into_parse_table(std::string , std::string , std::string );
public:
    void build_parse_table();
    void fetch_from_parse_table();
};

#endif //COMPILERS_PARSERTABLE_H
