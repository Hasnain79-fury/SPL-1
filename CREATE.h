#include<bits/stdc++.h>
#include<fstream>
using namespace std;
#define ll long long

struct ARRAY1 {
    string table_name;
    ll row;
    ll column;
    };

string *HEADER1;
string *FIELD1;

void column_name1 (ll x)
{
    HEADER1 = new string [x];
}

void field_value1(ll x)
{
    FIELD1 = new string [x];
}

/* CREATE TABLE table (
   ID int,
   NAME varchar,
   ROLL int ) ;
*/

void createtable(string command, string table, string TABLENAME, string str)
{
    ifstream infofile;
    infofile.open("FileInformation.txt");
    string s;
    ll total_table;
    ll total_column=0;
    infofile >> s;
    if(s=="")
        total_table=0;
    else 
        total_table=stoll(s);
    infofile.close();
    if(total_table == 0)
    {
       ofstream database;
       database.open("My_database.txt", ios::app);
       database << TABLENAME << endl << endl;

       ofstream tableshowing;
       tableshowing.open("Table_Showing.txt", ios::app);

       tableshowing << TABLENAME << '\t';

       if(str=="(")
       {
           string type;
           cin >> str >> type;
           while(str!=")")
           {
               total_column++;
               database << str << '\t' << '\t' << '\t';
               tableshowing << str << '\t' << type << '\t';
               cin >> str >> type;
           }
       }
       tableshowing << "." << endl;
       tableshowing.close();
       database << endl << endl;
       remove("FileInformation.txt");
       database.close();
       database.open("FileInformation.txt", ios::app);
       database << total_table+1 << endl;
       database<< TABLENAME <<'\t' << 0 << '\t' << total_column << endl;
       database.close();

       cout << endl << endl << "Table created successfully!" << endl << endl;
    }
     else
    {   
        
        ifstream ifile;
        ifile.open("FileInformation.txt", ios::in);
        ifile >> total_table;

        ARRAY1 tableinfo[total_table];

        //storing table name, total row, total column

        for(ll i=0; i<total_table; i++)
        {
            ifile >> tableinfo[i].table_name;
            ifile >> tableinfo[i].row;
            ifile >> tableinfo[i].column;
        }

        ifile.close();

        remove("FileInformation.txt");
        ofstream ofile;
        ofile.open("FileInformation.txt", ios::app);

        ofile << total_table+1 << '\n';

        for(ll i=0; i<total_table; i++)
        {
           
            ofile << tableinfo[i].table_name << '\t';
            ofile << tableinfo[i].row << '\t';
            ofile << tableinfo[i].column << " ";
            ofile << endl;
            
        }
        ll sum_of_rows = 0;

        for (ll i=0; i<total_table; i++)
        {
            sum_of_rows += tableinfo[i].row;
        }
        
        field_value1 (sum_of_rows);

        column_name1 (total_table);

        //storing the information from database
        ifstream iffile;

        iffile.open("My_database.txt", ios::in );

        string str1, table;

        ll index = 0;

        for(ll i=0; i<total_table; i++)
        {
            iffile >> table;
            getline(iffile, str1);
            getline(iffile, str1);
            getline(iffile, HEADER1[i]);
            getline(iffile, str1);

            ll Iindex = 0;

            while (Iindex != tableinfo[i].row)
            {
                getline(iffile, FIELD1[index]);
                index++;
                Iindex++;
            }

            if (i != total_table-1 )
            {
                getline(iffile, str1);
            }
        }
        

        iffile.close();

        remove("My_database.txt");
        
        ofstream offile;

        offile.open( "My_database.txt", ios::app );

        index = 0;

        for(ll i=0; i<total_table; i++)
        {
            offile << tableinfo[i].table_name << endl << endl;
            offile << HEADER1[i] << endl << endl;

            ll Iindex = 0;

            while (Iindex != tableinfo[i].row)
            {
                offile << FIELD1[index] << endl;
                index++;
                Iindex++;
            }
            
            if (i != total_table-1 )
            {
                offile << endl;
            }
        }
        
        ofstream tableShow;
        tableShow.open("Table_Showing.txt",ios::app);
        offile << endl << TABLENAME << endl << endl;
        tableShow << endl << TABLENAME << '\t';
        if(str=="("){
           string s1;
           cin >> str >> s1;
           
           while(str!=")")
           {
               total_column++;
               offile << str << "\t\t\t";
               tableShow << str << '\t' << s1 << '\t';
               cin >> str >> s1;
           }
            
        }
       
        tableShow << "." << endl;
        tableShow.close();
        offile << endl << endl;
        offile.close();
        ofile<< TABLENAME <<'\t' << 0 << '\t' << total_column << endl;
        ofile.close();

       cout << endl << endl << "Table created successfully!" << endl << endl;
    }
}