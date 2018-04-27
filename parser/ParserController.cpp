//
// Created by ahmed on 24/04/18.
//

#include "printing/table_printer.h"
#define _USE_MATH_DEFINES
#include <math.h>

#if defined(USE_BOOST_KARMA)
#include <boost/spirit/include/karma.hpp>
namespace karma = boost::spirit::karma;
#endif

using bprinter::TablePrinter;

#include "ParserController.h"
#include "../lexical_analyzer/automata/Helper.h"
#include "GrammarNormalizer.h"
#include "Utility.h"
#include "../lexical_analyzer/file_services/GrammarReader.h"
#include "algorithm"


#include <iostream>

using namespace std;

void ParserController::run_parser(const string grammar_rule_file) {

    construct_grammar(grammar_rule_file);

    GrammarNormalizer normalizer(grammar_rules);

    /* START: FOR TESTING */
    cout << "STEP(0): Actual grammar from file" << endl;
    normalizer.print_grammar(grammar_rules);
    /* END: FOR TESTING */

    normalizer.perform_grammar_normalization();
    grammar_rules.clear();
    grammar_rules = normalizer.normalized_grammar;


    /* FOR TESTING */
    cout << "STEP (2): Performing Left Factoring (Working Version)" << endl;
    normalizer.print_grammar(grammar_rules);

    construct_non_terminals();

    construct_terminals();

    /* FOR TESTING */
    cout << "STEP (2.1): Terminals" << endl;
    normalizer.print_grammar(terminals);

    /* FOR TESTING */
    cout << "STEP (2.2): Non-Terminals" << endl;
    normalizer.print_grammar(non_terminals);

    construct_non_terminals_classes();

    construct_productions();

    /* FOR TESTING */
    print_productions();

    construct_follow_helper();

    /* FOR TESTING */
    print_follow_helper();

    // TO DO: CALL FIRST()
    for (int i = 0; i < non_terminals.size(); ++i) {

        Utility::compute_first_terminals(non_terminals_classes[non_terminals[i]],
                                         non_terminals_classes[non_terminals[i]]->first);
    }

    for (int i = 0; i < non_terminals.size(); ++i) {

        Utility::compute_follow_terminals(non_terminals_classes[non_terminals[i]],
                                          non_terminals_classes[non_terminals[i]]->follow);
    }

    for (int i = 0; i < non_terminals.size(); ++i) {

        cout << "First of " << non_terminals_classes[non_terminals[i]]->non_terminal << " ";

        for (auto it = non_terminals_classes[non_terminals[i]]->first.begin();
             it != non_terminals_classes[non_terminals[i]]->first.end(); ++it)
            cout << *it << " ";

        cout << endl;

    }

    cout << endl;

    for (int i = 0; i < non_terminals.size(); ++i) {

        cout << "Follow of " << non_terminals_classes[non_terminals[i]]->non_terminal << " ";

        for (auto it = non_terminals_classes[non_terminals[i]]->follow.begin();
             it != non_terminals_classes[non_terminals[i]]->follow.end(); ++it)
            cout << *it << " ";

        cout << endl;
    }

    TablePrinter tp(&std::cout);

    vector<NonTerminal> non_ts;
    ParserTable parse_table;

    tp.AddColumn("Non-Terminals", 15);
    for (string t : terminals) {
        if(t == "\\L") {
            t = "$";
        }
        tp.AddColumn(t, 10);
    }
    tp.PrintHeader();

    for (string non_t : non_terminals)
    {
        non_ts.push_back(*non_terminals_classes[non_t]);
    }
    parse_table.build_parse_table(non_ts);
    auto table = parse_table.get_parse_table();
    for (string non_terminal_sym : non_terminals)
    {
        tp << non_terminal_sym;
        for (string terminal_sym : terminals)
        {
            if (terminal_sym == "\\L")
                terminal_sym = "$";
            auto tmp = parse_table.fetch_from_parse_table(non_terminal_sym, terminal_sym);
            string production = "";
            for (auto curr : tmp)
            {
                if (curr.second == "")
                    production.append(curr.first->non_terminal + " ");
                else
                    production.append(curr.second + " ");
            }
            tp << production;
        }
    }
    tp.PrintFooter();
    // TO DO: CALL CONSTRUCT_PARSE_TABLE()
    // TO DO: CALL SIMULATE_STACK()

}

void ParserController::construct_grammar(const string grammar_rule_file) {

    Grammar_Reader x;
    int line_count = 1;

    while(x.read_next_grammar_rule_line(grammar_rule_file, line_count) != "~") {

        string grammar_rule = x.read_next_grammar_rule_line(grammar_rule_file, line_count);
        line_count++;

        while(x.read_next_grammar_rule_line(grammar_rule_file, line_count)[0] == '|') {
            grammar_rule.append(" ");
            grammar_rule.append(x.read_next_grammar_rule_line(grammar_rule_file, line_count));
            line_count++;
        }

        grammar_rule = grammar_rule.substr(2,grammar_rule.size() - 2);
        add_grammar_rule(grammar_rule);
    }
}

