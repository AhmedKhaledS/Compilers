//
// Created by ahmed on 16/03/18.
//

#ifndef LEXICAL_ANALYZER_SYMBOLTABLE_H
#define LEXICAL_ANALYZER_SYMBOLTABLE_H

#include <map>
#include <string>

class Symbol_table
{
    private:
        static std::map<std::string, std::string> symbol_table;
    public:
        static void add_identifier(std::string label, std::string value);
        static bool search_identifier(std::string label);
};

#endif //LEXICAL_ANALYZER_SYMBOLTABLE_H
