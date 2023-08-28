#include "MultipleLinearRegression.h"

MultipleLinearRegression::MultipleLinearRegression(string file) {
	file_name = file;
	read_contents_of_file();
}


void MultipleLinearRegression::read_contents_of_file() {
    vector<string> row;
    string line, word;

    fstream file(file_name, ios::in);
    if (file.is_open()) {
        int j = 0;
        while (getline(file, line)) {
            row.clear();

            stringstream str(line);
            int i = 0;
            while (getline(str, word, ',')) {
                if (j == 0) {
                    dependencies.push_back(word);
                }
                if (j != 0) {
                    int temp = i % dependencies.size();
                    try {
                        data[dependencies[temp]].push_back(stod(word));
                    }
                    catch (std::invalid_argument) {
                        continue;
                    }
                    data_1[dependencies[temp]].push_back(word);
                    i++;
                }
            }
            j++;
        }
    }
}

vector<string> MultipleLinearRegression::operator[](string temp) {
    return data_1[temp];
}

vector<vector<double>> MultipleLinearRegression::generate_x_array(vector<string>& regressors) {
    for (int i = 0; i < data[regressors[0]].size(); i++) {
            vector<double> temp;
            independent_variables.push_back(temp);
        }

        for (int i = 0; i < regressors.size(); i++) {
            for (int j = 0; j < data[regressors[i]].size(); j++) {
                independent_variables[j].push_back(data[regressors[i]][j]);
            }
        }

        return independent_variables;
}

vector<double> MultipleLinearRegression::generate_y_array(vector<string>& regressor) {
    return data[regressor[0]];
}

vector<vector<double>> MultipleLinearRegression::transpose_matrix() {
    for (int i = 0; i < independent_variables[0].size(); i++) {
        vector<double> temp;
        transpose_independent_variables.push_back(temp);
    }

    for (int i = 0; i < independent_variables.size(); i++) {
        for (int j = 0; j < independent_variables[i].size(); j++) {
            transpose_independent_variables[j].push_back(independent_variables[i][j]);
        }
    }

    return transpose_independent_variables;
}

vector<vector<double>> MultipleLinearRegression::generic_transpose_matrix(vector<vector<double>> A) {
    vector<vector<double>> transpose;
    for (int i = 0; i < A[0].size(); i++) {
        vector<double> temp;
        transpose.push_back(temp);
    }

    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A[i].size(); j++) {
            transpose[j].push_back(A[i][j]);
        }
    }

    return transpose;
}

vector<vector<double>> MultipleLinearRegression::matrix_multiplication_2d_2d(vector<vector<double>> a1, vector<vector<double>> b1) {
    int first_matrix_row_size = a1.size();
    int first_matrix_column_size = a1[0].size();

    int second_matrix_row_size = b1.size();
    int second_matrix_column_size = b1[0].size();

    vector<vector<double>> multiplied_matrix;

    if (first_matrix_column_size != second_matrix_row_size) {
        cout << "No multiplication can be performed by two incompatible matrices";
        return multiplied_matrix;
    }

    init_2Dvector(multiplied_matrix, first_matrix_row_size, second_matrix_column_size);

    for (int i = 0; i < first_matrix_row_size; i++) {
        for (int j = 0; j < second_matrix_column_size; j++) {
            multiplied_matrix[i][j] = 0;

            for (int k = 0; k < first_matrix_column_size; k++) {
                multiplied_matrix[i][j] += a1[i][k] * b1[k][j];
            }
        }
    }

    return multiplied_matrix;
}

vector<double> MultipleLinearRegression::matrix_multiplication_2d_1d(vector<vector<double>> a1, vector<double> b1) {
    int first_matrix_row_size = a1.size();
    int first_matrix_column_size = a1[0].size();

    int second_matrix_row_size = b1.size();
    int second_matrix_column_size = 1;

    vector<double> multiplied_matrix;

    if (first_matrix_column_size != second_matrix_row_size) {
        cout << "No multiplication can be performed by two incompatible matrices";
        return multiplied_matrix;
    }

    for (int i = 0; i < first_matrix_row_size; i++) {
        for (int j = 0; j < second_matrix_column_size; j++) {
            multiplied_matrix.push_back(0);

            for (int k = 0; k < first_matrix_column_size; k++) {
                multiplied_matrix[i] += a1[i][k] * b1[k];
            }
        }
    }

    return multiplied_matrix;
}

