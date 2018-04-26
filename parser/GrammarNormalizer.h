//
// Created by hisham on 26/04/18.
//

#ifndef COMPILERS_GRAMMARNORMALIZER_H
#define COMPILERS_GRAMMARNORMALIZER_H

#include <string>
#include <vector>


using namespace std;

class GrammarNormalizer {

public:

    GrammarNormalizer(vector<string> grammar);

    void perform_grammar_normalization();

    void perform_left_recursion_elimination();
    void left_recursion_elimination(string grammar);
    string left_recursion_substitution(string grammar);

    void perform_left_factoring();
    string left_factoring_substitution(int start, int end, string prefix,
                                     vector<string> or_tokens, string output_grammar);
    string common_prefix_util(string str1, string str2);

    void print_grammar(vector<string> grammar);


    vector<string> grammar;
    vector<string> non_recursive_grammar;
    vector<string> normalized_grammar;

};


#endif //COMPILERS_GRAMMARNORMALIZER_H