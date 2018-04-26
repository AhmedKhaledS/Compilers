#include <iostream>

#include <string>
#include <vector>
#include <fstream>
#include "lexical_analyzer/file_services/FileWriter.h"
#include "lexical_analyzer/file_services/GrammarReader.h"
#include "lexical_analyzer/file_services/SourceProgramReader.h"
#include "lexical_analyzer/LexicalController.h"
#include "lexical_analyzer/SymbolTable.h"
#include "lexical_analyzer/automata/DFATransformer.h"

#include "lexical_analyzer/automata/NFAOperations.h"
#include "lexical_analyzer/automata/NFA.h"
#include "lexical_analyzer/automata/NFAGenerator.h"

#include "parser/ParserController.h"
#include "parser/NonTerminal.h"
#include "parser/Utility.h"
#include "parser/ParserTable.h"


using namespace std;

int main()
{
//     Lexical_controller l;
//     l.run_("test_simple.txt", "test_1_simple.txt");

//     ParserController p;
//     p.run_parser();

    NonTerminal e,e2,t,t2,f;
    e.name = "e";
    e2.name = "e2";
    t.name = "t";
    t2.name = "t2";
    f.name = "f";

    e.first.insert("(");
    e.first.insert("x");
    e.first.insert("y");
    e2.first.insert("+");
    e2.first.insert("\\L");
    t.first.insert("(");
    t.first.insert("x");
    t.first.insert("y");
    t2.first.insert("*");
    t2.first.insert("\\L");
    f.first.insert("(");
    f.first.insert("x");
    f.first.insert("y");

    e.follow.insert("$");
    e.follow.insert(")");
    e2.follow.insert("$");
    e2.follow.insert(")");
    t.follow.insert("+");
    t.follow.insert("$");
    t.follow.insert(")");
    t2.follow.insert("+");
    t2.follow.insert("$");
    t2.follow.insert(")");
    f.follow.insert("*");
    f.follow.insert("+");
    f.follow.insert(")");
    f.follow.insert("$");

//    a.first.insert("id");
//    c.first.insert("(");
//    c.first.insert("\\L");
//    d.first.insert("num");
//

//    b.first.insert("id");

//    NonTerminal a, b, c, d;
//    a.non_terminal = "A";
//
//    c.non_terminal = "C";
//    d.non_terminal = "D";
////    a.first.insert("id");
////    c.first.insert("(");
////    c.first.insert("\\L");
////    d.first.insert("num");
////
//    b.non_terminal = "B";
////    b.first.insert("id");
////
////    vector<pair <NonTerminal, string> > tmp;
////    tmp.push_back({c, ""});
////    tmp.push_back({d, ""});
////
////    b.follow_helper.push_back({tmp, a});
////    Utility::compute_follow_terminals(&b, b.follow);
////
////    for (auto it = b.follow.begin(); it != b.follow.end(); ++it)
////        cout << *it << " ";
//    NonTerminal tt;
//    tt.non_terminal = "";
//
//    vector<pair<NonTerminal, string> > tmp2;
//    tmp2.push_back({tt, "id"});
//    b.productions.push_back(tmp2);
//
//    vector<pair<NonTerminal, string> > tmp3;
//    tmp3.push_back({tt, "num"});
//    c.productions.push_back(tmp3);

//
//    vector<pair<NonTerminal, string> > tmp4;
//    tmp4.push_back({tt, "("});
//    d.productions.push_back(tmp4);
//
//    vector<pair<NonTerminal, string> > tmp;
//    tmp.push_back({b, ""});
//    tmp.push_back({c, ""});
//    a.productions.push_back(tmp);
//    vector<pair<NonTerminal, string> > tmp1;
//    tmp1.push_back({d, ""});
//    a.productions.push_back(tmp1);
//
//    vector<pair<NonTerminal, string> > tmp0;
//    tmp0.push_back({tt, "\\L"});
//    a.productions.push_back(tmp0);
//
//    Utility::compute_first_terminals(&a, a.first);
//    for (auto it = a.first.begin(); it != a.first.end(); ++it)
//        cout << *it << " ";

    NonTerminal tt;
    tt.name = "";

    vector<pair<NonTerminal, string> > tmp2;
    tmp2.push_back({t,""});
    tmp2.push_back({e2,""});
    e.productions.push_back(tmp2);

    vector<pair<NonTerminal, string> > tmp2_1;
    tmp2_1.push_back({tt, "+"});
    tmp2_1.push_back({t,""});
    tmp2_1.push_back({e2,""});
    e2.productions.push_back(tmp2_1);
    tmp2_1.clear();
    tmp2_1.push_back({tt,"\\L"});
    e2.productions.push_back(tmp2_1);

    vector<pair<NonTerminal, string> > tmp3;
    tmp3.push_back({f, ""});
    tmp3.push_back({t2, ""});
    t.productions.push_back(tmp3);

    vector<pair<NonTerminal, string> > tmp4;
    tmp4.push_back({tt, "*"});
    tmp4.push_back({f, ""});
    tmp4.push_back({t2, ""});
    t2.productions.push_back(tmp4);
    tmp4.clear();
    tmp4.push_back({tt,"\\L"});
    t2.productions.push_back(tmp4);


    vector<pair<NonTerminal, string> > tmp;
    tmp.push_back({tt, "("});
    tmp.push_back({e,""});
    tmp.push_back({tt, ")"});
    f.productions.push_back(tmp);
    tmp.clear();
    tmp.push_back({tt,"X"});
    f.productions.push_back(tmp);
    tmp.clear();
    tmp.push_back({tt,"Y"});
    f.productions.push_back(tmp);







    vector<NonTerminal> grammar;
    grammar.push_back(e);
    grammar.push_back(e2);
    grammar.push_back(t);
    grammar.push_back(t2);
    grammar.push_back(f);

    ParserTable test_runner ;
    test_runner.build_parse_table(grammar);

    return 0;
}