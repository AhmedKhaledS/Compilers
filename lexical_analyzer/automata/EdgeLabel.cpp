//
// Created by ahmed on 19/04/18.
//

#include "EdgeLabel.h"

using namespace std;

EdgeLabel::EdgeLabel(std::string input)
    : input(input)
{}
void EdgeLabel::discard_char(string c)
{
    this->discarded_chars.insert(c);
}
set<string> EdgeLabel::get_discarded_char()
{
    return this->discarded_chars;
}
string EdgeLabel::get_input()
{
    return input;
}