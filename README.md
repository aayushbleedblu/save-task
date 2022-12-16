Task for Save

To run the code enter the following command:

```
$ LD_LIBRARY_PATH=/usr/local/mysql-connector-c++-8.0.31/lib64 clang++ -std=c++14 -stdlib=libc++ -o demo -I/usr/local/include -I/opt/local/include -I/usr/local/mysql-connector-c++-8.0.31/include/jdbc -L /usr/local/mysql-connector-c++-8.0.31/lib64 -lmysqlcppconn demo.cpp
```
