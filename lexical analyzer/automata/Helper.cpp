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