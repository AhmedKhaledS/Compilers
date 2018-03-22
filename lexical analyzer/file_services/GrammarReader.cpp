//
// Created by ahmed on 16/03/18.
//

#include "GrammarReader.h"

using namespace std;

Grammar_Reader::Grammar_Reader()
{}

string Grammar_Reader::read_next_grammar_rule_line(const string file_name, const int line_num)
{
    if (file_stream.empty())
        read(file_name);

    if (line_num > file_stream.size() || line_num <= 0)
        return NULL;

    // Line number is 1-based.
    return file_stream[line_num - 1];
}
char Grammar_Reader::get_next_char_from_src_program(const std::string file_name)
{}
