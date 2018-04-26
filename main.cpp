#include <iostream>

#include <string>
#include <vector>
#include <fstream>
#include "lexical analyzer/file_services/FileWriter.h"
#include "lexical analyzer/file_services/GrammarReader.h"
#include "lexical analyzer/file_services/SourceProgramReader.h"
#include "lexical analyzer/LexicalController.h"
#include "lexical analyzer/SymbolTable.h"
#include "lexical analyzer/automata/DFATransformer.h"

#include "lexical analyzer/automata/NFAOperations.h"
#include "lexical analyzer/automata/NFA.h"
#include "lexical analyzer/automata/NFAGenerator.h"

#include "parser/ParserController.h"
#include "parser/NonTerminal.h"
#include "parser/Utility.h"


using namespace std;

int main()
{
//     Lexical_controller l;
//     l.run_("test_simple.txt", "test_1_simple.txt");

     ParserController p;
     p.run_parser();

    NonTerminal a, b, c, d;
    a.name = "A";

    c.name = "C";
    d.name = "D";
//    a.first.insert("id");
//    c.first.insert("(");
//    c.first.insert("\\L");
//    d.first.insert("num");
//
    b.name = "B";
//    b.first.insert("id");
//
//    vector<pair <NonTerminal, string> > tmp;
//    tmp.push_back({c, ""});
//    tmp.push_back({d, ""});
//
//    b.follow_helper.push_back({tmp, a});
//    Utility::compute_follow_terminals(&b, b.follow);
//
//    for (auto it = b.follow.begin(); it != b.follow.end(); ++it)
//        cout << *it << " ";
    NonTerminal tt;
    tt.name = "";

    vector<pair<NonTerminal, string> > tmp2;
    tmp2.push_back({tt, "id"});
    b.productions.push_back(tmp2);

    vector<pair<NonTerminal, string> > tmp3;
    tmp3.push_back({tt, "num"});
    c.productions.push_back(tmp3);

    vector<pair<NonTerminal, string> > tmp4;
    tmp4.push_back({tt, "("});
    d.productions.push_back(tmp4);

    vector<pair<NonTerminal, string> > tmp;
    tmp.push_back({b, ""});
    tmp.push_back({c, ""});
    a.productions.push_back(tmp);
    vector<pair<NonTerminal, string> > tmp1;
    tmp1.push_back({d, ""});
    a.productions.push_back(tmp1);

    vector<pair<NonTerminal, string> > tmp0;
    tmp0.push_back({tt, "\\L"});
    a.productions.push_back(tmp0);

    Utility::compute_first_terminals(&a, a.first);
    for (auto it = a.first.begin(); it != a.first.end(); ++it)
        cout << *it << " ";
    return 0;
}