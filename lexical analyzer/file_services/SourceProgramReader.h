//
// Created by ahmed on 16/03/18.
//

#ifndef LEXICAL_ANALYZER_SOURCEPROGRAMREADER_H
#define LEXICAL_ANALYZER_SOURCEPROGRAMREADER_H

#include "FileReader.h"
#include <string>

class Source_program_reader: public File_Reader
{
    public:
        std::string read_grammar_rules(std::string file_name);
        std::string read_source_file(std::string file_name);
};
#endif //LEXICAL_ANALYZER_SOURCEPROGRAMREADER_H
