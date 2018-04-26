//
// Created by ahmed on 16/03/18.
//

#include "FileReader.h"
#include <fstream>

using namespace std;

File_Reader::File_Reader()
{}

std::vector<std::string> File_Reader::read(const std::string file_name)
{
    string line;

    ifstream file;
    file.open(file_name, ios::in);

    while(getline(file, line))
    {
        file_stream.push_back(line);
    }
    file.close();
    return file_stream;
}

void File_Reader::write(const std::string file_name, const std::vector<std::string> data_stream)
{}
