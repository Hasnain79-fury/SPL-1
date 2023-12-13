#include <iostream>
#include <sstream>

using namespace std;

string parseTableName(const string& query) {
    istringstream iss(query);
    string keyword, tableName;

    
    iss >> keyword;

   
    if (keyword == "SELECT") {
        // Skip the * or column names
        iss >> keyword;

        // Read the FROM keyword
        iss >> keyword;

        // Read the table name
        iss >> tableName;
    } else {
        // Handle error for invalid query
        cout << "Invalid SELECT query." << endl;
    }

    return tableName;
}

int main() {
    // Example SQL query
    string sqlQuery ;
    cout<<"Enter create command: ";
                 
                getline(cin, sqlQuery);

    // Parse the table name
    string tableName = parseTableName(sqlQuery);

    // Display the result
    cout << "Table Name: " << tableName << endl;

    return 0;
}
