//
// Created by ahmed on 16/03/18.
//

#ifndef LEXICAL_ANALYZER_SOURCEPROGRAMREADER_H
#define LEXICAL_ANALYZER_SOURCEPROGRAMREADER_H

#include "FileReader.h"
#include <string>

class Source_program_reader: public File_Reader
{
    private:
        int index;
        std::string src_program;
    public:
        Source_program_reader();
        std::string read_next_grammar_rule_line(std::string file_name, int line_num);
        char get_next_char_from_src_program(std::string file_name);
};
#endif //LEXICAL_ANALYZER_SOURCEPROGRAMREADER_H
