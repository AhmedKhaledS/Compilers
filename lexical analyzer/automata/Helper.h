//
// Created by hisham on 23/03/18.
//

#ifndef COMPILERS_HELPER_H
#define COMPILERS_HELPER_H

#include <string>
#include <vector>

using namespace std;


class Helper {

    public:
        string hide_classes(string s);
        string expand_classes(char start, char end);
        vector<string> get_classes(const string s);
        string normalize_classes(string expression);

        string insert_concatination(string expression);

        vector<string> tokenaize(string s, char delim);

        string remove_escape_char(string s);

        string trim(const string& str);

        bool is_all_or(string expression);

        bool is_operation(char c);

};



#endif //COMPILERS_HELPER_H