void ParserController::construct_non_terminals() {

    Helper helper;

    for (int i = 0; i < grammar_rules.size(); ++i) {

        vector<string> equal_tokens = helper.tokenaize_first(grammar_rules[i], '=');

        add_non_terminal(equal_tokens[0]);
    }
}

void ParserController::construct_terminals() {

    Helper helper;

    for (int i = 0; i < grammar_rules.size(); ++i) {

        vector<string> equal_tokens = helper.tokenaize_first(grammar_rules[i], '=');
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

        non_terminals_classes[non_terminals[i]] = new
                NonTerminal(non_terminals[i]);

    }

}

void ParserController::construct_productions() {

    Helper helper;

    for (int i = 0; i < grammar_rules.size(); ++i) {

        vector<string> equal_tokens = helper.tokenaize_first(grammar_rules[i], '=');
        vector<string> or_tokens = helper.tokenaize(equal_tokens[1], '|');

        NonTerminal &current_non_terminal = *non_terminals_classes[equal_tokens[0]];
        vector<vector<pair<NonTerminal*, string>>> productions;

        for (int j = 0; j < or_tokens.size(); ++j) {

            vector<string> current_tokens = helper.tokenaize(or_tokens[j], ' ');
            vector<pair<NonTerminal*, string>> single_production;

            for (int k = 0; k < current_tokens.size(); ++k) {

                string current = current_tokens[k];
                pair<NonTerminal*, string> single_identifier;

                if(is_terminal(current)) {
                    single_identifier.first = new NonTerminal("");
                    single_identifier.second = current.substr(1, current.length() - 2);
                } else if(is_epsilon(current)) {
                    single_identifier.first = new NonTerminal("");
                    single_identifier.second = "\\L";
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

    for (int i = 0; i < non_terminals.size(); ++i) {

        NonTerminal &parent = *non_terminals_classes[non_terminals[i]];
        vector<vector<pair<NonTerminal*, string>>> productions = parent.productions;

        for (int j = 0; j < productions.size(); ++j) {

            vector<pair<NonTerminal*, string> > current_production = productions[j];

            for (int k = 0; k < current_production.size(); ++k) {

                if (is_non_terminal(*current_production[k].first)) {

                    string non_terminal_name = current_production[k].first->non_terminal;
                    NonTerminal &child = *non_terminals_classes[non_terminal_name];

                    vector<pair<NonTerminal*, string>> follow_ups;

                    for (int l = k + 1; l < current_production.size(); ++l) {
                        follow_ups.push_back({current_production[l].first, current_production[l].second});
                    }

                    pair<vector<pair<NonTerminal*, string>>, NonTerminal*> paired_follow_ups;
                    paired_follow_ups.first = follow_ups;
                    paired_follow_ups.second = non_terminals_classes[non_terminals[i]];
                    child.follow_helper.push_back(paired_follow_ups);
                }
            }
        }

    }
}



void ParserController::add_grammar_rule(string grammar_rule) {
    grammar_rules.push_back(grammar_rule);
}

void ParserController::add_non_terminal(string name) {
    non_terminals.push_back(name);
}

void ParserController::add_terminal(string terminal) {
    if(std::find(terminals.begin(), terminals.end(), terminal) != terminals.end()) {
        // DO NOTHING
    } else {
        terminals.push_back(terminal);
    }
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

    cout << "STEP(3): Productions" << endl;

    for (int i = 0; i < non_terminals.size(); ++i) {
        string non_terminal = non_terminals[i];
        NonTerminal* non_terminal_class = non_terminals_classes[non_terminal];

        cout << non_terminal_class->non_terminal << " = ";

        vector<vector<pair<NonTerminal*, string>>> productions = non_terminal_class->productions;

        for (int j = 0; j < productions.size(); ++j) {
            vector<pair<NonTerminal*, string>> single_production = productions[j];
            for (int k = 0; k < single_production.size(); ++k) {
                if(single_production[k].first->non_terminal != "") {
                    cout << single_production[k].first->non_terminal << " ";
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
    cout << endl;

}

void ParserController::print_follow_helper() {

    cout << "STEP(4): Follow Helper" << endl;

    for (int i = 0; i < non_terminals.size(); ++i) {
        print_current_follow_helper(non_terminals[i]);
    }
}

void ParserController::print_current_follow_helper(string name) {

    cout << "Non-Terminal: " << name << endl;

    vector<pair<vector<pair<NonTerminal*, string>>, NonTerminal*>> follow_helper =
            non_terminals_classes[name]->follow_helper;

    for (int l = 0; l < follow_helper.size(); ++l) {
        pair<vector<pair<NonTerminal*, string>>, NonTerminal*> current_production = follow_helper[l];

        vector<pair<NonTerminal*, string>> productions = current_production.first;
        cout << "Number#" << l+1 << "(size:" << productions.size() << ") ";
        for (int i = 0; i < productions.size(); ++i) {

            if(productions[i].first->non_terminal != "") {
                cout << productions[i].first->non_terminal << " ";
            } else if(productions[i].second != "") {
                cout << productions[i].second << " ";
            } else {
                cout << "\\L" << " ";
            }

        }

        cout << " (Parent:" << current_production.second->non_terminal << ")" << endl;
    }

    cout << endl;
}