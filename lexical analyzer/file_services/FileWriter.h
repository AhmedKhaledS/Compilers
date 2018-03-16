//
// Created by ahmed on 16/03/18.
//

#ifndef LEXICAL_ANALYZER_FILE_WRITER_H
#define LEXICAL_ANALYZER_FILE_WRITER_H

#include "FileHandler.h"
#include <string>

class File_Writer: public File_Handler
{
    public:
        File_Writer();
        std::vector<std::string> read(std::string file_name) override;
        void write(std::string file_name, std::vector<std::string> data_stream) override;
};
#endif //LEXICAL_ANALYZER_FILE_WRITER_H
