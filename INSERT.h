#include <bits/stdc++.h>
#include <fstream>
using namespace std;
#define ll long long

ll flag = 0;

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

void insertTable() {
    string into, tablename, value, str;

    // Input: INTO table_name VALUES (
    cin >> into;
    cin >> tablename;
    cin >> value;
    cin >> str;

    // Store table name, total row, total column from file.
    // First, need to store the total table count.
    ifstream ifile;

    ifile.open("FileInformation.txt", ios::in);
    string tableCount;
    ll totalTables;
    ifile >> tableCount;
    if (tableCount == "")
        totalTables = 0;
    else
        totalTables = stoll(tableCount);

    // Close the file.
    ifile.close();

    // If there is no table, show this message.
    if (totalTables == 0) {
        cout << "Can't insert values as there is no table. First, create a table.\n";
    } else {
        ifstream ifile;

        ifile.open("FileInformation.txt", ios::in);

        ifile >> totalTables;

        TableInfo tableInfo[totalTables];

        // Store table name, total row, total column.

        for (ll i = 0; i < totalTables; i++) {
            ifile >> tableInfo[i].table_name;
            ifile >> tableInfo[i].row;
            ifile >> tableInfo[i].column;
        }

        ifile.close();

        remove("FileInformation.txt");

        ofstream ofile;

        ofile.open("FileInformation.txt", ios::app);

        ofile << totalTables << '\n';

        for (ll i = 0; i < totalTables; i++) {
            if (tableInfo[i].table_name == tablename) {
                ofile << tableInfo[i].table_name << " ";
                ofile << tableInfo[i].row + 1 << " ";
                ofile << tableInfo[i].column << " ";
                ofile << endl;

            } else {
                ofile << tableInfo[i].table_name << " ";
                ofile << tableInfo[i].row << " ";
                ofile << tableInfo[i].column << " ";
                ofile << endl;
            }
        }

        ofile.close();

        ll sumOfRows = 0;

        for (ll i = 0; i < totalTables; i++) {
            sumOfRows += tableInfo[i].row;
        }

        initializeField(sumOfRows);
        initializeHeader(totalTables);

        // Store information from the database.
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

            if (tableInfo[i].table_name == tablename) {
                flag = 1;
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
            cout << "Row inserted in " << tablename << " successfully!" << endl << endl;
        } else {
            cout << "There is no such table." << endl << endl;
        }
    }
}
