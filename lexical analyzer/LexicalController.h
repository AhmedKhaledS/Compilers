//
// Created by ahmed on 16/03/18.
//

#ifndef LEXICAL_ANALYZER_LEXICALCONTROLLER_H
#define LEXICAL_ANALYZER_LEXICALCONTROLLER_H

#include <string>
#include <vector>
#include <map>
#include "automata/State.h"
#include "automata/NFAGenerator.h"
#include "file_services/GrammarReader.h"
#include "file_services/SourceProgramReader.h"

class Lexical_controller
{
private:
    std::string grammar_rule_line;
    std::vector< State > nfa_graph;
    int token_count;
public:
    Lexical_controller();vector<string> cached_tokens;
    void run_(const std::string grammar_rule_file, const std::string src_program_file);
    string next_token();

};
#endif //LEXICAL_ANALYZER_LEXICALCONTROLLER_H
