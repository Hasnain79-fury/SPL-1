#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Table {
public:
    string name;
    vector<vector<string>> data;

    Table(const string& table_name, int rows, int cols);

    void saveToFile() const;

    void loadFromFile();

    void display() const;
};

bool tableExistsOnDisk(const string& table_name);

#endif // TABLE_H
