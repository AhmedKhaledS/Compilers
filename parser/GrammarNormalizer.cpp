//
// Created by hisham on 26/04/18.
//

#include "GrammarNormalizer.h"
#include "../lexical analyzer/automata/Helper.h"

#include "iostream"

GrammarNormalizer::GrammarNormalizer(vector<string> grammar) {
    this->grammar = grammar;
}

void GrammarNormalizer::perform_left_recursion_elimination() {

    for (int i = 0; i < grammar.size(); ++i) {

        string current_grammar_rule = left_recursion_substitution(grammar[i]);

        cout << "Currently: " << current_grammar_rule << endl;

        left_recursion_elimination(current_grammar_rule);

    }
}

string GrammarNormalizer::left_recursion_substitution(string grammar_rule) {

    Helper helper;

    vector<string> equal_tokens = helper.tokenaize(grammar_rule, '=');
    vector<string> or_tokens = helper.tokenaize(equal_tokens[1], '|');

    string output_grammar_rule = "";
    output_grammar_rule += equal_tokens[0];
    output_grammar_rule += " = ";


    for (int i = 0; i < or_tokens.size(); ++i) {

        bool is_substituted = false;
        vector<string> tokens = helper.tokenaize(or_tokens[i], ' ');

        // Loop on previously added grammar...
        for (int j = 0; j < normalized_grammar.size() && !is_substituted; ++j) {

            vector<string> equal_tokens_temp = helper.tokenaize(normalized_grammar[j], '=');

            if(tokens[0] == equal_tokens_temp[0]) {

                is_substituted = true;
                // cout << "Substiutuion: ";
                vector<string> or_tokens_temp = helper.tokenaize(equal_tokens_temp[1], '|');
                for (int k = 0; k < or_tokens_temp.size(); ++k) {
                    output_grammar_rule += or_tokens_temp[k];
                    output_grammar_rule += " ";

                    int size = tokens[0].size();
                    output_grammar_rule += or_tokens[i].substr(size + 1, or_tokens[i].size() - size);

                    if(k != or_tokens_temp.size() - 1)
                        output_grammar_rule += " | ";
                }

                if(i != or_tokens.size() - 1)
                    output_grammar_rule += " | ";

                // cout << output_grammar_rule << endl;

            }

        }

        if (!is_substituted) {
            output_grammar_rule += or_tokens[i];
            if(i != or_tokens.size() - 1)
                output_grammar_rule += " | ";

            // cout << "No Substiutuion: " ;
            // cout << output_grammar_rule << endl;

        }

    }

    // normalized_grammar.push_back(grammar_rule);

    return output_grammar_rule;
}

void GrammarNormalizer::left_recursion_elimination(string grammar_rule) {

    Helper helper;

    vector<string> equal_tokens = helper.tokenaize(grammar_rule, '=');
    vector<string> or_tokens = helper.tokenaize(equal_tokens[1], '|');

    string current_non_terminal = equal_tokens[0];
    vector<string> alpha, beta;
    for (int j = 0; j < or_tokens.size(); ++j) {
        vector<string> tokens = helper.tokenaize(or_tokens[j], ' ');
        if(tokens[0] == current_non_terminal) {
            int size = tokens[0].size();
            alpha.push_back(or_tokens[j].substr(size + 1, or_tokens[j].size() - size));
        } else {
            beta.push_back(or_tokens[j]);
        }
    }

    if(alpha.size() != 0) {
        string first_rule = "", second_rule = "";
        string temp_non_terminal = current_non_terminal + "\'";

        first_rule += current_non_terminal;
        first_rule += " = ";
        for (int j = 0; j < beta.size(); ++j) {
            first_rule += beta[j];
            first_rule += " ";
            first_rule += temp_non_terminal;
            if(j != beta.size() - 1)
                first_rule += " | ";
        }

        second_rule += temp_non_terminal;
        second_rule += " = ";
        for (int j = 0; j < alpha.size(); ++j) {
            second_rule += alpha[j];
            second_rule += " ";
            second_rule += temp_non_terminal;
            second_rule += " | ";
        }

        second_rule += "\\L";

        normalized_grammar.push_back(first_rule);
        normalized_grammar.push_back(second_rule);

    } else {

        normalized_grammar.push_back(grammar_rule);
    }
}

void GrammarNormalizer::print_grammar(vector<string> grammar) {
    for (int i = 0; i < grammar.size(); ++i) {
        cout << grammar[i] << endl;
    }
}





