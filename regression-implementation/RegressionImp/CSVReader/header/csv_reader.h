#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

class CSV_Reader {

public:
    string file_name;
    vector<int> y;
    vector<string> regressors;
    map<string, vector<double>> data;
    map<string, vector<string>> data_1;
    vector<vector<double>> independent_variables;
    vector<vector<double>> transpose_independent_variables;

    vector<string> dependencies;

    // Constructor to receive the address of the file.
    CSV_Reader(string file);

    // Function to read the contents of the file
    void read_contents_of_file();

};
