//
// Created by ahmed on 24/04/18.
//

#include "Utility.h"
#include <algorithm>

using namespace std;

void Utility::compute_first_terminals(NonTerminal *non_terminal, set<string> &first_set)
{
    if (!non_terminal->first.empty())
        return;
    for (int i = 0; i < non_terminal->productions.size(); ++i)
    {
        vector< pair<NonTerminal, string > > current_rule = non_terminal->productions[i];
        if (!current_rule.empty())
        {
            if (current_rule[0].second != "")
            {
                first_set.insert(current_rule[0].second);
            }
            else
            {
                //set<string> first_set_aux;
                compute_first_terminals(&current_rule[0].first, current_rule[0].first.first);
                first_set.insert(current_rule[0].first.first.begin(), current_rule[0].first.first.end());
            }
        }
    }
}

void Utility::compute_follow_terminals(NonTerminal *non_terminal, set<string> &follow_set)
{
    /// Iterate over each line in follow_productions.
    for (int i = 0; i < non_terminal->follow_helper.size(); ++i)
    {
        NonTerminal parent = non_terminal->follow_helper[i].second;
        auto next_tokens = non_terminal->follow_helper[i].first;
        if (next_tokens.empty()) // Get the follow of the parent.
        {
            set<string> follow_set_aux;
            compute_follow_terminals(&parent, follow_set_aux);
            follow_set.insert(follow_set_aux.begin(), follow_set_aux.end());
        }
        for (int j = 0; j < non_terminal->follow_helper[i].first.size(); ++j)
        {
            NonTerminal current_non_terminal = non_terminal->follow_helper[i].first[j].first;
            string terminal_name = non_terminal->follow_helper[i].first[j].second;
            if (current_non_terminal.non_terminal == "" && terminal_name != "") // Terminal symbol case.
            {
                follow_set.insert(terminal_name);
                break;
            }
//            else if (current_non_terminal.non_terminal == "" && terminal_name == "") // Epsilon case.
//            {
//                if (j + 1 ==  non_terminal->follow_helper[i].first.size()) // Add follow of the parent;
//                {
//                    set<string> follow_set_aux;
//                    compute_follow_terminals(&parent, follow_set_aux);
//                    follow_set.insert(follow_set_aux.begin(), follow_set_aux.end());
//                }
//                continue;
//            }
            else // Non-terminal case.
            {
                set<string> first_of_current_non_terminal = current_non_terminal.first;
                if (first_of_current_non_terminal.count("\\L") != 0) // Epsilon exists!
                {
                    first_of_current_non_terminal.erase(first_of_current_non_terminal.find("\\L"));
                    follow_set.insert(first_of_current_non_terminal.begin(), first_of_current_non_terminal.end());
                    continue;
                }
                else // Epsilon doesn't exist.
                {
                    follow_set.insert(first_of_current_non_terminal.begin(), first_of_current_non_terminal.end());
                }
                break;
            }

        }
    }
}

