//--------------------------------------------------------------
// File Name: source.cpp
// Author: Gouri Yerra
// Date: 1/24/17
// Course: CSCI 262 - Data Structures
// Assignment: Image editing program 
// Description: This program applies effects to images
//--------------------------------------------------------------

// Header files with #pragma once to guard against multiple inclusions
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "vector.h"

using namespace std;

// Global constants 
static const int DO_NOTHING = 0;
static const int GRAYSCALE = 1;
static const int FLIP_HORIZONTAL = 2;
static const int NEGATE_RED = 3;
static const int NEGATE_GREEN = 4;
static const int NEGATE_BLUE = 5;
static const int FLATTEN_RED = 6;
static const int FLATTEN_GREEN = 7;
static const int FLATTEN_BLUE = 8;
static const int EXTREME_CONTRAST = 9;
static const int FLIP_VERTICAL = 10;

static const int EFFECT_COUNT = 11;

int num_of_columns;
int num_of_rows;
int depth;
static const string MENU_STRINGS[] = 
{
	"do nothing,\n",
	"convert to grayscale,\n",
	"flip horizontally,\n",
	"negate red,\n",
	"negate green,\n",
	"negate blue,\n",
	"flatten red,\n",
	"flatten green,\n",
	"flatten blue,\n",
	"extreme contrast, and\n",
	"flip vertically\n"
};

// A class to represent a pixel, and do a 2-D grid of pixel objects.
class Colors 
{
public:
	int r = 255;
	int g = 255;
	int b = 255;
};

// Function prototypes
void get_user_selections(bool*);
void grayscale(Vector<Vector<Colors>> &image);
void flip_horizontal(Vector<Vector<Colors>> &image);
void negate_red(Vector<Vector<Colors>> &image);
void negate_green(Vector<Vector<Colors>> &image);
void negate_blue(Vector<Vector<Colors>> &image);
void flatten_red(Vector<Vector<Colors>> &image);
void flatten_green(Vector<Vector<Colors>> &image);
void flatten_blue(Vector<Vector<Colors>> &image);
void flip_vertical(Vector<Vector<Colors>> &image);
void extreme_contrast(Vector<Vector<Colors>> &image);

// MAIN
int main() 
{
	// User interaction to obtain input filename
	cout << "Portable Pixmap (PPM) Image Editor!" << endl << endl;
	cout << "Hello user! Enter name of image file: ";
	string infile;
	getline(cin, infile);

	// Open input filestream
	ifstream fin;
	fin.open(infile);
	if (fin.fail()) 
	{
		cerr << "Error opening input file '";
		cerr << infile << "', exiting!" << endl;
		return -1;
	}

	// Read magic 
	string magic;
	fin >> magic;
	if (magic != "P3") 
	{
		cerr << "Input file '" << infile;
		cerr << "' appears to not be a PPM, exiting!" << endl;
		fin.close();
		return -1;
	}

	fin >> num_of_columns;
	fin >> num_of_rows;
	fin >> depth;
	// This data structure is a Vector of Vectors of int sized to hold
	// rows x columns x 3 integers.
	// Also this section reads in columns/rows/depth header info and
	// reads all of the image data into your data structure.
	Vector< Vector<Colors> > image;
	for (int i = 0; i < num_of_rows; i++) 
	{
		Vector<Colors> read_in;
		for (int j = 0; j < num_of_columns; j++)
		{
			Colors pix_in;
			fin >> pix_in.r;
			fin >> pix_in.g;
			fin >> pix_in.b;

			read_in.push_back(pix_in);
		}
		image.push_back(read_in);
	}

	// To close input file
	fin.close();

	// This gets output filename and open output file
	string file_to_copy_to;
	cout << "Please enter a file to copy to: ";
	getline(cin, file_to_copy_to);

	// This displays menu and get user selections
	bool selections[EFFECT_COUNT];
	get_user_selections(selections);

	// This is to apply each effect selected by the user to the image.
	// Each effect is in its own function.  
	// Image is the name of the data structure holding all of your
	// image data.
	if (selections[GRAYSCALE]) grayscale(image);
	if (selections[FLIP_HORIZONTAL]) flip_horizontal(image);
	if (selections[NEGATE_RED]) negate_red(image);
	if (selections[NEGATE_GREEN]) negate_green(image);
	if (selections[NEGATE_BLUE]) negate_blue(image);
	if (selections[FLATTEN_RED]) flatten_red(image);
	if (selections[FLATTEN_GREEN]) flatten_green(image);
	if (selections[FLATTEN_BLUE]) flatten_blue(image);
	if (selections[EXTREME_CONTRAST]) extreme_contrast(image);
	if (selections[FLIP_VERTICAL]) flip_vertical(image);

	// This outputs magic, columns, rows, depth header values, then outputs 
	// all of the image data 
	ofstream fout(file_to_copy_to);

	fout << "P3\n" << num_of_columns << " " << num_of_rows << " " << "\n" << depth <<"\n";
	for (int i = 0; i < num_of_rows; i++) 
	{
		for (int j = 0; j < num_of_columns; j++) 
		{
			fout << image[i][j].r << " ";
			fout << image[i][j].g << " ";
			fout << image[i][j].b << " ";
		}
	}

	// This closes output file
	fout.close();

	return 0;
}

