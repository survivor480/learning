#pragma once

/*
            B = ((XT x X)^-1 x ((X^-1) x y))

             _          _                            _       _
            | 1 7 560    |                          |  16.68  |
            | 1 3 220    |                          |  11.50  |
            | 1 3 340    |                          |  12.03  |
            | 1 4 80     |                          |  14.88  |
            | 1 6 150    |                          |  13.75  |
            | 1 7 330    |                          |  18.11  |
            | 1 2 110    |                          |   8.00  |
            | 1 7 210    |                          |  17.83  |
            | 1 30 1460  |                          |  79.24  |
            | 1 5 605    |                          |  21.50  |
    X =     | 1 16 688   |                    y =   |  40.33  |
            | 1 10 215   |                          |  21.00  |
            | 1 4 255    |                          |  13.50  |
            | 1 6 462    |                          |  19.75  |
            | 1 9 448    |                          |  24.00  |
            | 1 10 776   |                          |  29.00  |
            | 1 6 200    |                          |  15.35  |
            | 1 7 132    |                          |  19.00  |
            | 1 3 36     |                          |   9.50  |
            | 1 17 770   |                          |  35.10  |
            | 1 10 140   |                          |  17.90  |
            | 1 26 810   |                          |  52.32  |
            | 1 9 450    |                          |  18.75  |
            | 1 8 635    |                          |  19.83  |
            |_1 4 150   _|                          |_ 10.75 _|


        The X'X matrix is


                 _                         _        _          _                _                              _
                | 1      1       ....    1  |      | 1  7   560 |              | 25         219         10232   |
        X'X =   | 7      3       ....    4  | x    | 1  3   220 |           =  | 219        3055        133899  |
                |_560   220      ....   150_|      |.....       |              |_10232      133899      6725688_|
                                                   |_1  4   150_|


                 _                         _        _           _                _         _
                | 1      1       ....    1  |      |    16.68    |              | 559.60    |
        X'y =   | 7      3       ....    4  | x    |    11.50    |          =   | 7375.44   |
                |_560   220      ....   150_|      |    ....     |              |_337072.00_|
                                                   |_   10.75   _|


        B = ((X'X)^-1(X'y))

        With this we get a single dimension array of values for all coefficients of all the regressors.

        The final equation is y = 2.34123 + 1.61591 x1 + 0.0143848 x2



        Make a chart in Excel using c++
        https://blog.aspose.com/cells/create-charts-in-excel-spreadsheets-using-cpp/#:~:text=Create%20Line%20Chart%20in%20Excel%20using%20C%2B%2B,-To%20create%20a&text=Firstly%2C%20create%20an%20instance%20of,the%20data%20for%20the%20chart.

*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <stdarg.h>


using namespace std;


// Overloaded cout operator. This prints the vector data structure in the particular way we want
template <class T>
ostream& operator << (ostream& out, vector<T> data) {
    for (auto& it : data) {
        cout << it << endl;
    }
    return out;
}


// Overloaded double vector. This prints the vector of vector data structure in the particular way we want
template <class T>
ostream& operator << (ostream& out, vector<vector<T>> data) {
    for (auto& it : data) {
        for (auto& itr : it) {
            cout << itr << " ";
        }
        cout << endl;
    }
    return out;
}

// A simple function to initialize the 2D vector such that it is easier to push the required data inside of the vector
void init_2Dvector(vector<vector<double> >& vec, int x_dim, int y_dim) {
    vec.resize(x_dim);
    for (int i = 0; i < vec.size(); i++)
        vec[i].resize(y_dim);
}


// This is the multiple linear Regression class that we have access to.

class MultipleLinearRegression {
private:
    string file_name;
    vector<int> y;
    vector<string> regressors;
    map<string, vector<double>> data;
    map<string, vector<string>> data_1;
    vector<vector<double>> independent_variables;
    vector<vector<double>> transpose_independent_variables;

public:

    vector<string> dependencies;

    // Constructor to receive the address of the file.

    MultipleLinearRegression(string file);

    // Function to read the contents of the file
    void read_contents_of_file();

    // return the exact operator to print to the console
    vector<string> operator[](string temp);


    // Create the vector of the regressors for just putting it into the regression table
    vector<vector<double>> generate_x_array(vector<string>& regressors);

    // Generate the results array. This will serve as the Y array which is mentioned in the formula.
    vector<double> generate_y_array(vector<string>& regressor);

    // The original matrix is transpose in this function. This function just serves the purpose of transposing the regressor array
    vector<vector<double>> transpose_matrix();


    // The original matrix is a generic function which can transpose any matrix that we want
    vector<vector<double>> generic_transpose_matrix(vector<vector<double>> A);


    // Multiplication of a 2Dx2D array. Mainly required for the purpose of multiplying the X matrix to its transpose
    vector<vector<double>> matrix_multiplication_2d_2d(vector<vector<double>> a1, vector<vector<double>> b1);

    // Function to multiply a 2D array to a 1D array. This is used for the purpose of multiplying X'y and then the product of the previous 2D-2D multiplication and
    // 2D-1D multiplication obtained in this step. Please refer to the comments on the top for a better understanding.
    vector<double> matrix_multiplication_2d_1d(vector<vector<double>> a1, vector<double> b1);

    // Obtain the cofactor related to an element in a matrix
    vector<vector<double>> getCofactor(vector<vector<double>>& A, int p, int q, int n); 

    // Generic function for determinant of a matrix
    double determinant(vector<vector<double>>& A, int n);

    // Generic adjoint function to find the adjoint of a given matrix
    vector<vector<double>> adjoint(vector<vector<double>> A);

    // Generic inverse to find the inverse of a matrix
    vector<vector<double>> inverse(vector<vector<double>>& A);

};


