#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

class LinearRegression {

private:
    string file_name;
    map<string, vector<int>> data;
    vector<int> x;
    vector<int> y;

public:
    LinearRegression(string file);

    void read_contents_of_file();

    double sum_of_x();

    double sum_of_y();

    double calculate_Sxx();

    double calculate_Sxy();

    double calculate_mean_of_x();

    double calculate_mean_of_y();

    double beta_1();

    double beta_0();

    void regression_line();
};

