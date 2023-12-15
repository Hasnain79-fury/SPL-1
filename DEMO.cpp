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
#include <vector>
#include <list>
#include <string>
#include <functional>

using namespace std;

class HashTable 
{
private:
    vector<list<pair<string, vector<string>>>> buckets;
    size_t numBuckets;

public:
    HashTable(size_t buckets_count) : numBuckets(buckets_count), buckets(buckets_count) {}

    size_t hashFunction(const string& key) const
     {
        return hash<string>{}(key) % numBuckets;
    }

    void insert(const string& key, const vector<string>& data) 
    {
        size_t bucketIndex = hashFunction(key);
        buckets[bucketIndex].push_back({key, data});
    }

    vector<string> getData(const string& key) const 
    {
        size_t bucketIndex = hashFunction(key);
        for (const auto& item : buckets[bucketIndex]) 
        {
            if (item.first == key)
             {
                return item.second;
            }
        }
       
        return {};
    }

    void display() const 
    {
        for (size_t i = 0; i < numBuckets; ++i)
         {
            cout << "Bucket " << i << ": ";
            for (const auto& item : buckets[i]) 
            {
                for (const string& cell : item.second) 
                {
                    cout << cell << " ";
                }
                cout << "| ";
            }
            cout << endl;
        }
    }
};


class Table 
{
public:
    
    HashTable hashTable;
     string name;
    vector<string> columnNames;
    vector<vector<string>> data;
    Table(const string& table_name, int rows, int cols)
        : name(table_name), data(rows, vector<string>(cols)) , hashTable(100) {}

    void setColumnNames(vector<string> s) 
    {
       
        for (int i = 0; i < s.size(); i++) 
        {
            string columnName;
            
            columnName = s[i];
            columnNames.push_back(columnName);
        }
    }

    void saveToFile() const 
    {
        ofstream file(name + ".txt");

        if (file.is_open()) 
        {
            file << "Table Name: " << name << endl;

            for (const string& columnName : columnNames) 
            {
                file << " " << columnName;
            }
            file << endl;

            for (int i = 0; i < data.size(); i++) 
            {
                for (int j = 0; j < data[i].size(); j++) 
                {
                    file << data[i][j] << " ";
                }
                file << endl;
            }
            file.close();
            cout << "Table data saved to " << name << ".txt" << endl;
        } 
        else 
        {
            cout << "Unable to open file for writing." << endl;
        }
    }

    void loadFromFile() 
    {
        ifstream file(name + ".txt");

        if (file.is_open()) 
        {
            string line;

            getline(file, line);

            columnNames.clear();

            if (getline(file, line)) 
            {
                istringstream columnNamesStream(line);
                string columnName;

                while (columnNamesStream >> columnName) 
                {
                    columnNames.push_back(columnName);
                }
            }

           
            data.clear();

            
            while (getline(file, line) && !line.empty())
             {
                istringstream rowStream(line);
                vector<string> row;

                string cell;
                while (rowStream >> cell) 
                {
                    row.push_back(cell);
                }

                data.push_back(row);
                
            }

            

            file.close();

            for(int i = 0 ; i < columnNames.size(); i++)
            {
                string key = columnNames[i];
                vector<string> d;
                for(int j = 0 ; j < data.size(); j++)
                {
                    d.push_back(data[j][i]);
                }
                hashTable.insert(key,d);
            }

            cout << "Table data loaded from " << name << ".txt" << endl;
        } 
        else 
        {
            cout << "Table file not found." << endl;
        }
    }

    void insert(vector<string> s) 
    {
       
        vector<string> temp;
        for (int i = 0; i < columnNames.size(); i++) 
        {
            string x;
            x=s[i];
            temp.push_back(x);
        }

        
       // hashTable.insert(temp[0], temp);

        data.push_back(temp);
    }

