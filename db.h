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
    double *getLine();
    double *getLine2();
    double randomNumber();
    int getSize();
    int getCurrentLine();

    void setStartLine(int);
    int getStartLine();
    void setEndLine(int);
    int getEndLine();
    void reset();
    void nextLine();
    double toDouble(std::string s);


 private:
  //vector<string> *lines = new vector<string>;
  std::vector < std::string > lines;
  int n;
  int sLine;
  int eLine;
};

#endif				// DB_H
