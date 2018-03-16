//
// Created by ahmed on 16/03/18.
//

#include "FileWriter.h"
#include "iostream"
#include <fstream>

using namespace std;

File_Writer::File_Writer()
{}

std::vector<std::string> File_Writer::read(std::string file_name)
{}

void File_Writer::write(std::string file_name, std::vector<std::string> data_stream)
{
    ofstream file(file_name + ".lan");
    for (string line : data_stream)
    {
        file << line + "\n";
    }
    file.close();
}