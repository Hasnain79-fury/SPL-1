#include<bits/stdc++.h>
#include<fstream>
using namespace std;
#define ll long long

ll flag = 0;
struct ARRAY {
    string table_name;
    ll row;
    ll column;
    };

string *HEADER;
string *FIELD;

void column_name (ll x)
{
    HEADER = new string [x];
}

void field_value(ll x)
{
    FIELD = new string [x];
}

/* INSERT INTO table_name
   values ( 1 , Tash , 1223 ) ;
*/
void insert_table ()
{
    string into, tablename, value, str;

    // input into table_name values (
    cin >> into;
    cin >> tablename;
    cin >> value;
    cin >> str;

    // store table name, total row, total column from file
    // first need to store total table no
    ifstream ifile;

    ifile.open("FileInformation.txt", ios::in);
    string tablee;
    ll total_table;
    ifile >> tablee;
    if(tablee=="")
        total_table=0;
    else
        total_table=stoll(tablee);

    // close the file
    ifile.close();

    //if there is no table then show this message
    if ( total_table == 0)
    {
        cout << " Can't insert the values as there is no table. First create a table.\n";
    }

    else
    {
        ifstream ifile;

        ifile.open("FileInformation.txt", ios::in);

        ifile >> total_table;

        ARRAY tableinfo[total_table];

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

        ofile << total_table << '\n';

        for(ll i=0; i<total_table; i++)
        {
            if(tableinfo[i].table_name == tablename)
            {
                ofile << tableinfo[i].table_name << " ";
                ofile << tableinfo[i].row + 1 << " ";
                ofile << tableinfo[i].column << " ";
                ofile << endl;

            }
            else
            {
                ofile << tableinfo[i].table_name << " ";
                ofile << tableinfo[i].row << " ";
                ofile << tableinfo[i].column << " ";
                ofile << endl;
            }
        }

        ofile.close();

        ll sum_of_rows = 0;

        for (ll i=0; i<total_table; i++)
        {
            sum_of_rows += tableinfo[i].row;
        }

        field_value (sum_of_rows);

        column_name (total_table);

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
            getline(iffile, HEADER[i]);
            getline(iffile, str1);

            ll Iindex = 0;

            while (Iindex != tableinfo[i].row)
            {
                getline(iffile, FIELD[index]);
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
            offile << HEADER[i] << endl << endl;

            ll Iindex = 0;

            while (Iindex != tableinfo[i].row)
            {
                offile << FIELD[index] << endl;
                index++;
                Iindex++;
            }

            if ( tableinfo[i].table_name == tablename )
            {   
                flag=1;
               if(str=="("){
                    while(1)
                        {
                            string comma;

                            cin >> str >> comma;

                            if(comma!=")")
                            {
                                offile << str << "\t" << "\t" << "\t";
                            }
                            else
                            {
                               string ss;
                               cin >> ss;
                               offile << str << "\t" << "\t" << "\t";
                               break;
                            }
                        }
                            offile << endl;
               }
            }
            
            if (i != total_table-1 )
            {
                offile << endl;
            }
        }

        offile.close();
        if(flag)
        {
            cout << "Row inserted in " << tablename <<" successfully!" << endl << endl;
        }
        else
        {
           cout << "There is no such table." << endl << endl; 
        }

    }

}