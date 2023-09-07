#include <bits/stdc++.h>
#include <fstream>
using namespace std;
#define ll long long

// Define a struct to represent table information
struct TableInfo {
    string table_name;
    ll row;
    ll column;
};

string *header;
string *field;

void initializeHeader(ll x) {
    header = new string[x];
}

void initializeField(ll x) {
    field = new string[x];
}

ll flag = 0;

void createTable(string command, string table, string tableName, string str) {
    ifstream infoFile;
    infoFile.open("FileInformation.txt");
    string s;
    ll totalTables;
    ll totalColumns = 0;
    infoFile >> s;
    if (s == "")
        totalTables = 0;
    else
        totalTables = stoll(s);
    infoFile.close();
    if (totalTables == 0) {
        ofstream database;
        database.open("My_database.txt", ios::app);
        database << tableName << endl << endl;

        ofstream tableShowing;
        tableShowing.open("Table_Showing.txt", ios::app);

        tableShowing << tableName << '\t';

        if (str == "(") {
            string type;
            cin >> str >> type;
            while (str != ")") {
                totalColumns++;
                database << str << '\t' << '\t' << '\t';
                tableShowing << str << '\t' << type << '\t';
                cin >> str >> type;
            }
        }
        tableShowing << "." << endl;
        tableShowing.close();
        database << endl << endl;
        remove("FileInformation.txt");
        database.close();
        database.open("FileInformation.txt", ios::app);
        database << totalTables + 1 << endl;
        database << tableName << '\t' << 0 << '\t' << totalColumns << endl;
        database.close();

        cout << endl << endl << "Table created successfully!" << endl << endl;
    } else {
        ifstream ifile;
        ifile.open("FileInformation.txt", ios::in);
        ifile >> totalTables;

        TableInfo tableInfo[totalTables];

        // Storing table name, total row, total column

        for (ll i = 0; i < totalTables; i++) {
            ifile >> tableInfo[i].table_name;
            ifile >> tableInfo[i].row;
            ifile >> tableInfo[i].column;
        }

        ifile.close();

        remove("FileInformation.txt");
        ofstream ofile;
        ofile.open("FileInformation.txt", ios::app);

        ofile << totalTables + 1 << '\n';

        for (ll i = 0; i < totalTables; i++) {
            ofile << tableInfo[i].table_name << '\t';
            ofile << tableInfo[i].row << '\t';
            ofile << tableInfo[i].column << " ";
            ofile << endl;
        }
        ll sumOfRows = 0;

        for (ll i = 0; i < totalTables; i++) {
            sumOfRows += tableInfo[i].row;
        }

        initializeField(sumOfRows);
        initializeHeader(totalTables);

        // Storing the information from the database
        ifstream dataFile;
        dataFile.open("My_database.txt", ios::in);

        string str1, tableName;

        ll index = 0;

        for (ll i = 0; i < totalTables; i++) {
            dataFile >> tableName;
            getline(dataFile, str1);
            getline(dataFile, str1);
            getline(dataFile, header[i]);
            getline(dataFile, str1);

            ll Iindex = 0;

            while (Iindex != tableInfo[i].row) {
                getline(dataFile, field[index]);
                index++;
                Iindex++;
            }

            if (i != totalTables - 1) {
                getline(dataFile, str1);
            }
        }

        dataFile.close();

        remove("My_database.txt");

        ofstream outputFile;

        outputFile.open("My_database.txt", ios::app);

        index = 0;

        for (ll i = 0; i < totalTables; i++) {
            outputFile << tableInfo[i].table_name << endl << endl;
            outputFile << header[i] << endl << endl;

            ll Iindex = 0;

            while (Iindex != tableInfo[i].row) {
                outputFile << field[index] << endl;
                index++;
                Iindex++;
            }

            if (tableInfo[i].table_name == tableName) {
                if (str == "(") {
                    while (1) {
                        string comma;

                        cin >> str >> comma;

                        if (comma != ")") {
                            outputFile << str << "\t" << "\t" << "\t";
                        } else {
                            string ss;
                            cin >> ss;
                            outputFile << str << "\t" << "\t" << "\t";
                            break;
                        }
                    }
                    outputFile << endl;
                }
            }

            if (i != totalTables - 1) {
                outputFile << endl;
            }
        }

        outputFile.close();
        if (flag) {
            cout << "Row inserted in " << tableName << " successfully!" << endl << endl;
        } else {
            cout << "There is no such table." << endl << endl;
        }
    }
}
