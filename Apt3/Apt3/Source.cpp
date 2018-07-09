#pragma once
#include <string>
#include <vector>
#include "vector.h"
#include <iostream>
#include "map.h"
#include "stack.h"

using namespace std;

string encrypt(string message);
bool is_valid(string expr, string left, string right);
int snowy_highway_length(Vector<int> &start_points, Vector<int> &end_points);

Vector<string> whos_dishonest(Vector<string> &club1, Vector<string> &club2, Vector<string> &club3) 
{
	Vector<string> notHonest;

	//--------------------------------------
	// This is for club1
	//--------------------------------------
	for (int i = 0; i < club1.size(); ++i)
	{
		string tmpM = club1[i];

		for (int j = 0; j < club2.size(); ++j)
		{
			if (tmpM.compare(club2[j]) == 0)
				if (find(notHonest.begin(), notHonest.end(), tmpM) == notHonest.end()) notHonest.push_back(tmpM);
		}

		for (int k = 0; k < club3.size(); ++k)
		{
			if (tmpM.compare(club3[k]) == 0)
				if (find(notHonest.begin(), notHonest.end(), tmpM) == notHonest.end()) notHonest.push_back(tmpM);
		}
	}

	//--------------------------------------
	// This is for club2
	//--------------------------------------
	for (int i = 0; i < club2.size(); ++i)
	{
		string tmpM = club2[i];

		for (int j = 0; j < club1.size(); ++j)
		{
			if (tmpM.compare(club1[j]) == 0)
				if (find(notHonest.begin(), notHonest.end(), tmpM) == notHonest.end()) notHonest.push_back(tmpM);
		}

		for (int k = 0; k < club3.size(); ++k)
		{
			if (tmpM.compare(club3[k]) == 0)
				if (find(notHonest.begin(), notHonest.end(), tmpM) == notHonest.end()) notHonest.push_back(tmpM);
		}
	}

	//--------------------------------------
	// This is for club3
	//--------------------------------------
	for (int i = 0; i < club3.size(); ++i)
	{
		string tmpM = club3[i];

		for (int j = 0; j < club1.size(); ++j)
		{
			if (tmpM.compare(club1[j]) == 0)
				if (find(notHonest.begin(), notHonest.end(), tmpM) == notHonest.end()) notHonest.push_back(tmpM);
		}

		for (int k = 0; k < club2.size(); ++k)
		{
			if (tmpM.compare(club2[k]) == 0)
				if (find(notHonest.begin(), notHonest.end(), tmpM) == notHonest.end()) notHonest.push_back(tmpM);
		}
	}	
	sort(notHonest.begin(), notHonest.end());
	return notHonest;
}

int main()
{
	/*Vector<string> club1 = { "Bijay", "Bijay", "Gouri" };
	Vector<string> club2 = { "Romeo", "Gouri", "Ann" };
	Vector<string> club3 = { "Romeo", "Radha", "Sony" , "Ann"};

	Vector<string> dishonest = whos_dishonest(club1, club2, club3);
	for (int i = 0; i < dishonest.size(); ++i)
		cout << dishonest[i] << endl;

	cin.get();*/

	
	/*string message = "hello";
	cout << encrypt(message);
	*/
	//cout << "check gouri" << is_valid("gouri", "", "") << endl;
	//cout << "check abcd() " << is_valid("abcd()", "(", ")") << endl;
	//cout << "check ({hello " << (bool) is_valid("({hello ", "({", ")}") << endl;
	//cout << is_valid("(])]", "([", ")]") << endl;

	Vector<int> start = { 10, 15, 25, 100 };
	Vector<int> end =   { 11, 17, 110, 120 };
	snowy_highway_length(start, end);

	cin.get();
}

string encrypt(string message)
{
	Map<char, char> cipher;
	int cipherCtr = 0;

	for (int i = 0; i < message.length(); ++i)
	{
		char c = message[i];

		if (cipher.get(c) == 0) { // the c is not in the map.. now we can add it
			cipher.put(c, 'a' + cipherCtr);
			message[i] = 'a' + cipherCtr++;
		}
		else {
			message[i] = cipher.get(c);
		}
	}
	return message;
}

bool is_valid(string expr, string left, string right) {
	Stack<char> stk;

	for (int i = 0; i < expr.length(); ++i)
	{
		char c = expr[i];
		
		if (left.find(c) != std::string::npos) {
			// this is  found.
			stk.push(c);
			continue;
		} 

		int index = right.find(c);
		if (index != std::string::npos) {  //found on right side	
			if (stk.isEmpty())
				return false;

			char tmp = stk.pop();
			if (tmp == left[index])
				continue;
			else
				return false;
		}
	}

	if (stk.size() == 0)
		return true;
	else
		return false;
}

struct Pair {
	int start;
	int end;

	Pair() { start = 0; end = 0; }
	Pair(int a, int b) { start = a; end = b; }
};

bool isPointInASegment(int point, Pair s)
{
	cout << "Checkin " << point << " is with in " << s.start << " - " << s.end << endl;
	if (point >= s.start && point <= s.end)
		return true;

	return false;
}

int snowy_highway_length(Vector<int> &start_points, Vector<int> &end_points) {

	Vector<Pair> segments;
	segments.push_back(Pair(start_points[0], end_points[0]));

	for (int i = 1; i < start_points.size(); ++i)
	{

		for (int s = 0; s < segments.size(); ++s)
		{
			if (isPointInASegment(start_points[i], segments[s]))
			{
				if (isPointInASegment(end_points[i], segments[s]))
					break;
				else {
					segments[s].end = end_points[i];
					break;
				}
			}
			else if (isPointInASegment(end_points[i], segments[s]))
			{
				segments[s].start = start_points[i];
				break;
			}
			else {
				segments.push_back(Pair(start_points[i], end_points[i]));
				break;
			}
		}
	}
	
	for (int i = 0; i < segments.size(); ++i)
		cout << "Start = " << segments[i].start << ", End = " << segments[i].end << endl;

	return 0;
}
