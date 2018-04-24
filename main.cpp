#include <iostream>

#include <string>
#include <vector>
#include "lexical analyzer/file_services/FileWriter.h"
#include "lexical analyzer/file_services/GrammarReader.h"
#include "lexical analyzer/file_services/SourceProgramReader.h"
#include "lexical analyzer/LexicalController.h"
#include "lexical analyzer/SymbolTable.h"
#include "lexical analyzer/automata/DFATransformer.h"
#include <fstream>

#include "lexical analyzer/automata/NFAOperations.h"
#include "lexical analyzer/automata/NFA.h"
#include "lexical analyzer/automata/NFAGenerator.h"

#include "parser/ParserController.h"


using namespace std;

int main()
{
    // Lexical_controller l;
    // l.run_("test_simple.txt", "test_1_simple.txt");

    ParserController p;
    p.run_parser();



    return 0;
}