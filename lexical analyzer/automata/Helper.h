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
};



#endif //COMPILERS_HELPER_H
