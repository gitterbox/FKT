#include "db.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <QRegExpValidator>
#include <QDebug>

using namespace std;

Database::Database()
{
	//default values
	setStartLine(1);
  //Todo: set Endline automatically           to lines.size
    setEndLine(360);

	cout << "db is alive" << endl;
}

Database::~Database()
{
	cout << "db is dead" << endl;
}

/*  Reads Values from file
 * 	file has currently 360 lines
 *  the values of a line are separated with semicolons
 *  (1-360) or (1-720)
 * ---
 *  returns  0 ok
 *  returns -1 fail
 */
int Database::read(std::string path)
{
    //Todo: load recent file  JWGEC++ S. 365
	//inputfilestream
	std::ifstream aFile;

	aFile.open(path.c_str(), ios_base::in);

	if (!aFile) {
		cerr << "Error while open:" << path << endl;
		return -1;
	}
	//vector<string> lines;
	string s;

	if (lines.size() != 0) {
		cout << "lines is allready filled .. cleaning all data " <<
		    endl;
		lines.clear();
		reset();
	}
	//s (line) starts with 3 or 2 or 1 digit(s)
	QRegExp rx("^[0-9]{1,3}.*");
	QRegExpValidator v(rx, 0);
	QString ss;
	int pos = 0;
	QValidator::State line;

	while (!aFile.eof()) {
		getline(aFile, s);
		ss = QString::fromStdString(s);
		line = v.validate(ss, pos);
		if (line == QValidator::Acceptable)
			lines.push_back(s);
	}

	//Debug
	//for (int i = 0; i < 5 && i < lines.size(); ++i)
	//cout << "##" << lines.at(i) << "##" << endl;

	cout << "lines is filled up" << endl;
	aFile.close();

	// naive check ;-)
	if (lines.size() > 0) {
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

int Database::getSize()
{
	return lines.size();
}

/*
 * returns the current line number
 */
int Database::getCurrentLine()
{
	return n;
}

/*
 * Reads a line
 * first value of line is degree
 * ---
 * n points to the current position in lines
 * returns a ptr to a line of values
 */
double *Database::getLine()
{
    //Todo: amount of double
	double *vals = new double[35];
	string line_as_str;
	// vec|deg
	// 0  | 1°;;..
	// 1  | 2°;;
	line_as_str = lines.at(n - 1);

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

	return vals;

}

void Database::nextLine()
{
	n++;
}

void Database::setStartLine(int aLine)
{
	sLine = aLine;
	n = sLine;
}

int Database::getStartLine()
{
	return sLine;
}

void Database::setEndLine(int aLine)
{
	eLine = aLine;
}

int Database::getEndLine()
{
	return eLine;
}

void Database::reset()
{
	//reset n to given startLine
	n = sLine;
}
