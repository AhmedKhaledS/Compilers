//
// Created by hisham on 26/04/18.
//

#include "GrammarNormalizer.h"
#include "../lexical analyzer/automata/Helper.h"

#include "iostream"

GrammarNormalizer::GrammarNormalizer(vector<string> grammar) {
    this->grammar = grammar;
}

void GrammarNormalizer::left_recursion_elimination() {

    Helper helper;

    for (int i = 0; i < grammar.size(); ++i) {

        string current_grammar_rule = grammar[i];

        vector<string> equal_tokens = helper.tokenaize(grammar[i], '=');
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

            cout << first_rule << endl;
            cout << second_rule << endl;

        } else {
            cout << current_grammar_rule << endl;
        }

    }
}

void GrammarNormalizer::print_grammar() {
    for (int i = 0; i < grammar.size(); ++i) {
        cout << grammar[i] << endl;
    }
}


