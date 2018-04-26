//
// Created by ahmed on 4/24/18.
//
#include "ParserTable.h"

void ParserTable::build_parse_table( vector<NonTerminal> grammar_rules)
{
    for(int i = 0 ; i < grammar_rules.size() ; i++){
        vector<vector<pair<NonTerminal,string>>> production = grammar_rules[i].productions;
        for(int j = 0 ; j < production.size() ; j++){
            if(production[j][0].second == ""){
                for(string z : production[j][0].first.first){
                    vector<pair<NonTerminal,string>> trans = production[j] ;
                    insert_into_parse_table(grammar_rules[i].name,z,trans);
                }
            } else {
                vector<pair<NonTerminal,string>> trans = production[j];
                insert_into_parse_table(grammar_rules[i].name,production[j][0].second,trans);
            }
        }

    }





}

void ParserTable::insert_into_parse_table(string non_term, string term, vector<pair<NonTerminal, string>> Trans)
{
    pair<string , string> key ;
    key.first = non_term ;
    key.second = term ;
    pair < pair<string,string> , vector<pair<NonTerminal,string>> > input(key , Trans) ;
    predictive_parse_table.insert(input);
}

vector<pair<NonTerminal,string>> ParserTable::fetch_from_parse_table( string non_term ,  string term )
{
    pair<string , string> key ;
    key.first = non_term ;
    key.second = term ;
    map< pair<string,string>, vector<pair<NonTerminal,string>> > :: iterator it ;
    it = predictive_parse_table.find(key);
    if (it != predictive_parse_table.end()){

        return it->second;
    }

    vector<pair<NonTerminal,string>> empty;

    return empty ;

};
