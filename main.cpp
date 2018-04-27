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

     ParserController p;
     p.run_parser();

//    NonTerminal e,e2,t,t2,f;
//    e.non_terminal = "e";
//    e2.non_terminal = "e2";
//    t.non_terminal = "t";
//    t2.non_terminal = "t2";
//    f.non_terminal = "f";
//
//    e.first.insert("(");
//    e.first.insert("x");
//    e.first.insert("y");
//    e2.first.insert("+");
//    e2.first.insert("\\L");
//    t.first.insert("(");
//    t.first.insert("x");
//    t.first.insert("y");
//    t2.first.insert("*");
//    t2.first.insert("\\L");
//    f.first.insert("(");
//    f.first.insert("x");
//    f.first.insert("y");
//
//    e.follow.insert("$");
//    e.follow.insert(")");
//    e2.follow.insert("$");
//    e2.follow.insert(")");
//    t.follow.insert("+");
//    t.follow.insert("$");
//    t.follow.insert(")");
//    t2.follow.insert("+");
//    t2.follow.insert("$");
//    t2.follow.insert(")");
//    f.follow.insert("*");
//    f.follow.insert("+");
//    f.follow.insert(")");
//    f.follow.insert("$");
//    NonTerminal tt;
//    tt.non_terminal = "";
//
//    vector<pair<NonTerminal, string> > tmp2;
//    tmp2.push_back({t,""});
//    tmp2.push_back({e2,""});
//    e.productions.push_back(tmp2);
//
//    vector<pair<NonTerminal, string> > tmp2_1;
//    tmp2_1.push_back({tt, "+"});
//    tmp2_1.push_back({t,""});
//    tmp2_1.push_back({e2,""});
//    e2.productions.push_back(tmp2_1);
//    tmp2_1.clear();
//    tmp2_1.push_back({tt,"\\L"});
//    e2.productions.push_back(tmp2_1);
//
//    vector<pair<NonTerminal, string> > tmp3;
//    tmp3.push_back({f, ""});
//    tmp3.push_back({t2, ""});
//    t.productions.push_back(tmp3);
//
//    vector<pair<NonTerminal, string> > tmp4;
//    tmp4.push_back({tt, "*"});
//    tmp4.push_back({f, ""});
//    tmp4.push_back({t2, ""});
//    t2.productions.push_back(tmp4);
//    tmp4.clear();
//    tmp4.push_back({tt,"\\L"});
//    t2.productions.push_back(tmp4);
//
//
//    vector<pair<NonTerminal, string> > tmp;
//    tmp.push_back({tt, "("});
//    tmp.push_back({e,""});
//    tmp.push_back({tt, ")"});
//    f.productions.push_back(tmp);
//    tmp.clear();
//    tmp.push_back({tt,"X"});
//    f.productions.push_back(tmp);
//    tmp.clear();
//    tmp.push_back({tt,"Y"});
//    f.productions.push_back(tmp);
//





//
//    vector<NonTerminal> grammar;
//    grammar.push_back(e);
//    grammar.push_back(e2);
//    grammar.push_back(t);
//    grammar.push_back(t2);
//    grammar.push_back(f);
//
//    ParserTable test_runner ;
//    test_runner.build_parse_table(grammar);

    return 0;
}