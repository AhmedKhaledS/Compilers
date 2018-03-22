//
// Created by ahmed on 16/03/18.
//

#ifndef LEXICAL_ANALYZER_REDUCEDDFA_H
#define LEXICAL_ANALYZER_REDUCEDDFA_H

#include <vector>
#include <string>


class Minimize_DFA
{
    private:
    int marked_count;
    std::vector<std::vector<>> Graph ;
    std::vector<std::string> States;
    std::vector<std::string> Final_Unmarked_States;
    // here we will need a boolean Myhill_Nerode;
    void Myhill_Nerode_Iteration(int it);
    void set_up_matrix_bool();
    void merge_final_states();

    public:

    Minimize_DFA(/*vector of vectors*/);
    std::vector<std::vector> Minimum_DFA();
};

#endif //LEXICAL_ANALYZER_REDUCEDDFA_H
