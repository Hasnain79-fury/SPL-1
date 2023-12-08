#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <list>

using namespace std;

class HashTable {
private:
    vector<list<vector<string>>> buckets;
    size_t numBuckets;

public:
    HashTable(size_t buckets_count) : numBuckets(buckets_count), buckets(buckets_count) {}

    size_t hashFunction(const string& key) const {
        // Simple hash function for demonstration purposes
        return hash<string>{}(key) % numBuckets;
    }

    void insert(const string& key, const vector<string>& data) {
        size_t bucketIndex = hashFunction(key);
        buckets[bucketIndex].push_back(data);
    }

    void display() const {
        for (size_t i = 0; i < numBuckets; ++i) {
            cout << "Bucket " << i << ": ";
            for (const auto& item : buckets[i]) {
                for (const string& cell : item) {
                    cout << cell << " ";
                }
                cout << "| ";
            }
            cout << endl;
        }
    }
};

class Table {

   

public:
     string name;
    vector<string> columnNames;
    vector<vector<string>> data;
    Table(const string& table_name, int rows, int cols)
        : name(table_name), data(rows, vector<string>(cols)) {}

    void setColumnNames() {
        cout << "Enter column names for the table:" << endl;
        for (int i = 0; i < data[0].size(); i++) {
            string columnName;
            cout << "Column " << i + 1 << ": ";
            cin >> columnName;
            columnNames.push_back(columnName);
        }
    }

    void saveToFile() const {
        ofstream file(name + ".txt");

        if (file.is_open()) {
            file << "Table Name: " << name << endl;

            for (const string& columnName : columnNames) {
                file << " " << columnName;
            }
            file << endl;

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

            // Read the first line containing the table name
            getline(file, line);

            columnNames.clear();

            if (getline(file, line)) {
                istringstream columnNamesStream(line);
                string columnName;

                while (columnNamesStream >> columnName) {
                    columnNames.push_back(columnName);
                }
            }

            // Clear the existing data and column names
            data.clear();

            // Read data until there are no more non-empty lines
            while (getline(file, line) && !line.empty()) {
                istringstream rowStream(line);
                vector<string> row;

                string cell;
                while (rowStream >> cell) {
                    row.push_back(cell);
                }

                data.push_back(row);
            }

            file.close();
            cout << "Table data loaded from " << name << ".txt" << endl;
        } else {
            cout << "Table file not found." << endl;
        }
    }

    void insert(HashTable& hashTable) {
        cout << "Insert new elements: ";
        vector<string> temp;
        for (int i = 0; i < data[0].size(); i++) {
            string x;
            cin >> x;
            temp.push_back(x);
        }

        // Insert the data into the hash table
        hashTable.insert(temp[0], temp);

        // Insert the data into the main data vector
        data.push_back(temp);
    }

    void display() const {
        cout << "Table Name: " << name << endl;
        for (const auto& x : columnNames) {
            cout << x << " ";
        }
        cout << endl;
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
        Table existingTable(table_name, 3, 5);
        existingTable.loadFromFile();
        existingTable.display();

        // Create a hash table with a specified number of buckets
        HashTable hashTable(10);

        // Insert data into the hash table and the existing table
        existingTable.insert(hashTable);

        // Display the hash table
        cout << "\nHash Table:\n";
        hashTable.display();

        // Save the updated existing table
        existingTable.saveToFile();
        existingTable.display();
    } else {
        int row, column;
        cout << "Enter num of rows and columns in your table: ";
        cin >> row >> column;

        // Create a table with user-specified rows and columns
        Table newTable(table_name, row, column);

        // Set column names for the new table
        newTable.setColumnNames();

        cout << "Create Table: " << endl;

        // Input data for the new table
        for (int i = 0; i < newTable.data.size(); i++) {
            for (int j = 0; j < newTable.data[i].size(); j++) {
                cin >> newTable.data[i][j];
            }
        }

        // Save the new table to a file
        newTable.saveToFile();
        newTable.display();
    }

    return 0;
}
