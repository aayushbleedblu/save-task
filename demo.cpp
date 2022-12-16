
/*
  
  ERROR libc++abi.dylib: terminating with uncaught exception of type sql::SQLException
  Abort trap: 6


  STEP 1 - Connector
  Download Mysql C++ Connector for Mac OS from here https://dev.mysql.com/downloads/connector/cpp/
  Extract cppconn direcotry and mysql_connection.h, mysql_driver.h, mysql_error.h file to the root direcotry of your application
  
  STEP 2 - CREATE DYLIB file from cpp connector using the same compiler we are using to compile our code
  git clone https://github.com/mysql/mysql-connector-cpp
  git checkout 1.1
  git tag
  git checkout tags/1.1.9
  which g++
  which gcc
  cmake -DCMAKE_C_COMPILER=/opt/local/bin/gcc -DCMAKE_CXX_COMPILER=/opt/local/bin/g++ .
  make
  make install
  You should find dylib files in driver director and copy those files to the same directory where your code exists
  
  STEP 3 - RUNNING CODE 
  g++ -o demo -I/usr/local/include -I/Volumes/D/www/c++ -L. -lmysqlcppconn demo.cpp
  ./demo

*/

/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>
#include <fstream>

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h" 

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

int main(void)
{
cout << endl;


  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  sql::ResultSet *res;

  /* Create a connection */
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "root", "aayush1998");
  /* Connect to the MySQL test database */
  con->setSchema("save_schema");
  string query1 = "select ai.first_name, ai.last_name, avgs.account_number, avgs.transaction_number, avgs.merchant_description, avgs.transaction_amount "
    "from account_info ai join "
    "(select t.account_number, t.transaction_number, t.merchant_description, t.transaction_amount "
    "from transactions t "
    "join (select account_number, merchant_description, avg(transaction_amount) avg_ta "
    "from transactions "
    "group by account_number, merchant_description) x "
    "on t.account_number = x.account_number and t.merchant_description = x.merchant_description "
    "where transaction_amount > 2.5*x.avg_ta) avgs "
    "on ai.account_number = avgs.account_number"; 
  stmt = con->createStatement();
  res = stmt->executeQuery(query1);

  ofstream myfile1;
  myfile1.open ("output1.txt");
  cout << "first_name, last_name, account_number, transaction_number, merchant_description, transaction_amount" << endl;
  myfile1 << "first_name, last_name, account_number, transaction_number, merchant_description, transaction_amount" << endl;
  while (res->next()) {
    // cout << "\t... MySQL replies: ";
    /* Access column data by alias or column name */
    // cout << res->getString("_message") << endl;
    // cout << "\t... MySQL says it again: ";
    /* Access column data by numeric offset, 1 is the first column */
    for (int i=1; i<=6; i++){
      cout << res->getString(i) << ", " ;
      myfile1 << res->getString(i) << ", " ;
    }
    cout << endl;
    myfile1 << endl;
    // cout << res->getString(1) << ' ' << res->getString(2) << ' ' << res->getString(7) << endl;
  }
  cout << endl;
  myfile1.close();

  string query2 = "select ai.first_name, ai.last_name, t.account_number, t.transaction_number, ai.state as expected_location, right(t.merchant_description, 2) as actual_location "
"from account_info ai "
"join transactions t "
"on ai.account_number = t.account_number "
"where ai.state <> right(t.merchant_description, 2)"; 
  stmt = con->createStatement();
  res = stmt->executeQuery(query2);

  ofstream myfile2;
  myfile2.open ("output2.txt");
  cout << "first_name, last_name, account_number, transaction_number, expected_location, actual_location" << endl;
  myfile2 << "first_name, last_name, account_number, transaction_number, expected_location, actual_location" << endl;
  while (res->next()) {
    // cout << "\t... MySQL replies: ";
    /* Access column data by alias or column name */
    // cout << res->getString("_message") << endl;
    // cout << "\t... MySQL says it again: ";
    /* Access column data by numeric offset, 1 is the first column */
    for (int i=1; i<=6; i++){
      cout << res->getString(i) << ", " ;
      myfile2 << res->getString(i) << ", " ;
    }
    cout << endl;
    myfile2 << endl;
    // cout << res->getString(1) << ' ' << res->getString(2) << ' ' << res->getString(7) << endl;
  }
  myfile2.close();

  delete res;
  delete stmt;
  delete con;


cout << endl;

return EXIT_SUCCESS;
}


// LD_LIBRARY_PATH=/usr/local/mysql-connector-c++-8.0.31/lib64 clang++ -std=c++14 -stdlib=libc++ -o demo -I/usr/local/include -I/opt/local/include -I/usr/local/mysql-connector-c++-8.0.31/include/jdbc -L /usr/local/mysql-connector-c++-8.0.31/lib64 -lmysqlcppconn demo.cpp