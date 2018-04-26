//
// Created by ahmed on 19/04/18.
//

#ifndef LEXICAL_ANALYZER_EDGELABEL_H
#define LEXICAL_ANALYZER_EDGELABEL_H
#include <string>
#include <set>

class EdgeLabel {

    private:
        std::string input;
        std::set<std::string> discarded_chars;
    public:
        EdgeLabel(std::string input);
        void discard_char(std::string c);
        std::string get_input();
        std::set<std::string> get_discarded_char();

};


#endif //LEXICAL_ANALYZER_EDGELABEL_H
