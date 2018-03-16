cmake_minimum_required(VERSION 3.9)
project(lexical_analyzer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCEFILES main.cpp file_services/FileReader.cpp  file_services/FileWriter.cpp file_services/SourceProgramReader.cpp
                LexicalController.cpp SymbolTable.cpp ErrorHandler.cpp automata/DFATransformer.cpp automata/ReducedDFA.cpp file_services/GrammarReader.cpp file_services/GrammarReader.h)

set(HEADERFILES file_services/FileReader.h file_services/FileWriter.h file_services/SourceProgramReader.h
                LexicalController.h SymbolTable.h ErrorHandler.h automata/NFAGenerator.h  automata/DFATransformer.h
                automata/ReducedDFA.h)

add_executable(lexical_analyzer ${SOURCEFILES})