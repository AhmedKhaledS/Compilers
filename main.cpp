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


using namespace std;

int main()
{
//     Lexical_controller l;
//     l.run_("test_simple.txt", "test_1_simple.txt");

     ParserController p;
     p.run_parser();
     NonTerminal *a = new NonTerminal();
    NonTerminal *b = new NonTerminal();
    NonTerminal *c = new NonTerminal();
    NonTerminal *d = new NonTerminal();
    NonTerminal *e = new NonTerminal();
    a->non_terminal = "A";
    a->starting_state = true;
    b->non_terminal = "B";
    c->non_terminal = "C";
    d->non_terminal = "D";
    e->non_terminal = "E";
    //    a.first.insert("id");
//    c.first.insert("(");
//    c.first.insert("\\L");
//    d.first.insert("num");
//
//    b.first.insert("id");
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
    tt.non_terminal = "";

    vector<pair<NonTerminal, string> > tmp2;
    tmp2.push_back({tt, "not"});
    tmp2.push_back({*e, ""});
    e->productions.push_back(tmp2);
    tmp2.clear();
    tmp2.push_back({tt, "("});
    tmp2.push_back({*a, ""});
    tmp2.push_back({tt, ")"});
    e->productions.push_back(tmp2);
    tmp2.clear();
    tmp2.push_back({tt, "true"});
    e->productions.push_back(tmp2);
    tmp2.clear();
    tmp2.push_back({tt, "false"});
    e->productions.push_back(tmp2);
    // E is done


    vector<pair<NonTerminal, string> > tmp3;
    tmp3.push_back({tt, "and"});
    tmp3.push_back({*e, ""});
    tmp3.push_back({*d, ""});
    d->productions.push_back(tmp3);
    tmp3.clear();
    tmp3.push_back({tt, "\\L"});
    d->productions.push_back(tmp3);
    // D is done



    vector<pair<NonTerminal, string> > tmp4;
    tmp4.push_back({*e, ""});
    tmp4.push_back({*d, ""});
    c->productions.push_back(tmp4);
    // C is done here.

    vector<pair<NonTerminal, string> > tmp;
    tmp.push_back({tt, "or"});
    tmp.push_back({*c, ""});
    tmp.push_back({*b, ""});
    b->productions.push_back(tmp);
    tmp.clear();
    tmp.push_back({tt, "\\L"});
    b->productions.push_back(tmp);


    vector<pair<NonTerminal, string> > tmp1;
    tmp1.push_back({*c, ""});
    tmp1.push_back({*b, ""});
    a->productions.push_back(tmp1);

    Utility::compute_first_terminals(a, a->first);
    Utility::compute_first_terminals(b, b->first);
    Utility::compute_first_terminals(c, c->first);
    Utility::compute_first_terminals(d, d->first);
    Utility::compute_first_terminals(e, e->first);


    // Constructing follow-helper.
    vector<pair <NonTerminal, string> > tmpp;
//    tmpp.push_back({tt, ""});
    a->follow_helper.push_back({tmpp, tt});
    tmpp.clear();
//    tmpp.push_back({tt, ""});
    a->follow_helper.push_back({tmpp, tt});
    tmpp.clear();
//    tmpp.push_back({tt, ""});
    a->follow_helper.push_back({tmpp, tt});
    tmpp.clear();
//    tmpp.push_back({tt, ""});
    a->follow_helper.push_back({tmpp, tt});
    tmpp.clear();
    tmpp.push_back({tt, ")"});
    a->follow_helper.push_back({tmpp, *e});
    // Follow-helper for A is done.

    tmpp.clear();
    //tmpp.push_back({tt, ""});
    b->follow_helper.push_back({tmpp, *a});

    tmpp.clear();
//    tmpp.push_back({tt, ""});
    b->follow_helper.push_back({tmpp, *b});

    tmpp.clear();
//    tmpp.push_back({tt, ""});
    b->follow_helper.push_back({tmpp, tt});

    tmpp.clear();
//    tmpp.push_back({tt, ""});
    b->follow_helper.push_back({tmpp, tt});

    tmpp.clear();
//    tmpp.push_back({tt, ""});
    b->follow_helper.push_back({tmpp, tt});
    // B is done.


    tmpp.clear();
    tmpp.push_back({*b, ""});
    c->follow_helper.push_back({tmpp, *a});

    tmpp.clear();
    tmpp.push_back({*b, ""});
    c->follow_helper.push_back({tmpp, *b});

    tmpp.clear();
//    tmpp.push_back({tt, ""});
    c->follow_helper.push_back({tmpp, tt});

    tmpp.clear();
//    tmpp.push_back({tt, ""});
    c->follow_helper.push_back({tmpp, tt});

    tmpp.clear();
//    tmpp.push_back({tt, ""});
    c->follow_helper.push_back({tmpp, tt});
    // C is done.


    tmpp.clear();
//    tmpp.push_back({tt, ""});
    d->follow_helper.push_back({tmpp, tt});

    tmpp.clear();
//    tmpp.push_back({tt, ""});
    d->follow_helper.push_back({tmpp, tt});

    tmpp.clear();
//    tmpp.push_back({tt, ""});
    d->follow_helper.push_back({tmpp, *c});

    tmpp.clear();
//    tmpp.push_back({tt, ""});
    d->follow_helper.push_back({tmpp, *d});

    tmpp.clear();
//    tmpp.push_back({tt, ""});
    d->follow_helper.push_back({tmpp, tt});
    // D is done.


    tmpp.clear();
//    tmpp.push_back({tt, ""});
    e->follow_helper.push_back({tmpp, tt});

    tmpp.clear();
//    tmpp.push_back({tt, ""});
    e->follow_helper.push_back({tmpp, tt});

    tmpp.clear();
    tmpp.push_back({*d, ""});
    e->follow_helper.push_back({tmpp, *c});

    tmpp.clear();
    tmpp.push_back({*d, ""});
    e->follow_helper.push_back({tmpp, *d});

    tmpp.clear();
//    tmpp.push_back({tt, ""});
    e->follow_helper.push_back({tmpp, *e});
    // E is done.



    Utility::compute_follow_terminals(a, a->follow);
    Utility::compute_follow_terminals(b, b->follow);
    Utility::compute_follow_terminals(c, c->follow);
    Utility::compute_follow_terminals(d, d->follow);
    Utility::compute_follow_terminals(e, e->follow);

    cout << "First of A: ";
    for (auto it = a->first.begin(); it != a->first.end(); ++it)
        cout << *it << " ";
    cout << "\nFirst of B: ";
    for (auto it = b->first.begin(); it != b->first.end(); ++it)
        cout << *it << " ";
    cout << "\nFirst of C: ";
    for (auto it = c->first.begin(); it != c->first.end(); ++it)
        cout << *it << " ";
    cout << "\nFirst of D: ";
    for (auto it = d->first.begin(); it != d->first.end(); ++it)
        cout << *it << " ";
    cout << "\nFirst of E: ";
    for (auto it = e->first.begin(); it != e->first.end(); ++it)
        cout << *it << " ";


    cout << "\nFollow of A: ";
    for (auto it = a->follow.begin(); it != a->follow.end(); ++it)
        cout << *it << " ";
    cout << "\nFollow of B: ";
    for (auto it = b->follow.begin(); it != b->follow.end(); ++it)
        cout << *it << " ";
    cout << "\nFollow of C: ";
    for (auto it = c->follow.begin(); it != c->follow.end(); ++it)
        cout << *it << " ";
    cout << "\nFollow of D: ";
    for (auto it = d->follow.begin(); it != d->follow.end(); ++it)
        cout << *it << " ";
    cout << "\nFollow of E: ";
    for (auto it = e->follow.begin(); it != e->follow.end(); ++it)
        cout << *it << " ";
    return 0;
}