    void display() const {
        cout << "Table Name: " << name << endl;
        for (const auto& x : columnNames) 
        {
            cout << x << " ";
        }
        cout << endl;
        for (int i = 0; i < data.size(); i++) 
        {
            for (int j = 0; j < data[i].size(); j++) 
            {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }
    
    vector<vector<string>> selectAll() const
     {
        return data;
    }

    vector<vector<string>> selectWhere(const string& columnName, const string& value) const 
    {
        vector<vector<string>> result;
        size_t columnIndex = findColumnIndex(columnName);

        if (columnIndex != string::npos) {
            for (const auto& row : data) {
                if (row.size() > columnIndex && row[columnIndex] == value) 
                {
                    result.push_back(row);
                }
            }
        }

        return result;
    }

    void insertAndClear(vector<vector<string>> s) {

    data.clear();

    
    for (int i = 0; i < s.size(); i++) {
        vector<string> temp;
        for(int j = 0 ; j < s[0].size(); j++){
            temp.push_back(s[i][j]);

        }
        data.push_back(temp);
    }

    
   
}

    vector<vector<string>> deleteWhere(const string& columnName, const string& value) const {
        vector<vector<string>> result;
        size_t columnIndex = findColumnIndex(columnName);

        if (columnIndex != string::npos) {
            for (const auto& row : data) {
                if (row.size() > columnIndex && row[columnIndex] != value) {
                    result.push_back(row);
                }
            }
        }

        return result;
    }



    vector<vector<string>> selectWhereGreaterThan(const string& columnName, const string& value) const 
    {
    vector<vector<string>> result;
    size_t columnIndex = findColumnIndex(columnName);

    if (columnIndex != string::npos) 
    {
        for (const auto& row : data)
         {
            if (row.size() > columnIndex)
             {
                const string& cellValue = row[columnIndex];
                bool greaterThan;

                try 
                {
                    int intValue = stoi(cellValue);
                    int compareValue = stoi(value);
                    greaterThan = (intValue > compareValue);
                } 
                catch (const invalid_argument&) 
                {
                    greaterThan = (cellValue > value);
                }

                if (greaterThan) 
                {
                    result.push_back(row);
                }
            }
        }
    }

    return result;
}


    vector<string> selectDistinct(const string& columnName) const 
    {
        vector<string> distinctValues;
        size_t columnIndex = findColumnIndex(columnName);

        if (columnIndex != string::npos)
         {
            unordered_set<string> uniqueSet;

            for (const auto& row : data) 
            {
                if (row.size() > columnIndex) 
                {
                    uniqueSet.insert(row[columnIndex]);
                }
            }

            distinctValues.assign(uniqueSet.begin(), uniqueSet.end());
        }

        return distinctValues;
    }

    size_t findColumnIndex(const string& columnName) const 
    {
        for (size_t i = 0; i < columnNames.size(); ++i) 
        {
            if (columnNames[i] == columnName) 
            {
                return i;
            }
        }
        return string::npos; 
    }

    double calculateSum(const string& columnName) const 
    {
        size_t columnIndex = findColumnIndex(columnName);

        if (columnIndex != string::npos) 
        {
            vector<double> numericColumn;

            for (const auto& row : data)
             {
                if (row.size() > columnIndex) 
                {
                   
                    double value = stod(row[columnIndex]);
                    numericColumn.push_back(value);
                }
            }

            
            double sum = 0;
            for(auto x : numericColumn)
            {
                sum+=x;
            }
            return sum;
        }

        return 0.0; 
    }

     double calculateAVG(const string& columnName) const 
     {
        size_t columnIndex = findColumnIndex(columnName);

        if (columnIndex != string::npos) 
        {
            vector<double> numericColumn;

            for (const auto& row : data) 
            {
                if (row.size() > columnIndex) 
                {
                   
                    double value = stod(row[columnIndex]);
                    numericColumn.push_back(value);
                }
            }

            
            double sum = 0;
            for(auto x : numericColumn)
            {
                sum+=x;
            }
            return sum/numericColumn.size();
        }

        return 0.0; 
     }

    

    void selectColumn(const string& columnName) const 
    {
        vector<string> result=hashTable.getData(columnName);
        
    for (const string& cell : result) 
    {
        cout << cell << " ";
    }
    cout << endl;


        return;
    }

};





class demo
{
        public:

        void newSelectcol()
        {
            string tableName, columnName;
        cout << "Enter table name: ";
        cin >> tableName;
            if (tableExistsOnDisk(tableName))
             {
            Table existingTable(tableName, 3, 5);
            existingTable.loadFromFile();
            existingTable.display();

            cout << "Enter column name to select: ";
            cin >> columnName;

            existingTable.selectColumn(columnName);
        } 
        else 
        {
            cout << "Table doesn't exist" << endl;
        }
        }


        void calculateColumnSum() 
        {
        string tableName, columnName;
        cout << "Enter table name: ";
        cin >> tableName;

        if (tableExistsOnDisk(tableName))
         {
            Table existingTable(tableName, 3, 5);
            existingTable.loadFromFile();
            existingTable.display();

            cout << "Enter column name to calculate sum: ";
            cin >> columnName;

            double sum = existingTable.calculateSum(columnName);

            if (sum != 0.0) 
            {
                cout << "Sum of values in the '" << columnName << "' column: " << sum << endl;
            } 
            else 
            {
                cout << "Column not found or does not contain numeric values." << endl;
            }
        } 
        else 
        {
            cout << "Table doesn't exist" << endl;
        }
    }



    void calculateColumnAVG() 
    {
        string tableName, columnName;
        cout << "Enter table name: ";
        cin >> tableName;

        if (tableExistsOnDisk(tableName)) 
        {
            Table existingTable(tableName, 3, 5);
            existingTable.loadFromFile();
            existingTable.display();

            cout << "Enter column name to calculate sum: ";
            cin >> columnName;

            double sum = existingTable.calculateAVG(columnName);

            if (sum != 0.0) 
            {
                cout << "Average of values in the '" << columnName << "' column: " << sum << endl;
            } 
            else 
            {
                cout << "Column not found or does not contain numeric values." << endl;
            }
        }
         else
          {
            cout << "Table doesn't exist" << endl;
        }
    }
            

            void create()
            {
                vector<string> columnNames;
                 string tableName; string cmd;
                 cout<<"Enter create command: ";
                 cin.ignore();
                getline(cin, cmd);
                 
                 
              
                 size_t posOpen = cmd.find("(");
                size_t posClose = cmd.find(")");

                if (posOpen != string::npos && posClose != string::npos && posOpen < posClose) {
        
                string columnsSubstring = cmd.substr(posOpen + 1, posClose - posOpen - 1);

      
                stringstream ss(columnsSubstring);
                string token;

       
                while (getline(ss, token, ',')) {
            
                token.erase(remove_if(token.begin(), token.end(), ::isspace), token.end());

            
            if (!token.empty())
             {
                columnNames.push_back(token);
            }
        }

        
        tableName = cmd.substr(12, posOpen - 13); 
    } 
    else 
    {
        
        cout << "Invalid CREATE TABLE command format." << endl;
    }
                

                if(tableExistsOnDisk(tableName))
                {
                    cout<<"Table exists select another name";
                }
                else
                {
                    
                    int x,y;
                   
                    x=0; y = columnNames.size();
                    Table newTable(tableName,x,y);
                    newTable.setColumnNames(columnNames);

                    newTable.saveToFile();


                }


            }

            

            void insert()
            {
                
                string cmd;
                cout<<"Enter insert into command: ";
                 cin.ignore();
                getline(cin, cmd);

   string tableName;
   vector<string> values;

    size_t posOpen = cmd.find("(");
        size_t posClose = cmd.find(")");
        if (posOpen != string::npos && posClose != string::npos && posOpen < posClose)
         {
        
        string columnsSubstring = cmd.substr(posOpen + 1, posClose - posOpen - 1);

        
        stringstream ss(columnsSubstring);
        string token;

        
        while (getline(ss, token, ',')) 
        {
            
            token.erase(remove_if(token.begin(), token.end(), ::isspace), token.end());

            
            if (!token.empty())
             {
                values.push_back(token);
            }
        }
          tableName = cmd.substr(11, posOpen - 19);

    }

    else 
    {
       
        cout << "Invalid CREATE TABLE command format." << endl;
    }
                if(tableExistsOnDisk(tableName))
                {
                    Table existingTable(tableName,3,5);
                    existingTable.loadFromFile();
                    existingTable.display();

                    HashTable hashTable(10);

                    existingTable.insert(values);

                    existingTable.saveToFile();
                    existingTable.display();

                }
                else
                {
                    cout<<"Table doesn't exist"<<endl;
                }

            }

           

    string parseTableName(const string& query) 
    {
    istringstream iss(query);
    string keyword, tableName;

    
    iss >> keyword;

   
    if (keyword == "SELECT") {
        
        iss >> keyword;

        
        iss >> keyword;

       
        iss >> tableName;
    }
     else 
     {
        
        cout << "Invalid SELECT query." << endl;
    }

    return tableName;
}

    void selectAll() 
    {
        string tableName;
       string sqlQuery ;
    cout<<"Enter select command: ";
                 
                getline(cin, sqlQuery);

    
    tableName = parseTableName(sqlQuery);
        if (tableExistsOnDisk(tableName)) 
        {
            Table existingTable(tableName, 3, 5);
            existingTable.loadFromFile();
            existingTable.display();

            vector<vector<string>> result = existingTable.selectAll();

            cout << "Selected All Rows and Columns: " << endl;
            displayResult(result);
        }
         else
          {
            cout << "Table doesn't exist" << endl;
        }
    }

   
    void selectWhere() 
    {
        string tableName, columnName, value;
        cout << "Enter table name: ";
        cin >> tableName;

        if (tableExistsOnDisk(tableName)) 
        {
            Table existingTable(tableName, 3, 5);
            existingTable.loadFromFile();
            existingTable.display();

            cout << "Enter column name and value to select: ";
            cin >> columnName >> value;

            vector<vector<string>> result = existingTable.selectWhere(columnName, value);

            cout << "Selected Rows Where " << columnName << " = " << value << ":" << endl;
            displayResult(result);
        }
         else 
         {
            cout << "Table doesn't exist" << endl;
        }
    }

    void DeleteWhere() {
        string tableName, columnName, value;
        cout << "Enter table name: ";
        cin >> tableName;

        if (tableExistsOnDisk(tableName)) {
            Table existingTable(tableName, 3, 5);
            existingTable.loadFromFile();
            existingTable.display();

            cout << "Enter column name and value to select: ";
            cin >> columnName >> value;

            vector<vector<string>> result = existingTable.deleteWhere(columnName, value);
            existingTable.insertAndClear(result);
            //existingTable.display();
            existingTable.saveToFile();
            cout << "Deleted Rows Where " << columnName << " = " << value << ":" << endl;
            displayResult(result);
        } else {
            cout << "Table doesn't exist" << endl;
        }
    }

    
    void selectDistinct() 
    {
        string tableName, columnName;
        cout << "Enter table name: ";
        cin >> tableName;

        if (tableExistsOnDisk(tableName)) 
        {
            Table existingTable(tableName, 3, 5);
            existingTable.loadFromFile();
            existingTable.display();

            cout << "Enter column name to select distinct values: ";
            cin >> columnName;

            vector<string> result = existingTable.selectDistinct(columnName);

            cout << "Distinct Values in Column " << columnName << ":" << endl;
            displayResult(result);
        } 
        else 
        {
            cout << "Table doesn't exist" << endl;
        }
    }

            bool tableExistsOnDisk(const string& table_name) 
            {
                ifstream file(table_name + ".txt");
                return file.good();
        }

       
        void selectWheregreaterthan() 
        {
        string tableName, columnName, value;
        cout << "Enter table name: ";
        cin >> tableName;

        if (tableExistsOnDisk(tableName)) 
        {
            Table existingTable(tableName, 3, 5);
            existingTable.loadFromFile();
            existingTable.display();

            cout << "Enter column name for condition: ";
            cin >> columnName;

            cout << "Enter value for condition: ";
            cin >> value;

            vector<vector<string>> selectedRows = existingTable.selectWhereGreaterThan(columnName, value);

            cout << "Selected Rows for condition: " << columnName << " = " << value << endl;
            for (const auto& row : selectedRows) 
            {
                for (const string& cell : row) 
                {
                    cout << cell << " ";
                }
                cout << endl;
            }
        } 
        else 
        {
            cout << "Table doesn't exist" << endl;
        }
    }

    private:
   
    void displayResult(const vector<vector<string>>& result) const 
    {
        for (const auto& row : result) 
        {
            for (const string& cell : row) 
            {
                cout << cell << " ";
            }
            cout << endl;
        }
    }

    
    void displayResult(const vector<string>& result) const
     {
        for (const string& value : result)
         {
            cout << value << endl;
        }
    }
};

class typecast
{
   std::vector<int> stringToInt(const std::vector<std::string>& a)
    {
    std::vector<int> result;
    
    for (const std::string& str : a) 
    {
        try 
        {
            int num = std::stoi(str);
            result.push_back(num);
        } catch (const std::invalid_argument& e) 
        {
            std::cerr << "Invalid argument: " << e.what() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Out of range: " << e.what() << std::endl;
        }
    }

    return result;
}
};

bool tableExistsOnDisk(const string& table_name) 
{
    ifstream file(table_name + ".txt");
    return file.good();
}

int main() 
{
    
    demo d;
   
   // d.newSelectcol();
   
   // d.create(); 
   //d.insert();
    //d.calculateColumnSum();
   //d.calculateColumnAVG();
    // d.selectAll();
    //d.selectDistinct();
  // d.selectWheregreaterthan();
   d.DeleteWhere();
    //d.selectWhere();
}
