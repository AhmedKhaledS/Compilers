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

        void perform_left_recursion_elimination();
        string left_recursion_substitution(string grammar);
        void left_recursion_elimination(string grammar);

        void print_grammar(vector<string> grammar);


        vector<string> grammar;
        vector<string> normalized_grammar;



};


#endif //COMPILERS_GRAMMARNORMALIZER_H
