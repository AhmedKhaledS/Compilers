//
// Created by ahmed on 4/24/18.
//
#include <iostream>
#include <algorithm>
#include "ParserStack.h"
#include "../lexical_analyzer/LexicalController.h"

using namespace std ;

ParserStack::ParserStack(ParserTable table, pair<NonTerminal*, string> initial_state)
{
    empty.non_terminal = "";
    this->predictive_parse_table = table ;
    this->initial_parse_state = initial_state;
    initialize_stack();
}


void ParserStack::match_tokens(std::string current_token, Lexical_controller *input)
{
    while(!input_parsing_stack.empty())
    {
        if(input_parsing_stack.top().second != "") // TOS is a terminal.
        {
            if (current_token == input_parsing_stack.top().second)
            {
                cout << "Token: " << current_token << " is matched.\n";
                current_token = input->next_token();
            }
            else
                cout << "Missing the current TOS: " << input_parsing_stack.top().first->non_terminal <<"\n";
            input_parsing_stack.pop();
            print_stack();
        } else {
            string key_non_terminal =  input_parsing_stack.top().first->non_terminal;
            vector<pair<NonTerminal*,string> > replacement = predictive_parse_table.
                    fetch_from_parse_table(key_non_terminal, current_token);
//            input_parsing_stack.pop();
            if(replacement.empty())
            {
//                error_logger(Reject);
                cout << "No entry for the current token: " << current_token << ".\n";
                current_token = input->next_token();
            } else if (replacement[0].second == "Synch") {
//                error_logger(Synch);
                input_parsing_stack.pop();
                print_stack();
                cout << "The TOS of stack is a Non-Terminal that has a 'Synch' entry in the Parse-Table.\n";
            } else {
                input_parsing_stack.pop();
                if(replacement[0].second != "\\L")
                {
                    reverse(replacement.begin(),replacement.end());
                    for(pair<NonTerminal*,string> x : replacement)
                    {
                        input_parsing_stack.push(x);
                    }
                    cout << "TOS is a Non-Terminal and replaced by its transition.\n";
                }
                print_stack();

            }
        }
    }
    if (current_token != "$")
    {
        cout << "Error exist while matching!!!\n";
        exit(0);
    }
//    if (input_parsing_stack.top().second == "$" && current_token == "$")
//        return;
//
//    cout << "Error exist while matching!!!\n";
//    exit(0);
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
    this->input_parsing_stack.push({&empty,"$"});
    this->input_parsing_stack.push(initial_parse_state);
}

void ParserStack::print_stack()
{
    auto temp_stack = input_parsing_stack;
    while (!temp_stack.empty())
    {
        cout << (temp_stack.top().second != "" ? temp_stack.top().second : temp_stack.top().first->non_terminal) << " ";
        temp_stack.pop();
    }
    cout << endl;
}
