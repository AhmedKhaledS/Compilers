//
// Created by ahmed on 16/03/18.
//

#ifndef LEXICAL_ANALYZER_DFATRANSFORMER_H
#define LEXICAL_ANALYZER_DFATRANSFORMER_H

#include <vector>

class NFA_DFA_Parser
{

    private:
    std::vector<> New_Graph;
    std::vector<> Grouped_Edges;
    std::vector<> Grouped_Nodes;
    void group_Nodes_Crawl(/*takes one node*/);
    void traverse_And_Group_eps_connected_states();

    public:

    NFA_DFA_Parser(/*vector*/);
    void build_DFA();
    std::vector<std::vector> transform_To_DFA();

};
#endif //LEXICAL_ANALYZER_DFATRANSFORMER_H
