//
// Created by ahmed on 4/24/18.
//
#include <iostream>
#include "ParserStack.h"
#include "../lexical_analyzer/LexicalController.h"

using namespace std ;

void ParserStack::ParserStack(ParserTable table, pair<NonTerminal, string> initial_state)
{
    NonTerminal empty;
    empty.non_terminal = "";
    this->predictive_parse_table = table ;
    this->initial_parse_state = initial_state;

    this->input_parsing_stack.push({});
    this->input_parsing_stack.push(initial_parse_state);
}

void ParserStack::run_string_matcher(Lexical_controller input)
{
    string temp = input.next_token();
    while(temp != ""){
        match_next(temp);
        temp = input.next_token();
    }
}

void ParserStack::match_next(std::string st)
{
    while(!input_parsing_stack.empty()){
        input_parsing_stack.pop();
    }
    this->input_parsing_stack.push("$");
    this->input_parsing_stack.push(initial_parse_state);

    while(input_parsing_stack.top())
    if(st == input_parsing_stack.top()){
        input_parsing_stack.pop();
        return ;
    } else {
        string temp = predictive_parse_table.fetch_from_parse_table(,st);
        if(temp == "Synch"){
            error_logger(Synch);
        } else if (temp == NULL) {
            error_logger(Panic);
        } else {
            input_parsing_stack.push(temp);
        }
    }
}

void ParserStack::error_logger(ERROR_ROUTINE err)
{
    switch (err){
        case Synch :
            //Synch routine
            std::cout << "Performing Synchronised recovery" << endl;
            break;
        case Panic :
            //Panic routine
            std::cout << "Performing Panicked recovery" << endl;
            break;
        case Correct :
            //Correct routine
            std::cout << "Missing Token :" << endl;
            break;
        case Reject :
            //Reject routine
            std::cout << "Aborting Program" << endl;
            break;
        default:
            std::cout << "Un-identified Error" << endl;

    }
}

