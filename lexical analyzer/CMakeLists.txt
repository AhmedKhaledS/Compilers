cmake_minimum_required(VERSION 3.9)
project(lexical_analyzer)

set(CMAKE_CXX_STANDARD 11)

add_executable(lexical_analyzer main.cpp "file services/FileHandler.h" "file services/FileReader.cpp" "file services/FileReader.h" "file services/FileWriter.cpp" "file services/FileWriter.h" "file services/SourceProgramReader.cpp" "file services/SourceProgramReader.h" LexicalController.cpp LexicalController.h SymbolTable.cpp SymbolTable.h ErrorHandler.cpp ErrorHandler.h Automata/NFAGenerator.cpp Automata/NFAGenerator.h Automata/DFATransformer.cpp Automata/DFATransformer.h Automata/ReducedDFA.cpp Automata/ReducedDFA.h)