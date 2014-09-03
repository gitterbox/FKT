#ifndef DB_H
#define DB_H
#include <string>
#include <vector>
using namespace std;
class Database {
 public:
	Database();
	~Database();
    int read(std::string path);
    double *getLine(int aLineNumber);
    double *getLine2();
    double randomNumber();
    int getSize();
    int getCurrentLine();

 private:
  //vector<string> *lines = new vector<string>;
  std::vector < std::string > lines;
  int cnt;
};

#endif				// DB_H
