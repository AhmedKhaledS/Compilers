//
// Created by ahmed on 24/04/18.
//

#include "ParserController.h"
#include "../lexical analyzer/automata/Helper.h"

#include <iostream>

using namespace std;

void ParserController::construct_grammar() {
    add_grammar_rule("S = B C A | 'X'");
    add_grammar_rule("B = A B C B");
    add_grammar_rule("C = A 'id' B 'x' | 'C' | 'c' B C A");
    add_grammar_rule("A = 'Z' | \\L");
}

void ParserController::construct_non_terminals() {

    Helper helper;

    for (int i = 0; i < grammar_rules.size(); ++i) {

        vector<string> equal_tokens = helper.tokenaize(grammar_rules[i], '=');

        add_non_terminal(equal_tokens[0]);
    }
}

void ParserController::construct_terminals() {

    Helper helper;

    for (int i = 0; i < grammar_rules.size(); ++i) {

        vector<string> equal_tokens = helper.tokenaize(grammar_rules[i], '=');
        vector<string> or_tokens = helper.tokenaize(equal_tokens[1], '|');

        for (int j = 0; j < or_tokens.size(); ++j) {

            vector<string> current_tokens = helper.tokenaize(or_tokens[j], ' ');

            for (int k = 0; k < current_tokens.size(); ++k) {

                string current = current_tokens[k];
                if(is_terminal(current)) {
                    add_terminal(current.substr(1, current.length() - 2));
                } else if (is_epsilon(current)) {
                    add_terminal(current);
                }

            }
        }
    }

}

void ParserController::construct_non_terminals_classes() {

    for (int i = 0; i < non_terminals.size(); ++i) {

        non_terminals_classes[non_terminals[i]] = NonTerminal(non_terminals[i]);

    }

}

void ParserController::construct_productions() {

    Helper helper;

    for (int i = 0; i < grammar_rules.size(); ++i) {

        vector<string> equal_tokens = helper.tokenaize(grammar_rules[i], '=');
        vector<string> or_tokens = helper.tokenaize(equal_tokens[1], '|');

        NonTerminal &current_non_terminal = non_terminals_classes[equal_tokens[0]];
        vector<vector<pair<NonTerminal, string>>> productions;

        for (int j = 0; j < or_tokens.size(); ++j) {

            vector<string> current_tokens = helper.tokenaize(or_tokens[j], ' ');
            vector<pair<NonTerminal, string>> single_production;

            for (int k = 0; k < current_tokens.size(); ++k) {

                string current = current_tokens[k];
                pair<NonTerminal, string> single_identifier;

                if(is_terminal(current)) {
                    NonTerminal temp_class("");
                    single_identifier.first = temp_class;
                    single_identifier.second = current.substr(1, current.length() - 2);
                } else if(is_epsilon(current)) {
                    NonTerminal temp_class("");
                    single_identifier.first = temp_class;
                    single_identifier.second = "";
                } else {

                    // Check for valid non-terminal
                    if(non_terminals_classes.find(current) == non_terminals_classes.end()) {
                        cout << "Error: " << current << " can't be resolved as a non-terminal" << endl;
                        exit(0);
                    }

                    single_identifier.first = non_terminals_classes[current];
                    single_identifier.second = "";
                }

                single_production.push_back(single_identifier);
            }

            productions.push_back(single_production);
        }

        current_non_terminal.productions = productions;
    }

}

