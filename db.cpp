#include "db.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

Database::Database()
{
	cout << "db alive" << endl;
}

Database::~Database()
{
	cout << "db is dead" << endl;
}

int Database::read(std::string path)
{
	if (lines.size() == 0) {

		//inputfilestream
		std::ifstream aFile;

		aFile.open(path.c_str(), ios_base::in);

		if (!aFile) {
			cerr << "Error while open:" << path << endl;
			return -1;
		}
		//vector<string> lines;
		string s;
		while (!aFile.eof()) {
			getline(aFile, s);
			lines.push_back(s);
		}

        //for (int i = 0; i < 5 && i < lines.size(); ++i)
            //cout << "##" << lines.at(i) << "##" << endl;

		cout << "lines is filled up" << endl;
		aFile.close();
		return 0;
	} else {
		return -1;
	}
}

double Database::randomNumber()
{
	return rand() / static_cast < double >(RAND_MAX);
}

double *Database::getLine2()
{
	int total = 30;
	double *vals = new double[total];

	for (int i = 0; i < total; ++i) {
		vals[i] = randomNumber();
	}
	return vals;
}

double *Database::getLine(int lineNr)
{
	double *vals = new double[35];

	string line_as_str;
	line_as_str = lines.at(lineNr);
	//line_as_string lesen bis semikolon, wert in vals legen, und nächster
	string delimiter = ";";

//    for (int i = 0; i < zeilen.size(); i++) {
	int pos = 0;
	int start = 0;
	int size = 0;
	int i = 0;
	string column, character;
	size = line_as_str.size();

	while (pos != -1) {
		character = line_as_str.substr(0, 1);

		pos = line_as_str.find(delimiter, start);
		column = line_as_str.substr(start, pos);
		if (column != "")
			vals[i] = atof(column.c_str());	//string to double!
		++i;
		//cout << "<td>" << column << "</td>";
		//save remaining charjs
		line_as_str = line_as_str.substr(pos + 1, size);
		//refresh size
		size = line_as_str.size();

	}			//while

////        }//for

	return vals;
}
