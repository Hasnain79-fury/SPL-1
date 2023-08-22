#include <iostream>
#include <fstream>
#include <vector>
#include "CREATE.h"
using namespace std;



int main() {
    // Example: Creating a table
    vector<string> columns = {"I", "NAME", "ROLL"};
    createTable("students", columns);

    return 0;
}
