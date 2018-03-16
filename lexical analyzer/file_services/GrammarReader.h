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
        std::string read_grammar_rules(std::string file_name) override;
        std::string read_source_file(std::string file_name) override;
};

#endif //LEXICAL_ANALYZER_GRAMMARREADER_H
