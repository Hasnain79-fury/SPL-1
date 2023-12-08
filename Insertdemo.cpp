#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Table {
public:
    string name;
    vector<string> columnNames;
    vector<vector<string>> data;

    Table(const string& table_name, int rows, int cols) : name(table_name), data(rows, vector<string>(cols)) {}

    void setColumnNames(){
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
           // file << "Column Names:";
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

            // Clear the existing column names
            //columnNames.clear();

            // Skip the "Column Names:" part
            //columnNamesStream >> columnName; // Read and ignore "Column"
            //columnNamesStream >> columnName; // Read and ignore "Names:"

            // Read the actual column names
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

    void insert(){
        cout<<"Insert new elements: ";
        vector<string> temp;
        for(int i = 0 ; i < data[0].size();i++){
            string x;
            cin>>x;
            temp.push_back(x);

        }
        data.push_back(temp);
    }


    void display() const {
        cout << "Table Name: " << name << endl;
        for(auto x: columnNames){
            cout<<x<<" ";
        }
        cout<<endl;
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
        existingTable.insert();
        existingTable.saveToFile();
        existingTable.display();

    } else {
        int row,column;
        cout<<"Enter num of rows and columns in your table";
        cin>>row>>column;
        // Create a table with 5 rows and 3 columns
        Table newTable(table_name, row, column );

        //cout<<"Enter the column names: ";

        newTable.setColumnNames();

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
