
#include "../header/csv_reader.h"

CSV_Reader::CSV_Reader(string file) {
	file_name = file;
	read_contents_of_file();
}


void CSV_Reader::read_contents_of_file() {
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