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

#include "lexical_analyzer/file_services/GrammarReader.h"

#include "lexical_analyzer/automata/Helper.h"


using namespace std;

int main()
{
//     Lexical_controller l;
//     l.run_("test_simple.txt", "test_1_simple.txt");

    ParserController p;
    p.run_parser("test_cases/Example_2.txt");

    return 0;
}