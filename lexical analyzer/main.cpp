#include <iostream>

#include <string>
#include <vector>
#include "file_services/FileWriter.h"
#include <fstream>

using namespace std;

int main()
{
    std::cout << "Hello, World!" << std::endl;
    vector<string> s;
    s.push_back("ahmed");
    s.push_back("Khaled");
    s.push_back("Saad");
    File_Writer fl;
    fl.write("dataa", s);

    return 0;
}