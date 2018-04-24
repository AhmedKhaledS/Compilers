//
// Created by ahmed on 16/03/18.
//

#ifndef LEXICAL_ANALYZER_GRAMMARREADER_H
#define LEXICAL_ANALYZER_GRAMMARREADER_H

#include "FileReader.h"
#include <string>

class Grammar_Reader: public File_Reader
{
    public:
        Grammar_Reader();
        std::string read_next_grammar_rule_line(const std::string file_name, const int line_num) override;
        char get_next_char_from_src_program() override;
};

#endif //LEXICAL_ANALYZER_GRAMMARREADER_H