void ParserController::construct_follow_helper() {

    Helper helper;

    for (int i = 0; i < non_terminals.size(); ++i) {

        NonTerminal &parent = non_terminals_classes[non_terminals[i]];
        vector<vector<pair<NonTerminal, string>>> productions = parent.productions;

        for (int j = 0; j < productions.size(); ++j) {

            vector<pair<NonTerminal, string> > current_production = productions[j];

            for (int k = 0; k < current_production.size(); ++k) {

                if (is_non_terminal(current_production[k].first)) {

                    string non_terminal_name = current_production[k].first.non_terminal;
                    NonTerminal &child = non_terminals_classes[non_terminal_name];

                    vector<pair<NonTerminal, string>> follow_ups;

                    for (int l = k + 1; l < current_production.size(); ++l) {
                        follow_ups.push_back(current_production[l]);
                    }

                    pair<vector<pair<NonTerminal, string>>, NonTerminal> paired_follow_ups;
                    paired_follow_ups.first = follow_ups;
                    paired_follow_ups.second = parent;
                    child.follow_helper.push_back(paired_follow_ups);
                }
            }
        }

    }
}



void ParserController::run_parser() {


    // TO DO: Read from actual file...
    construct_grammar();

    construct_non_terminals();

    construct_terminals();

    construct_non_terminals_classes();

    construct_productions();

    // print_productions();

    construct_follow_helper();

    // print_follow_helper();

    // TO DO: CALL FIRST()
    // TO DO: CALL FOLLOW()
    // TO DO: CALL CONSTRUCT_PARSE_TABLE()
    // TO DO: CALL SIMULATE_STACK()

}



void ParserController::add_grammar_rule(string grammar_rule) {
    grammar_rules.push_back(grammar_rule);
}

void ParserController::add_non_terminal(string non_terminal) {
    non_terminals.push_back(non_terminal);
}

void ParserController::add_terminal(string terminal) {
    terminals.push_back(terminal);
}



bool ParserController::is_terminal(string token) {
    return token[0] == '\'' && token[token.length() - 1] == '\'';
}

bool ParserController::is_epsilon(string token) {
    return token[0] == '\\';
}

bool ParserController::is_non_terminal(NonTerminal nonTerminal) {
    return nonTerminal.non_terminal != "";
}



void ParserController::print_productions() {

    for (int i = 0; i < non_terminals.size(); ++i) {
        string non_terminal = non_terminals[i];
        NonTerminal non_terminal_class = non_terminals_classes[non_terminal];

        cout << non_terminal_class.non_terminal << " = ";

        vector<vector<pair<NonTerminal, string>>> productions = non_terminal_class.productions;

        for (int j = 0; j < productions.size(); ++j) {
            vector<pair<NonTerminal, string>> single_production = productions[j];
            for (int k = 0; k < single_production.size(); ++k) {
                if(single_production[k].first.non_terminal != "") {
                    cout << single_production[k].first.non_terminal << " ";
                } else if(single_production[k].second != "") {
                    cout << single_production[k].second << " ";
                } else {
                    cout << "\\L" << " ";
                }
            }
            if(j != productions.size() - 1)
                cout << "| ";
        }
        cout << endl;
    }

}

void ParserController::print_follow_helper() {
    for (int i = 0; i < non_terminals.size(); ++i) {
        print_current_follow_helper(non_terminals[i]);
    }
}

void ParserController::print_current_follow_helper(string non_terminal) {

    cout << "Non-Terminal: " << non_terminal << endl;

    vector<pair<vector<pair<NonTerminal, string>>, NonTerminal>> follow_helper =
            non_terminals_classes[non_terminal].follow_helper;

    for (int l = 0; l < follow_helper.size(); ++l) {
        pair<vector<pair<NonTerminal, string>>, NonTerminal> current_production = follow_helper[l];

        vector<pair<NonTerminal, string>> productions = current_production.first;
        cout << "Number#" << l+1 << "(size:" << productions.size() << ") ";
        for (int i = 0; i < productions.size(); ++i) {

            if(productions[i].first.non_terminal != "") {
                cout << productions[i].first.non_terminal << " ";
            } else if(productions[i].second != "") {
                cout << productions[i].second << " ";
            } else {
                cout << "\\L" << " ";
            }

        }

        cout << " (Parent:" << current_production.second.non_terminal << ")" << endl;
    }

    cout << endl;
}