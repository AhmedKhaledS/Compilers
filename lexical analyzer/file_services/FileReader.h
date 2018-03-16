//
// Created by ahmed on 16/03/18.
//

#ifndef LEXICAL_ANALYZER_FILE_READER_H
#define LEXICAL_ANALYZER_FILE_READER_H

#include "FileHandler.h"
#include <string>
#include <vector>

class File_Reader: public File_Handler
{
    protected:
        std::vector<std::string> file_stream;
    public:
        File_Reader();
        std::vector<std::string> read(std::string file_name) override;
        void write(std::string file_name, std::vector<std::string> data_stream) override;
        virtual std::string read_grammar_rules(std::string file_name) = 0;
        virtual std::string read_source_file(std::string file_name) = 0;
};
#endif //LEXICAL_ANALYZER_FILE_READER_H
