//
// Created by hisham on 26/04/18.
//

#include <algorithm>
#include "GrammarNormalizer.h"
#include "../lexical_analyzer/automata/Helper.h"

#include "iostream"

GrammarNormalizer::GrammarNormalizer(vector<string> grammar) {
    this->grammar = grammar;
    this->normalization_characher = '1';
}



void GrammarNormalizer::perform_grammar_normalization() {

    perform_left_recursion_elimination();

    cout << "STEP (1): Eliminating Left Recursion" << endl;
    print_grammar(non_recursive_grammar);

    perform_left_factoring();

}



void GrammarNormalizer::perform_left_recursion_elimination() {

    for (int i = 0; i < grammar.size(); ++i) {

        string current_grammar_rule = left_recursion_substitution(grammar[i]);

        left_recursion_elimination(current_grammar_rule);

    }
}

string GrammarNormalizer::left_recursion_substitution(string grammar_rule) {

    Helper helper;

    vector<string> equal_tokens = helper.tokenaize_first(grammar_rule, '=');
    vector<string> or_tokens = helper.tokenaize(equal_tokens[1], '|');

    string output_grammar_rule = "";
    output_grammar_rule += equal_tokens[0];
    output_grammar_rule += " = ";


    for (int i = 0; i < or_tokens.size(); ++i) {

        bool is_substituted = false;
        vector<string> tokens = helper.tokenaize(or_tokens[i], ' ');

        // Loop on previously added grammar...
        for (int j = 0; j < non_recursive_grammar.size() && !is_substituted; ++j) {

            vector<string> equal_tokens_temp = helper.tokenaize_first(non_recursive_grammar[j], '=');

            if(tokens[0] == equal_tokens_temp[0]) {

                is_substituted = true;
                // cout << "Substiutuion: ";
                vector<string> or_tokens_temp = helper.tokenaize(equal_tokens_temp[1], '|');
                for (int k = 0; k < or_tokens_temp.size(); ++k) {
                    output_grammar_rule += or_tokens_temp[k];

                    int size = tokens[0].size();
                    if( or_tokens[i].size() - size == 0) {
                        continue;
                    }
                    output_grammar_rule += " ";
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

    vector<string> equal_tokens = helper.tokenaize_first(grammar_rule, '=');
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

        non_recursive_grammar.push_back(first_rule);
        non_recursive_grammar.push_back(second_rule);

    } else {

        non_recursive_grammar.push_back(grammar_rule);
    }
}



void GrammarNormalizer::perform_left_factoring() {

    Helper helper;

    for (int i = 0; i < non_recursive_grammar.size(); ++i) {

        string current_rule = non_recursive_grammar[i];

        vector<string> equal_tokens = helper.tokenaize_first(current_rule, '=');
        vector<string> or_tokens = helper.tokenaize(equal_tokens[1], '|');
        std::sort(or_tokens.begin(), or_tokens.end());

        bool visited_token[or_tokens.size()] = {false};
        int uncovered_tokens = or_tokens.size();

        string output_grammar_rule = "";
        output_grammar_rule += equal_tokens[0];
        output_grammar_rule += " = ";

        for (int j = 0; j < or_tokens.size() - 1; ++j) {
            string temp_prefix = common_prefix_util(or_tokens[j], or_tokens[j + 1]);
            if(temp_prefix.size() != 0) {
                int start_index = j, end_index = j+1;
                j++;
                j++;
                while(j < or_tokens.size() &&
                        common_prefix_util(temp_prefix,or_tokens[j]).size() > 0) {
                    temp_prefix = common_prefix_util(temp_prefix,or_tokens[j]);
                    end_index = j;
                    j++;
                }

                for (int k = start_index; k <= end_index; ++k) {
                    visited_token[k] = true;
                    uncovered_tokens--;
                }

                output_grammar_rule = left_factoring_substitution(start_index,end_index,temp_prefix,
                                                                  or_tokens, output_grammar_rule);

                if(j != or_tokens.size()) {
                    j--;
                }

                if(uncovered_tokens != 0) {
                    output_grammar_rule += " | ";
                }

            }
        }

        for (int l = 0; l < or_tokens.size(); ++l) {
            if(visited_token[l] == false) {
                output_grammar_rule += or_tokens[l];
                uncovered_tokens--;
                if(uncovered_tokens != 0) {
                    output_grammar_rule += " | ";
                }
            }
        }

        normalized_grammar.push_back(output_grammar_rule);
    }
}

string GrammarNormalizer::left_factoring_substitution(int start, int end, string prefix,
                                                    vector<string> or_tokens, string output_grammar) {
    string new_symbol = "X";
    new_symbol += normalization_characher++;
    string new_rule = new_symbol;
    new_rule += " = ";

    output_grammar += prefix;
    output_grammar += " ";
    output_grammar += new_symbol;

    for (int i = start; i < end + 1; ++i) {
        string current_production = or_tokens[i];
        if(or_tokens[i].substr(prefix.size(), or_tokens[i].size() - prefix.size()).size() == 0) {
            continue;
        }
        new_rule += or_tokens[i].substr(prefix.size(), or_tokens[i].size() - prefix.size());
        if(i != end)
            new_rule += " | ";
    }

    normalized_grammar.push_back(new_rule);

    return output_grammar;
}

string GrammarNormalizer::common_prefix_util(string str1, string str2) {
    string result;
    int n1 = str1.length(), n2 = str2.length();

    // Compare str1 and str2
    for (int i=0, j=0; i<=n1-1&&j<=n2-1; i++,j++)
    {
        if (str1[i] != str2[j])
            break;
        result.push_back(str1[i]);
    }

    while (std::count(result.begin(), result.end(), '\'') % 2 != 0) {
        result = result.substr(0,result.size() - 1);
    }

    if(result[result.size() - 1] == ' ') {
        result = result.substr(0,result.size() - 1);
    }

    return (result);
}



void GrammarNormalizer::print_grammar(vector<string> grammar) {
    for (int i = 0; i < grammar.size(); ++i) {
        cout << grammar[i] << endl;
    }
    cout << endl;
}