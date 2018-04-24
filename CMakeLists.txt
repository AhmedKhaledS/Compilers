cmake_minimum_required(VERSION 3.8)

project(Compilers)

set(CMAKE_CXX_STANDARD 11)

add_executable(Compilers
        "lexical analyzer/automata/DFANode.cpp"
        "lexical analyzer/automata/DFANode.h"
        "lexical analyzer/automata/DFATransformer.cpp"
        "lexical analyzer/automata/DFATransformer.h"
        "lexical analyzer/automata/EdgeLabel.cpp"
        "lexical analyzer/automata/EdgeLabel.h"
        "lexical analyzer/automata/Helper.cpp"
        "lexical analyzer/automata/Helper.h"
        "lexical analyzer/automata/NFA.cpp"
        "lexical analyzer/automata/NFA.h"
        "lexical analyzer/automata/NFAGenerator.cpp"
        "lexical analyzer/automata/NFAGenerator.h"
        "lexical analyzer/automata/NFAOperations.cpp"
        "lexical analyzer/automata/NFAOperations.h"
        "lexical analyzer/automata/ReducedDFA.cpp"
        "lexical analyzer/automata/ReducedDFA.h"
        "lexical analyzer/automata/State.cpp"
        "lexical analyzer/automata/State.h"
        "lexical analyzer/automata/Tokenizer.cpp"
        "lexical analyzer/automata/Tokenizer.h"
        "lexical analyzer/file_services/FileHandler.h"
        "lexical analyzer/file_services/FileReader.cpp"
        "lexical analyzer/file_services/FileReader.h"
        "lexical analyzer/file_services/FileWriter.cpp"
        "lexical analyzer/file_services/FileWriter.h"
        "lexical analyzer/file_services/GrammarReader.cpp"
        "lexical analyzer/file_services/GrammarReader.h"
        "lexical analyzer/file_services/SourceProgramReader.cpp"
        "lexical analyzer/file_services/SourceProgramReader.h"
        "lexical analyzer/ErrorHandler.cpp"
        "lexical analyzer/ErrorHandler.h"
        "lexical analyzer/LexicalController.cpp"
        "lexical analyzer/LexicalController.h"
        "main.cpp"
        "lexical analyzer/SymbolTable.cpp"
        "lexical analyzer/SymbolTable.h"
        parser/ParserController.cpp
        parser/ParserController.h parser/NonTerminal.cpp parser/NonTerminal.h)

