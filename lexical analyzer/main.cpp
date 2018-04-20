#include <iostream>

#include <string>
#include <vector>
#include "file_services/FileWriter.h"
#include "file_services/GrammarReader.h"
#include "file_services/SourceProgramReader.h"
#include "LexicalController.h"
#include "SymbolTable.h"
#include "automata/DFATransformer.h"
#include <fstream>

#include "automata/NFAOperations.h"
#include "automata/NFA.h"
#include "automata/NFAGenerator.h"


using namespace std;

int main()
{
    Lexical_controller l;
    l.run_("test.txt", "test_1.txt");
    return 0;
}