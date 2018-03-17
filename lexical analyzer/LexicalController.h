//
// Created by ahmed on 16/03/18.
//

#ifndef LEXICAL_ANALYZER_LEXICALCONTROLLER_H
#define LEXICAL_ANALYZER_LEXICALCONTROLLER_H

#include <string>
#include <vector>
#include <map>

class Lexical_controller
{
    private:
        std::string grammar_rule_line;
        //std::vector< std::vector<NFA> > nfa_graph;
        //std::vector< std::vector<DFA> > dfa_graph;
        //std::vector< std::vector<DFA> > _minimzed_dfa_graph;

    public:
        void run(const std::string grammar_rule_file, const std::string src_program_file);

};
#endif //LEXICAL_ANALYZER_LEXICALCONTROLLER_H
