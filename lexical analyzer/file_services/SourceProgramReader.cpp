//
// Created by ahmed on 16/03/18.
//

#include "SourceProgramReader.h"

using namespace std;

Source_program_reader::Source_program_reader()
{
    index = 0;
}

char Source_program_reader::get_next_char_from_src_program(const std::string file_name)
{
    if (file_stream.empty())
    {
        read(file_name);
        for (string curr : file_stream)
            src_program.append(curr + "\n");
    }

    // Check for bounds. // Don't forget about it in Controller.
    if (index > src_program.length())
        return EOF;
    return src_program[index++];
}

string Source_program_reader::read_next_grammar_rule_line(const string file_name, const int line_num)
{}