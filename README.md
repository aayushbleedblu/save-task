<h1>Task for Save</h1>

To run the code enter the following command:

```
$ LD_LIBRARY_PATH=/usr/local/mysql-connector-c++-8.0.31/lib64 clang++ -std=c++14 -stdlib=libc++ -o demo -I/usr/local/include -I/opt/local/include -I/usr/local/mysql-connector-c++-8.0.31/include/jdbc -L /usr/local/mysql-connector-c++-8.0.31/lib64 -lmysqlcppconn demo.cpp
```

This will create two files - output1.txt and output2.txt. 
It will also print the results on the console.

The github repo contains the output files generated. 