vector<vector<double>> MultipleLinearRegression::getCofactor(vector<vector<double>>& A, int p, int q, int n) {

    int i = 0, j = 0;

    vector<double> temp_1;
    vector<vector<double>> temp;
    bool inc = false;

    for (int row = 0; row < n; row++) {
        temp.push_back(temp_1);
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                inc = true;
                temp[j].push_back(A[row][col]);
            }
        }
        if (inc) {
            j++;
            inc = !inc;
        }
    }

    return temp;
}

double MultipleLinearRegression::determinant(vector<vector<double>>& A, int n) {

    double D = 0;

    if (n == 1) {
        return A[0][0];
    }

    if (n == 2) {
        return A[0][0] * A[1][1] - A[1][0] * A[0][1];
    }

    vector<vector<double>> temp;

    int sign = 1;

    for (int f = 0; f < n; f++) {
        temp = getCofactor(A, 0, f, n);
        D += sign * A[0][f] * determinant(temp, n - 1);

        sign = (-1) * sign;
    }

    return D;
}

vector<vector<double>> MultipleLinearRegression::adjoint(vector<vector<double>> A) {

    vector<double> temp_1;
    int N = A.size();
    vector<vector<double>> temp;
    if (A.size() == 1) {
        temp.push_back(temp_1);
        temp[0].push_back(1);
    }

    vector<vector<double>> adj;
    vector<vector<double>> transpose_adj;

    int sign = 1;

    for (int i = 0; i < A.size(); i++) {
        temp.push_back(temp_1);
        adj.push_back(temp_1);
        for (int j = 0; j < A[i].size(); j++) {
            temp = getCofactor(A, i, j, A.size());

            sign = ((i + j) % 2 == 0) ? 1 : -1;

            adj[i].push_back((sign * (determinant(temp, N - 1))));
        }
    }

    transpose_adj = generic_transpose_matrix(adj);
    return transpose_adj;
}


vector<vector<double>> MultipleLinearRegression::inverse(vector<vector<double>>& A) {
    double det = determinant(A, A.size());

    vector<double> temp_1;
    vector<vector<double>> inverse;

    if (det == 0) {
        cout << "Singular Matrix does not have an inverse";
        return inverse;
    }

    vector<vector<double>> adj;
    adj = adjoint(A);

    for (int i = 0; i < A.size(); i++) {
        inverse.push_back(temp_1);
        for (int j = 0; j < A.size(); j++) {
            inverse[i].push_back(adj[i][j] / det);
        }
    }

    return inverse;
}

int main() {
    MultipleLinearRegression set1("../data/my_data.csv");

    vector<string> x_regressors;
    vector<string> y_regressor;

    x_regressors.push_back("x1");
    x_regressors.push_back("x2");
    x_regressors.push_back("x3");
    // vector<vector<double>> temp = set1.generate_x_array(regressors);

    vector<vector<double>> temp = set1.generate_x_array(x_regressors);

    y_regressor.push_back("y");
    vector<double> temp_1 = set1.generate_y_array(y_regressor);

    vector<vector<double>> transpose_temp = set1.transpose_matrix();

    vector<vector<double>> multiplied_matrix_1 = set1.matrix_multiplication_2d_2d(transpose_temp, temp);

    vector<double> multiplied_matrix_2 = set1.matrix_multiplication_2d_1d(transpose_temp, temp_1);

    vector<vector<double>> temp_10;

    temp_10 = set1.inverse(multiplied_matrix_1);

    vector<double> final_multiplied_matrix = set1.matrix_multiplication_2d_1d(temp_10, multiplied_matrix_2);

    cout << "The final equation of multiple_linear_regression is: y = ";

    int m = 0;
    for (auto& it : final_multiplied_matrix) {
        cout << it;
        if (m != 0) {
            cout << " x" << m;
        }
        if (m != final_multiplied_matrix.size() - 1) {
            cout << " + ";
            m++;
        }
        else {
            cout << ". " << endl;
        }
    }

    return 0;
}



