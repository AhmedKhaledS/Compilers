//
// Created by ahmed on 16/03/18.
//

#ifndef LEXICAL_ANALYZER_REDUCEDDFA_H
#define LEXICAL_ANALYZER_REDUCEDDFA_H

#include <vector>

class Minimize_DFA
{
    private:
    std::vector<> Minimized_Graph;
    std::vector<> Grouped_Edges;
    std::vector<> Grouped_Nodes;
    void group_Nodes_Union(/*takes number of nodes*/);
    void sift_Through_Graph();
    bool examine_And_Split_Class(/*takes a class*/);

    public:

    Minimize_DFA(/*vector of vectors*/);
    void build_min_DFA();
    std::vector<std::vector> Minimum_DFA();






};

#endif //LEXICAL_ANALYZER_REDUCEDDFA_H
