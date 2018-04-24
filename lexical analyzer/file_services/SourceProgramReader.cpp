//
// Created by ahmed on 16/03/18.
//

#include "SourceProgramReader.h"

using namespace std;

Source_program_reader::Source_program_reader()
{
    index = 0;
}

char Source_program_reader::get_next_char_from_src_program()
{
    if (file_stream.empty())
    {
        read(src_file_name);
        for (string curr : file_stream)
            src_program.append(curr + "\n");
    }

    // Check for bounds. // Don't forget about it in Controller.
    if (index > src_program.length())
        return '~';
    return src_program[index++];
}

void Source_program_reader::set_src_file_name(std::string fname)
{
    this->src_file_name = fname;
}

string Source_program_reader::read_next_grammar_rule_line(const string file_name, const int line_num)
{}