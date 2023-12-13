#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <list>
#include <vector>
#include <stdexcept>
#include <bits/stdc++.h>
using namespace std;

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

/*CREATE TABLE alvi ( a, a, a )
INSERT INTO ALVI VALUES ( a, a, a )
*/

void parseInsertInto(const string& cmd, string& tableName, vector<string>& values) {
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

}

void parseCreateTable(const string& cmd, string& tableName, vector<string>& columnNames) {
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
        tableName = cmd.substr(13, posOpen - 14); // 13 is the length of "CREATE TABLE "
    } else {
        // Invalid command format
        cout << "Invalid CREATE TABLE command format." << endl;
    }
}

int main() {
    // Sample CREATE TABLE command
    string cmd;
                 cout<<"Enter create command: ";
                 cin.ignore();
                getline(cin, cmd);
                 

   string tableName;
   vector<string> values;

   parseInsertInto(cmd,tableName,values);
   cout<<tableName<<endl;
   for(auto x : values){
    cout<<x;
   }

    return 0;
}
