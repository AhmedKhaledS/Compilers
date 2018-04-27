//
// Created by ahmed on 4/24/18.
//
#include <iostream>
#include "ParserTable.h"


ParserTable::ParserTable()
{
    empty.non_terminal = "";
}
void ParserTable::build_parse_table( vector<NonTerminal> grammar_rules)
{
    for(int i = 0 ; i < grammar_rules.size() ; i++){

        vector<vector<pair<NonTerminal*, string>>> production = grammar_rules[i].productions;
        for(int j = 0 ; j < production.size() ; j++){
            if(production[j][0].second == ""){ //if non-terminal
                for(string z : production[j][0].first->first){
                    vector<pair<NonTerminal*,string>> trans = production[j] ;
                    insert_into_parse_table(grammar_rules[i].non_terminal, z, trans);
                }
            } else if(production[j][0].second == "\\L"){//else terminal and epsilon
                for(string z : grammar_rules[i].follow){
                    vector<pair<NonTerminal*,string>> trans = production[j];
                    insert_into_parse_table(grammar_rules[i].non_terminal, z, trans);
                }

            } else { //else terminal and not epsilon
                vector<pair<NonTerminal*,string>> trans = production[j];
                insert_into_parse_table(grammar_rules[i].non_terminal,production[j][0].second,trans);
            }
        }

        // Inserting Synchronization points
        for (string z : grammar_rules[i].follow)
        {
            vector<pair<NonTerminal*, string>> trans ;
            trans.push_back({&empty,"Synch"});
            insert_into_parse_table(grammar_rules[i].non_terminal, z, trans);
        }
    }



    // std::cout << "Test Finished" << std::endl;

}

void ParserTable::insert_into_parse_table(string non_term, string term, vector<pair<NonTerminal*, string>> Trans)
{
    pair<string , string> key ;
    key.first = non_term ;
    key.second = term ;
    pair < pair<string,string> , vector<pair<NonTerminal*,string>> > input(key , Trans);
    auto fetched_data = fetch_from_parse_table(non_term, term);
    if (Trans[0].second == "Synch" && !fetched_data.empty()) // Case of overwriting with Synch.
        return;
    if (!fetched_data.empty()) // Case of insertion on a non-empty entry.
    {
        cout << "Duplicates appeared while constructing Parse table under: \nNon-Terminal: "
                << non_term << " -- Terminal: " << term << endl;
        exit(0);
    }
    predictive_parse_table.insert(input);
}

vector<pair<NonTerminal*,string>> ParserTable::fetch_from_parse_table( string non_term ,  string term )
{
    pair<string , string> key ;
    key.first = non_term ;
    key.second = term ;
    auto it = predictive_parse_table.find(key);
    if (it != predictive_parse_table.end())
    {
        return it->second;
    }

    vector<pair<NonTerminal*, string>> empty;

    return empty;

};

map< pair<string,string>, vector<pair<NonTerminal*,string>> > ParserTable::get_parse_table()
{
    return this->predictive_parse_table;
}