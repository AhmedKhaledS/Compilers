//
// Created by ahmed on 16/03/18.
//

#ifndef LEXICAL_ANALYZER_FILE_HANDLER_H
#define LEXICAL_ANALYZER_FILE_HANDLER_H

#include <string>
#include <vector>

class File_Handler
{
    public:
        virtual std::vector<std::string> read(std::string file_name) = 0;
        virtual void write(std::string file_name, std::vector<std::string> data_stream) = 0;
};
#endif //LEXICAL_ANALYZER_FILE_HANDLER_H
