#include <iostream>
#include <fstream>
#include <vector>
#include "CREATE.h"
#include"INSERT.h"
#include"SHOW.h"
using namespace std;



int main() {
   

   createTable("CREATE", "table", "thirdTable", "(");

   insertTable();


    return 0;
}
