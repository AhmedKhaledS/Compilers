//
// Created by ahmed on 4/24/18.
//
#include "ParserTable.h"

void ParserTable::build_parse_table(std::vector<NonTerminal> grammar_rules)
{
    for(int i = 0 ; i < grammar_rules.size() ; i++ ){
        for(int j = 0 ; j < grammar_rules[i].productions.size() ; j++){
            if(grammar_rules[i].productions[j][0].second == ""){

                for(int k = 0 ; k < grammar_rules[i].productions[])
                insert_into_parse_table(grammar_rules[i].non_terminal ,
                                        grammar_rules[i].productions[0][0].first[0] ,
                                        )
            }

        }

    }





}
void ParserTable::insert_into_parse_table(std::string , std::string , std::string)
{










}

