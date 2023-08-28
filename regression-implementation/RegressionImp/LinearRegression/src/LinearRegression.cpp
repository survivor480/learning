#include "LinearRegression.h"

LinearRegression::LinearRegression(string file) {
    file_name = file;
    read_contents_of_file();
}

void LinearRegression::read_contents_of_file() {
    vector<string> row;
    string line, word;
    vector<string> dependencies;

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
                    if (i % 2 == 0) {
                        // cout<<word<<" ";
                        // cout<<word<<" ";
                        data["x"].push_back(stoi(word));
                    }
                    else {
                        // cout<<word<<" ";
                        data["y"].push_back(stoi(word));
                    }
                    i++;
                }
            }
            j++;
        }
    }
}

double LinearRegression::sum_of_x() {
    int sum_of_xi = 0;
    for (auto& it : data["x"]) {
        sum_of_xi += it;
    }
    return sum_of_xi;
}

double LinearRegression::sum_of_y() {
    int sum_of_yi = 0;
    for (auto& it : data["y"]) {
        sum_of_yi += it;
    }
    return sum_of_yi;
}

double LinearRegression::calculate_Sxx() {
    double sum_of_xi_squared = 0;
    double square_of_sum_of_xi;

    for (int i = 0; i < data["x"].size(); i++) {
        sum_of_xi_squared += data["x"][i] * data["x"][i];
    }

    square_of_sum_of_xi = sum_of_x() * sum_of_x();
    square_of_sum_of_xi = square_of_sum_of_xi / data["x"].size();

    return sum_of_xi_squared - square_of_sum_of_xi;
}


double LinearRegression::calculate_Sxy() {
    double sum_of_xi_yi = 0;
    double sum_of_x_into_sum_of_y;
    for (int i = 0; i < data["x"].size(); i++) {
        sum_of_xi_yi += data["x"][i] * data["y"][i];
    }
    sum_of_x_into_sum_of_y = sum_of_x() * sum_of_y();
    sum_of_x_into_sum_of_y = sum_of_x_into_sum_of_y / data["x"].size();

    return sum_of_xi_yi - sum_of_x_into_sum_of_y;
}


double LinearRegression::calculate_mean_of_x() {
    return sum_of_x() / data["x"].size();
}

double LinearRegression::calculate_mean_of_y() {
    return sum_of_y() / data["y"].size();
}


double LinearRegression::beta_1(){
    return calculate_Sxy() / calculate_Sxx();
}

double LinearRegression::beta_0() {
    double temp = beta_1() * calculate_mean_of_x();
    return calculate_mean_of_y() - temp;
}

void LinearRegression::regression_line() {
    cout << "The final regression line is y=" << beta_0() << " + " << beta_1() << "x" << endl;
}


int main() {
    LinearRegression set1("../data/my_data.csv");
    set1.regression_line();
}
