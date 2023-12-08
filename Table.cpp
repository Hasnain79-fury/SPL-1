#include "Table.h"

Table::Table(const string& table_name, int rows, int cols) : name(table_name), data(rows, vector<string>(cols)) {}

void Table::saveToFile() const {
    ofstream file(name + ".txt");

    if (file.is_open()) {
        file << "Table Name: " << name << endl;
        for (int i = 0; i < data.size(); i++) {
            for (int j = 0; j < data[i].size(); j++) {
                file << data[i][j] << " ";
            }
            file << endl;
        }
        file.close();
        cout << "Table data saved to " << name << ".txt" << endl;
    } else {
        cout << "Unable to open file for writing." << endl;
    }
}

void Table::loadFromFile() {
    ifstream file(name + ".txt");

    if (file.is_open()) {
        string line;
        getline(file, line);

        for (int i = 0; i < data.size(); i++) {
            for (int j = 0; j < data[i].size(); j++) {
                file >> data[i][j];
            }
        }

        file.close();
        cout << "Table data loaded from " << name << ".txt" << endl;
    } else {
        cout << "Table file not found." << endl;
    }
}

void Table::display() const {
    cout << "Table Name: " << name << endl;
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); j++) {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

bool tableExistsOnDisk(const string& table_name) {
    ifstream file(table_name + ".txt");
    return file.good();
}