// This function displays a menu of effects for the user and gathers
// the user's selections.
void get_user_selections(bool* selections) 
{
	// This initializes selections
	for (int i = 0; i < EFFECT_COUNT; i++) selections[i] = false;
	cout << endl << "Here are your choices: " << endl;
	
	int columns = 80;
	for (int i = 0; i < EFFECT_COUNT; i++) 
	{
		// This approximates length of menu item assuming 2 digit numbers
		int len = MENU_STRINGS[i].length() + 6;
		columns -= len;
		if (columns < 0) 
		{
			cout << endl;
			columns = 80 - len;
		}
		cout << "[" << i << "] " << MENU_STRINGS[i] << " ";
	}
	
	// This gets user response and extracts numbers from it
	string response;
	getline(cin, response);

	// This actually allows pretty much any characters between integers
	istringstream sin(response);
	while (sin) 
	{
		while ((sin.peek() < '0' || sin.peek() > '9') && sin.peek() != EOF) sin.ignore();
		if (sin.peek() == EOF) break;
		int n;
		sin >> n;

		if (n < EFFECT_COUNT) 
		{
			selections[n] = true;
		}
		else 
		{
			cout << "Invalid selection " << n << " ignored!" << endl;
		}
	}
}

// FUNCTION DEFINITIONS
// This sets sets each pixel value to the average of the three
void grayscale(Vector<Vector<Colors>> &image) {
	for (int i = 0; i < num_of_columns; i++){
		for (int j = 0; j < num_of_rows; j++){
			int average = (image[j][i].r + image[j][i].g + image[j][i].b) / 3;
			image[j][i].r = average;
			image[j][i].g = average;
			image[j][i].b = average;
		}
	}
}

// This flips each row horizontally
void flip_horizontal(Vector<Vector<Colors>> &image) {
	for (int i= 0; i < num_of_rows; i++){
		for (int j = 0; j < num_of_columns / 2; j++){
			Colors temp = image[i][j];

			image[i][j] = image[i][num_of_columns - j - 1];
			image[i][num_of_columns - j - 1] = temp;
		}
	}
}

// This flips the columns vertically
void flip_vertical(Vector<Vector<Colors>> &image) {
	for (int i = 0; i < num_of_rows / 2; i++){
		for (int j = 0; j < num_of_columns; j++){
			Colors temp = image[i][j];

			image[i][j] = image[num_of_rows - i - 1][j];
			image[num_of_rows - i - 1][j] = temp;
		}
	}
}

// This negates the red number of each pixel
void negate_red(Vector<Vector<Colors>> &image) {
	for (int i = 0; i < num_of_columns; i++){
		for (int j = 0; j < num_of_rows; j++){
			image[j][i].r = 255 - image[j][i].r;
		}
	}
}

// This negates the green number of each pixel
void negate_green(Vector<Vector<Colors>> &image) {
	for (int i = 0; i < num_of_columns; i++){
		for (int j = 0; j < num_of_rows; j++){
			image[j][i].g = 255 - image[j][i].g;
		}
	}
}

// This negates the blue number of each pixel
void negate_blue(Vector<Vector<Colors>> &image) {
	for (int i = 0; i < num_of_columns; i++){
		for (int j = 0; j < num_of_rows; j++){
			image[j][i].b = 255 - image[j][i].b;
		}
	}
}

// This sets the red values to zero
void flatten_red(Vector<Vector<Colors>> &image) {
	for (int i = 0; i < num_of_columns; i++){
		for (int j = 0; j < num_of_rows; j++){
			image[j][i].r = 0;
		}
	}
}

// This sets the green values to zero
void flatten_green(Vector<Vector<Colors>> &image) {
	for (int i = 0; i < num_of_columns; i++){
		for (int j = 0; j < num_of_rows; j++){
			image[j][i].g = 0;
		}
	}
}

// This sets the blue values to zero
void flatten_blue(Vector<Vector<Colors>> &image) {
	for (int i = 0; i < num_of_columns; i++){
		for (int j = 0; j < num_of_rows; j++){
			image[j][i].b = 0;
		}
	}
}

// This sets each color value to either the highest
// color possible or to 0.
void extreme_contrast(Vector<Vector<Colors>> &image) {
	for (int i = 0; i < num_of_columns; i++){
		for (int j = 0; j < num_of_rows; j++){
			if (image[j][i].r > 255 / 2) image[j][i].r = 255;
			else image[j][i].r = 0;

			if (image[j][i].g > 255 / 2) image[j][i].g = 255;
			else image[j][i].g = 0;

			if (image[j][i].b > 255 / 2) image[j][i].b = 255;
			else image[j][i].b = 0;
		}
	}
}