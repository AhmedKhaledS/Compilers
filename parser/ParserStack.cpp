//
// Created by ahmed on 4/24/18.
//
#include <iostream>
#include <algorithm>
#include "ParserStack.h"
#include "../lexical_analyzer/LexicalController.h"

using namespace std ;

void ParserStack::ParserStack(ParserTable table, pair<NonTerminal*, string> initial_state)
{
    this->predictive_parse_table = table ;
    this->initial_parse_state = initial_state;
    initialize_stack();
}

void ParserStack::run_string_matcher(Lexical_controller input)
{
    string temp = input.next_token();
    while(temp != ""){
        match_token(temp);
        temp = input.next_token();
    }
}

void ParserStack::match_token(std::string st)
{
    while(!input_parsing_stack.empty()){
        input_parsing_stack.pop();
    }
    initialize_stack();

    while(input_parsing_stack.top().second != "$" ){

        if(st == input_parsing_stack.top().second){
            input_parsing_stack.pop();
            if(input_parsing_stack.size() > 1)
                error_logger(Reject);
            else
                cout << "Matched Input , Getting next .." << endl;
            return;
        } else if(input_parsing_stack.top().second != ""){
            input_parsing_stack.pop();
            if(input_parsing_stack.size() > 1)
                error_logger(Reject);
            else
                error_logger(Missing);
            return;
        } else {
            string key_non_terminal =  input_parsing_stack.top().first->non_terminal;
            input_parsing_stack.pop();
            vector<pair<NonTerminal*,string>> replacement = predictive_parse_table.fetch_from_parse_table(key_non_terminal,st);
            if(replacement.empty()){
                error_logger(Reject);
            } else if (replacement[0].second == "Synch") {
                error_logger(Synch);
            } else {
                if(replacement[0].second == "\\L")
                    continue;
                reverse(replacement.begin(),replacement.end());
                for(pair<NonTerminal*,string> x : replacement){
                    input_parsing_stack.push(x);
                }
            }
        }
    }
}

void ParserStack::error_logger(ERROR_ROUTINE err)
{
    switch (err){
        case Synch :
            input_parsing_stack.pop();
            cout << "Performing Synchronised recovery" << endl;
            break;
        case Missing :
            cout << "Non-Terminals don`t match , a token must be missing" << endl;
            break;
        case Reject :
            cout << "Unmatched Input , Skipping to next .." << endl;
            break;
        default:
            cout << "Un-identified Error" << endl;

    }
}

void ParserStack::initialize_stack()
{
    NonTerminal *empty ;
    empty->non_terminal = "";
    this->input_parsing_stack.push({empty,"$"});
    this->input_parsing_stack.push(initial_parse_state);
}