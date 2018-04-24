//
// Created by ahmed on 4/24/18.
//
#include "ParserStack.h"
#include "LexicalController.h"

void ParserStack::ParserStack(ParserTable table ,
                              std::string initial_state)
{
    this->predictive_parse_table = table ;
    this->input_parsing_stack.push("$");
    this->input_parsing_stack.push(initial_state);
}

void ParserStack::run_string_matcher()
{
    while(input_parsing_stack.top() != "$" && != '$'){
        match_next();
    }
    if(input_parsing_stack.top() != "$" || input.at(input_index) != '$'){
        error_logger(Reject);
    }
}

void ParserStack::match_next()
{
    if(input.at(input_index) == input_parsing_stack.top()){
        input_parsing_stack.pop();
        input_index++;
    } else {
        input_parsing_stack.top();
        std::string temp = predictive_parse_table.fetch_from_parse_table();
        input_parsing_stack.pop();
        input_parsing_stack.push(temp);
    }



}