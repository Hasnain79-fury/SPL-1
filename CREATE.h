#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Structure to hold table information
struct TableInfo {
    string table_name;
    int row;
    int column;
};

// Function to create a new table
void createTable(string tableName, vector<string> columns) {
    // Open files for reading and writing
    ifstream inFile("FileInformation.txt");
    ofstream outFile("FileInformation.txt", ios::app);
    ofstream dbFile("My_database.txt", ios::app);
    ofstream showFile("Table_Showing.txt", ios::app);

    // Read and update total table count
    int totalTables;
    inFile >> totalTables;
    outFile << totalTables + 1 << endl;

    // Store table information
    outFile << tableName << '\t' << 0 << '\t' << columns.size() << endl;

    // Update table showing file
    showFile << endl << tableName << '\t';
    for (string column : columns) {
        showFile << column << '\t' << "columnTypeHere" << '\t';
    }
    showFile << "." << endl;

    // Write table structure and field values
    dbFile << endl << tableName << endl << endl;
    for (string column : columns) {
        dbFile << column << "\t\t\t";
    }
    dbFile << endl << endl;

    // Close files
    inFile.close();
    outFile.close();
    dbFile.close();
    showFile.close();

    cout << "Table created successfully!" << endl;
}

