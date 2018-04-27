//
// Created by hisham on 23/03/18.
//

#include "Helper.h"

#include <regex>

string Helper::hide_classes(string s) {

    regex reg("(.)( )*-( )*(.)");
    s = regex_replace(s, reg, "$");

    return s;
}

string Helper::expand_classes(char start, char end) {
    string result = "";
    result += start;
    for (char i = start + 1; i <= end; i++) {
        result += '|';
        result += i;
    }
    return result;
}

vector<string> Helper::get_classes(const string s) {

    vector<string> classes;

    string s_1(s);

    std::smatch m;
    std::regex e ("(.)( )*-( )*(.)");   // matches words beginning by "sub"

    while (std::regex_search (s_1,m,e)) {
        classes.push_back(m[0]);
        s_1 = m.suffix().str();
    }

    return classes;
}

string Helper::normalize_classes(string expression) {
    vector<string> classes = get_classes(expression);
    string hidden_classes = hide_classes(expression);
    string output = "";

    int count = 0;
    for (int i = 0; i < hidden_classes.size(); i++) {
        if(hidden_classes[i] == '$') {
            output += expand_classes(classes[count][0], classes[count][classes[count].size() - 1]);
            count++;
        } else {
            output += hidden_classes[i];
        }
    }

    return output;
}

string Helper::insert_concatination(string expression) {

    string result = "";

    if(expression.length() == 1) {
        return expression;
    }

    result += expression[0];

    for (int i = 1; i < expression.length(); ++i) {
        result += "@";
        result += expression[i];
    }

    return result;
}

vector<string> Helper::tokenaize(string s, char delim) {

    std::stringstream test(s);
    std::string segment;
    std::vector<std::string> tokens;

    while(std::getline(test, segment, delim))
    {
        tokens.push_back(trim(segment));
    }

    return tokens;
}

vector<string> Helper::tokenaize_first(string s, char delim) {

    std::stringstream test(s);
    std::string segment;
    std::vector<std::string> tokens;
    int size = 0;

    while(std::getline(test, segment, delim))
    {
        size = segment.size();
        tokens.push_back(trim(segment));
        break;
    }

    s = s.substr(size + 1, s.size() - size + 1);

    tokens.push_back(trim(s));

    return tokens;
}



string Helper::remove_escape_char(string s) {
    string result = "";
    for (int i = 0; i < s.length(); i++) {
        if(s[i] == '\\')
            continue;

        result += s[i];
    }
    return result;
}

string Helper::trim(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

bool Helper::is_all_or(string expression) {
    for (int i = 0; i < expression.length(); ++i) {
        if(is_operation(expression[i]))
            return false;
    }
    return true;
}

bool Helper::is_operation(char c) {

    return c == '(' || c == ')' || c == '@' || c == '*' || c == '+';

}