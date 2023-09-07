#include<bits/stdc++.h>
#include<fstream>
using namespace std;
#define ll long long

void showTable(string tableName)
{
    ifstream showFile;
    showFile.open("Table_Showing.txt");
    string s;
    int column=0;
    bool flag=false;
    while( showFile>>s )
    {
        if(s==tableName)
        {
            cout<<endl<<"Tablename: "<<s<<endl<<endl;
            while(showFile>>s && s!=".")
            {
                cout<<s<<'\t';
                showFile>>s;
                cout<<s<<'\t';
                cout<<endl;
                column++;
            }

            flag=true;

            break;
        }
    }

    if(flag==true)
    {
        cout<<endl<<endl<<"ShowTable operation completed!"<<endl<<endl;
    }

    else
    {
        cout<<endl<<endl<<"Can't show table."<<endl<<"Table doesn't exist."<<endl<<endl;
    }

    showFile.close();

    ifstream iFile;
    iFile.open("FileInformation.txt");

    string input;
    while(iFile>>input)
    {
        if(input==tableName)
        {
            iFile>>input;
            cout<<"Number of rows : "<<input<<endl;
            iFile>>input;
            cout<<"Number of columns : "<<input<<endl;
            break;
        }
    }

    iFile.close();
}