cmake_minimum_required(VERSION 3.8)
project(lexical_analyzer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCEFILES main.cpp file_services/FileReader.cpp  file_services/FileWriter.cpp file_services/SourceProgramReader.cpp
        LexicalController.cpp SymbolTable.cpp ErrorHandler.cpp automata/State.cpp automata/NFAGenerator.cpp
        automata/NFA.cpp automata/DFATransformer.cpp automata/ReducedDFA.cpp file_services/GrammarReader.cpp
        automata/TransitionTable.cpp automata/Helper.cpp automata/DFANode.cpp automata/NFAOperations.cpp
        automata/Utilities.cpp)

set(HEADERFILES file_services/FileHandler.h file_services/FileReader.h file_services/FileWriter.h file_services/SourceProgramReader.h
        LexicalController.h SymbolTable.h ErrorHandler.h automata/State.h automata/NFAGenerator.h
        automata/DFATransformer.h automata/Helper.h automata/ReducedDFA.h automata/NFA.h automata/NFANode.h automata/NFAOperations.h
        automata/Utilities.h)

add_executable(lexical_analyzer ${SOURCEFILES})