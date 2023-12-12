#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <list>
#include <vector>
#include <stdexcept>
#include <bits/stdc++.h>
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

    void setColumnNames(vector<string> s) {
        //cout << "Enter column names for the table:" << endl;
        for (int i = 0; i < s.size(); i++) {
            string columnName;
            //cout << "Column " << i + 1 << ": ";
            //cin >> columnName;
            columnName = s[i];
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

    void insert(HashTable& hashTable,vector<string> s) {
        //cout << "Insert new elements: ";
        vector<string> temp;
        for (int i = 0; i < columnNames.size(); i++) {
            string x;
            x=s[i];
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
    
    // Function to select all rows and columns
    vector<vector<string>> selectAll() const {
        return data;
    }

    // Function to select rows based on a condition
    vector<vector<string>> selectWhere(const string& columnName, const string& value) const {
        vector<vector<string>> result;
        size_t columnIndex = findColumnIndex(columnName);

        if (columnIndex != string::npos) {
            for (const auto& row : data) {
                if (row.size() > columnIndex && row[columnIndex] == value) {
                    result.push_back(row);
                }
            }
        }

        return result;
    }

    // Function to select distinct values from a column
    vector<string> selectDistinct(const string& columnName) const {
        vector<string> distinctValues;
        size_t columnIndex = findColumnIndex(columnName);

        if (columnIndex != string::npos) {
            unordered_set<string> uniqueSet;

            for (const auto& row : data) {
                if (row.size() > columnIndex) {
                    uniqueSet.insert(row[columnIndex]);
                }
            }

            distinctValues.assign(uniqueSet.begin(), uniqueSet.end());
        }

        return distinctValues;
    }

    // Function to find column index
    size_t findColumnIndex(const string& columnName) const {
        for (size_t i = 0; i < columnNames.size(); ++i) {
            if (columnNames[i] == columnName) {
                return i;
            }
        }
        return string::npos; // Not found
    }

    vector<string> selectColumn(const string& columnName) const {
        vector<string> result;
        size_t columnIndex = findColumnIndex(columnName);

        if (columnIndex != string::npos) {
            for (const auto& row : data) {
                if (row.size() > columnIndex) {
                    result.push_back(row[columnIndex]);
                }
            }
        }

        return result;
    }

};





class demo{
        public:
            

            void create(){
                // Variables to store the result
                vector<string> columnNames;
                 string tableName; string cmd;
                 cout<<"Enter create command: ";
                 cin.ignore();
                getline(cin, cmd);
                 
                 
               // parsing

               // Find the position of the opening and closing parentheses
    size_t posOpen = cmd.find("(");
    size_t posClose = cmd.find(")");

    if (posOpen != string::npos && posClose != string::npos && posOpen < posClose) {
        // Extract the substring between the parentheses
        string columnsSubstring = cmd.substr(posOpen + 1, posClose - posOpen - 1);

        // Tokenize the substring based on commas
        stringstream ss(columnsSubstring);
        string token;

        // Count the number of columns and store them in the vector
        while (getline(ss, token, ',')) {
            // Remove leading and trailing whitespaces from the token
            token.erase(remove_if(token.begin(), token.end(), ::isspace), token.end());

            // Skip empty tokens
            if (!token.empty()) {
                columnNames.push_back(token);
            }
        }

        // Extract the table name (assuming it's the first word in the command)
        tableName = cmd.substr(12, posOpen - 13); // 13 is the length of "CREATE TABLE "
    } else {
        // Invalid command format
        cout << "Invalid CREATE TABLE command format." << endl;
    }
                

                if(tableExistsOnDisk(tableName)){
                    cout<<"Table exists select another name";
                }
                else{
                    
                    int x,y;
                   // cout<<"Enter num of rows and columns in the table : ";
                    x=1; y = columnNames.size();
                    Table newTable(tableName,x,y);
                    newTable.setColumnNames(columnNames);

                    newTable.saveToFile();


                }


            }

            

            void insert(){
                //first give the name and check if the table exists on disk
                string cmd;
                cout<<"Enter insert into command: ";
                 cin.ignore();
                getline(cin, cmd);

   string tableName;
   vector<string> values;

    size_t posOpen = cmd.find("(");
        size_t posClose = cmd.find(")");
        if (posOpen != string::npos && posClose != string::npos && posOpen < posClose) {
        // Extract the substring between the parentheses
        string columnsSubstring = cmd.substr(posOpen + 1, posClose - posOpen - 1);

        // Tokenize the substring based on commas
        stringstream ss(columnsSubstring);
        string token;

        // Count the number of columns and store them in the vector
        while (getline(ss, token, ',')) {
            // Remove leading and trailing whitespaces from the token
            token.erase(remove_if(token.begin(), token.end(), ::isspace), token.end());

            // Skip empty tokens
            if (!token.empty()) {
                values.push_back(token);
            }
        }
          tableName = cmd.substr(11, posOpen - 19);

    }

    else {
        // Invalid command format
        cout << "Invalid CREATE TABLE command format." << endl;
    }
                if(tableExistsOnDisk(tableName)){
                    Table existingTable(tableName,3,5);
                    existingTable.loadFromFile();
                    existingTable.display();

                    HashTable hashTable(10);

                    existingTable.insert(hashTable,values);

                    existingTable.saveToFile();
                    existingTable.display();

                }
                else{
                    cout<<"Table doesn't exist"<<endl;
                }

            }

            void selectColumn() {
        string tableName, columnName;
        cout << "Enter table name: ";
        cin >> tableName;

        if (tableExistsOnDisk(tableName)) {
            Table existingTable(tableName, 3, 5);
            existingTable.loadFromFile();
            existingTable.display();

            cout << "Enter column name to select: ";
            cin >> columnName;

            vector<string> selectedColumn = existingTable.selectColumn(columnName);

            cout << "Selected Column: " << columnName << endl;
            for (const string& value : selectedColumn) {
                cout << value << endl;
            }
        } else {
            cout << "Table doesn't exist" << endl;
        }
    }

    void selectAll() {
        string tableName;
        cout << "Enter table name: ";
        cin >> tableName;

        if (tableExistsOnDisk(tableName)) {
            Table existingTable(tableName, 3, 5);
            existingTable.loadFromFile();
            existingTable.display();

            vector<vector<string>> result = existingTable.selectAll();

            cout << "Selected All Rows and Columns: " << endl;
            displayResult(result);
        } else {
            cout << "Table doesn't exist" << endl;
        }
    }

    // Function to select rows based on a condition
    void selectWhere() {
        string tableName, columnName, value;
        cout << "Enter table name: ";
        cin >> tableName;

        if (tableExistsOnDisk(tableName)) {
            Table existingTable(tableName, 3, 5);
            existingTable.loadFromFile();
            existingTable.display();

            cout << "Enter column name and value to select: ";
            cin >> columnName >> value;

            vector<vector<string>> result = existingTable.selectWhere(columnName, value);

            cout << "Selected Rows Where " << columnName << " = " << value << ":" << endl;
            displayResult(result);
        } else {
            cout << "Table doesn't exist" << endl;
        }
    }

    // Function to select distinct values from a column
    void selectDistinct() {
        string tableName, columnName;
        cout << "Enter table name: ";
        cin >> tableName;

        if (tableExistsOnDisk(tableName)) {
            Table existingTable(tableName, 3, 5);
            existingTable.loadFromFile();
            existingTable.display();

            cout << "Enter column name to select distinct values: ";
            cin >> columnName;

            vector<string> result = existingTable.selectDistinct(columnName);

            cout << "Distinct Values in Column " << columnName << ":" << endl;
            displayResult(result);
        } else {
            cout << "Table doesn't exist" << endl;
        }
    }

            bool tableExistsOnDisk(const string& table_name) {
                ifstream file(table_name + ".txt");
                return file.good();
        }

    private:
    // Helper function to display the result of a SELECT operation
    void displayResult(const vector<vector<string>>& result) const {
        for (const auto& row : result) {
            for (const string& cell : row) {
                cout << cell << " ";
            }
            cout << endl;
        }
    }

    // Helper function to display the result of a SELECT operation for a single column
    void displayResult(const vector<string>& result) const {
        for (const string& value : result) {
            cout << value << endl;
        }
    }
};

class typecast{
   std::vector<int> stringToInt(const std::vector<std::string>& a) {
    std::vector<int> result;
    
    for (const std::string& str : a) {
        try {
            int num = std::stoi(str);
            result.push_back(num);
        } catch (const std::invalid_argument& e) {
            // Handle invalid conversions (non-integer strings)
            std::cerr << "Invalid argument: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            // Handle out-of-range conversions
            std::cerr << "Out of range: " << e.what() << std::endl;
        }
    }

    return result;
}
};

bool tableExistsOnDisk(const string& table_name) {
    ifstream file(table_name + ".txt");
    return file.good();
}

int main() {
    /*cout << "Enter table name: ";
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


    return 0;*/
    demo d;
    //d.selectAll();
    //Id.create(); 
    d.insert();
    

    //d.selectDistinct();

    //d.selectColumn(); 
}
