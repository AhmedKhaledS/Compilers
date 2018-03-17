#include <iostream>

#include <string>
#include <vector>
#include "file_services/FileWriter.h"
#include "file_services/GrammarReader.h"
#include "file_services/SourceProgramReader.h"
#include "SymbolTable.h"
#include <fstream>

using namespace std;

int main()
{
    std::cout << "Hello, World!" << std::endl;
//    vector<string> s;
//    s.push_back("ahmed");
//    s.push_back("Khaled");
//    s.push_back("Saad");
//    File_Writer fl;
//    fl.write("dataa", s);
    Symbol_table::add_identifier("Name", "Ahmed");
    cout << Symbol_table::search_identifier("Name");

//    Source_program_reader sr;
//    cout << sr.get_next_char_from_src_program("dataa.lan");

    return 0;
}