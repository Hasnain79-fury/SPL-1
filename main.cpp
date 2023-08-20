#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Column {
    string name;
};

struct Row {
    vector<string> values;
};

struct Table {
    string name;
    vector<Column> columns;
    vector<Row> rows;
};

void readCSVFile(const string& filename, Table& table) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    // Read the header row to get column names
    string header;
    if (getline(file, header)) {
        istringstream headerStream(header);
        string columnName;
        while (getline(headerStream, columnName, ',')) {
            table.columns.push_back({columnName});
        }
    } else {
        cerr << "Empty or invalid CSV file: " << filename << endl;
        file.close();
        return;
    }

    // Read data rows and populate rows in the table
    string rowStr;
    while (getline(file, rowStr)) {
        Row row;
        istringstream rowStream(rowStr);
        string value;
        while (getline(rowStream, value, ',')) {
            row.values.push_back(value);
        }
        table.rows.push_back(row);
    }

    file.close();
}

int main() {
    Table employeesTable;
    employeesTable.name = "employees";

    // Read data from a CSV file
    readCSVFile("employees.csv", employeesTable);

    // Display the loaded table data
    cout << "Table: " << employeesTable.name << endl;
    for (const Column& col : employeesTable.columns) {
        cout << col.name << "\t";
    }
    cout << endl;

    for (const Row& row : employeesTable.rows) {
        for (const string& value : row.values) {
            cout << value << "\t";
        }
        cout << std::endl;
    }

    return 0;
}
