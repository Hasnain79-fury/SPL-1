#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Table {
public:
    string name;
    vector<vector<string>> data;

    Table(const string& table_name, int rows, int cols) : name(table_name), data(rows, vector<string>(cols)) {}

    void saveToFile() const {
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

    void loadFromFile() {
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

    void display() const {
        cout << "Table Name: " << name << endl;
        for (int i = 0; i < data.size(); i++) {
            for (int j = 0; j < data[i].size(); j++) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }
};

bool tableExistsOnDisk(const string& table_name) {
    ifstream file(table_name + ".txt");
    return file.good();
}

int main() {
    cout << "Enter table name: ";
    string table_name;
    cin >> table_name;

    if (tableExistsOnDisk(table_name)) {
        cout << "Table with the same name already exists. Loading existing table." << endl;

        // Create a temporary table to load existing data
        Table existingTable(table_name, 5, 3);
        existingTable.loadFromFile();
        existingTable.display();
    } else {
        int row,column;
        cout<<"Enter num of rows and columns in your table";
        cin>>row>>column;
        // Create a table with 5 rows and 3 columns
        Table newTable(table_name, row, column );

        cout << "Create Table: " << endl;

        for (int i = 0; i < newTable.data.size(); i++) {
            for (int j = 0; j < newTable.data[i].size(); j++) {
                cin >> newTable.data[i][j];
            }
        }

        newTable.saveToFile();
        newTable.display();
    }

    return 0;
}
