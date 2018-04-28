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
    string matched_string = "";
    print_stack();
    left_most_derivation.push_back(input_parsing_stack.top().first->non_terminal + " $");
    while(!input_parsing_stack.empty())
    {
        if(input_parsing_stack.top().second != "") // TOS is a terminal.
        {
            string tmp = current_token;
            if (current_token == input_parsing_stack.top().second)
                current_token = input->next_token();
            input_parsing_stack.pop();
        //    left_most_derivation.push_back(matched_string + tmp + " ");
            matched_string += tmp + " ";
            cout << "\t\tMatch(" << matched_string << ")";
            print_stack();
        } else {
            string key_non_terminal =  input_parsing_stack.top().first->non_terminal;
            vector<pair<NonTerminal*,string> > replacement = predictive_parse_table.
                    fetch_from_parse_table(key_non_terminal, current_token);
//            input_parsing_stack.pop();
            if(replacement.empty())
            {
//                error_logger(Reject);
                current_token = input->next_token();
            } else if (replacement[0].second == "Synch") {
//                error_logger(Synch);
                input_parsing_stack.pop();
                print_stack();
            } else {

                input_parsing_stack.pop();
                if(replacement[0].second != "\\L")
                {
                    reverse(replacement.begin(),replacement.end());
                    for(pair<NonTerminal*,string> x : replacement)
                    {
                        input_parsing_stack.push(x);
                    }
                }
                left_most_derivation.push_back(matched_string + (matched_string == ""? "" : " "));
                auto temp_stack = input_parsing_stack;
                while (!temp_stack.empty())
                {
                    string tmp = (temp_stack.top().second != "" ?
                                  temp_stack.top().second : temp_stack.top().first->non_terminal);
                    left_most_derivation.back().append(tmp + " ");
                    temp_stack.pop();
                }
                print_stack();

            }
        }
    }
    cout << "\n\nLeft-most derivation predictive parsing: \n";
    if (current_token != "$")
    {
        cout << "Error exist while matching!!!\n";
        exit(0);
    }
    for (auto curr : left_most_derivation)
        cout << curr << endl;
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
    cout << endl;
    auto temp_stack = input_parsing_stack;
    while (!temp_stack.empty())
    {
        string tmp = (temp_stack.top().second != "" ? temp_stack.top().second : temp_stack.top().first->non_terminal);
        cout << tmp << " ";
        temp_stack.pop();
    }
}
