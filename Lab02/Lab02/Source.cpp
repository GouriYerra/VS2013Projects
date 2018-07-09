//--------------------------------------------------------- 
//Lab 02: I/O
//Gouri Yerra
//Partner: Jimi Wilcox
//CSCI 262 - Data Structures
//This program's purpose is to show how to read values and lines from a console or a file
//--------------------------------------------------------- 

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
	/*
	string x = "";
	while (x != "exit") {
	cout << "Enter something: ";
	cin >> x;
	cout << "You entered: \"" << x << '\"' << endl;
	}
	
	string x = " ";
	while (x != "exit") {
		cout << "Enter something: ";
		getline(cin, x);
		cout << "You entered: \"" << x << '\"' << endl; 
	}*/
	
	string file_to_copy, filename_to_copy_to;

	//-----------------------------------------------------------
	// Name: getline()
	// Description: The function getline() lives in string and it takes
	// an entire line of input from the user at one time, discarding 
	// the line ending whitespace (the line ending sequence varies 
	// from system to system
	//-----------------------------------------------------------

	cout << "Hello user! Enter a file to copy: ";
	getline(cin, file_to_copy);
	cout << "Now enter the filename to copy to: ";
	getline(cin, filename_to_copy_to);

	//-----------------------------------------------------------
	// Name: ifstream and ofstream
	// Description: The ifstream class allows for input from files, 
	// and the ofstream allows for output to files.
	//-----------------------------------------------------------

	ifstream fin(file_to_copy);
	ofstream fout(filename_to_copy_to);

	while (!fin.eof()) {
		string line;
		getline(fin, line);
		fout << line << endl;
	}

	fin.close();
	fout.close();
}