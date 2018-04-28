//
// Created by ahmed on 4/24/18.
//

#include "printing/table_printer.h"
#define _USE_MATH_DEFINES
#include <math.h>

#if defined(USE_BOOST_KARMA)
#include <boost/spirit/include/karma.hpp>
namespace karma = boost::spirit::karma;
#endif

using bprinter::TablePrinter;

#include <iostream>
#include <algorithm>
#include "ParserStack.h"
#include "../lexical_analyzer/file_services/FileWriter.h"
#include "../lexical_analyzer/LexicalController.h"
#include "../lexical_analyzer/automata/Helper.h"

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

    TablePrinter tp(&std::cout);
    tp.AddColumn("Stack", 90);
    tp.AddColumn("Input", 40);
    tp.AddColumn("Action", 40);
    tp.PrintHeader();

    string matched_string = "";
    tp << print_stack();
    tp << current_token;
    left_most_derivation.push_back(input_parsing_stack.top().first->non_terminal + " $");

    while(!input_parsing_stack.empty())
    {
        if(input_parsing_stack.top().second != "") // TOS is a terminal.
        {
            string tmp = current_token;
            if (current_token == input_parsing_stack.top().second) { // Matched
                tp << "Matched Token";
                current_token = input->next_token();
                matched_string += tmp + " ";
            } else { // Not Matched
                matched_string += input_parsing_stack.top().second;
               tp << "Error: Missing Token, but Inserted";
            }
            input_parsing_stack.pop();

            tp << print_stack();
            tp << current_token;

        } else {
            string key_non_terminal =  input_parsing_stack.top().first->non_terminal;
            vector<pair<NonTerminal*,string> > replacement = predictive_parse_table.
                    fetch_from_parse_table(key_non_terminal, current_token);

            if(replacement.empty()) // Empty Entry
            {

                tp << "Error: No Transition, Skip this Input";

                string prev_token = current_token;
                current_token = input->next_token();

                if(prev_token == "$" && current_token == "$") {
                    break;
                }

                tp << print_stack();
                tp << current_token;

            } else if (replacement[0].second == "Synch") { // Sync Entry

                tp << "Error: Synch Transition, Pop TOS";

                input_parsing_stack.pop();

                tp << print_stack();
                tp << current_token;

            } else {

                tp << "Transition";

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

                tp << print_stack();
                tp << current_token;

            }
        }
    }

    if (current_token != "$")
    {
        tp << "";
        cout << "Error exist after matching: Some tokens from the user are discarded!!!\n";
        tp.PrintFooter();
        // exit(1);
    } else if (!input_parsing_stack.empty()) {
        tp.PrintFooter();
        cout << "Error exist after matching: Some tokens form the user can not be matched!!!\n";
        // exit(2);
    } else {
        tp << "Done";
        tp.PrintFooter();
        cout << "Successfully parsed\n";
    }


    cout << "\n\nLeft-most derivation predictive parsing: \n";
    for (auto curr : left_most_derivation)
        cout << curr << endl;


    File_Writer parser_file;
    parser_file.write("parsing_file.txt", left_most_derivation);

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

string ParserStack::print_stack()
{

    Helper h;

    string output = "";
    // cout << endl;
    auto temp_stack = input_parsing_stack;
    while (!temp_stack.empty())
    {
        string tmp = (temp_stack.top().second != "" ? temp_stack.top().second : temp_stack.top().first->non_terminal);
        output.append(tmp + " ");
        // cout << tmp << " ";
        temp_stack.pop();
    }

    h.trim(output);

    // output is here
    return output;
}
