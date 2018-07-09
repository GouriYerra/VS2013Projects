//------------------------------------------------------------
// Name: Gouri Yera
// Class: CSCI 262 - Data Structures
// Assignment: Lab 05 - Classes and Objects
// Date: 2/13/17
// Purpose: Practice creating classes
//			Practice overloadin operators
//			Explore some basic object capabilities
//-----------------------------------------------------------

//Header file that includes the public methods and constructors

#pragma once
#include <ostream>
#include <string>
#include <sstream>

using namespace std;

//This class was created to model time as kept on a 24-hour clock
//It will display the hours, minutes, and seconds
class clock_time 
{
	//Friend functions
	friend bool operator ==(clock_time &t1, clock_time &t2);
	friend bool operator !=(clock_time &t1, clock_time &t2);
	friend clock_time operator+(clock_time &t1, clock_time &t2);
	friend clock_time operator-(clock_time &t1, clock_time &t2);

	public:
		int h, m, s;
		int t1, t2;
		int sec;

		int get_hour();
		int get_minute();
		int get_second();

		int test_sec(int sec);

		void set_time(int h, int m, int s);
		clock_time();
		clock_time(int h, int m, int s);
		

	private: 
		int _seconds;
};

ostream& operator<<(ostream & out, clock_time c);
string to_string(clock_time c);