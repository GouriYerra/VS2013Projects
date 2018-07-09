//------------------------------------------------------------------------
// File Name: Source.cpp
// Name: Gouri Yerra
// Course: CSCI 262 - Data Structures
// Assignment: Lab 04
// Purpose: Practice with Sets and Maps
//          Learn how to time running programs
//          Do some basic performance comparisons on data structures
//------------------------------------------------------------------------

#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "vector.h"
#include "map.h"

using namespace std;

int main() {
	Map<int, Vector<string>> length_words;

	//length_words[1] = { "a", "i" };
	//length_words[2] = { "be", "my", "of", "to" };
	//length_words[3] = { "for", "ate", "bar", "may", "sit", "coo" };
	//length_words[4] = { "four", "date", "bard", "leaf", "seat", "cool" };
	ifstream fin("dictionary.txt");
	
	while (!fin.eof()) {
		string word;
		getline(fin, word);
		length_words[word.length()].add(word);
	}
	
	fin.close();

	int letters = 0;
	while (true) {
		cout << endl << "What length of word do you want? ";
		cin >> letters;

		if (letters == 0) break;

		if (length_words.containsKey(letters) == 0) {
			cout << "We do not have any words with this length. " << endl;
			continue;
		}

		cout << "Here's a word: ";
		cout << length_words[letters][rand() % length_words[letters].size()];
		cout << endl;
	}

	system("pause");
	return 0;
}