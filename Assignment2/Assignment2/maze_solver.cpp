//========================================================
//
//  File Name: maze_solver.cpp
//
//  Author: Christopher Painter-Wakefield 
//			Mark Baldwin
//
//  Course and Assignment: CSCI262 Assignment 2 Maze Solver
//
//  Description: This code for the maze_solver class.  
//  This class will use stack-based depth first search or 
//  queue-based breadth first search to find a solution (if
//  possible) to a simple maze.
//
//=========================================================

//These are all the header files
#pragma once
#include "maze_solver.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

// TODO: read the complete assignment instructions before beginning.  Also look
// at maze_solver.h - you will need to modify it as well. In this file you
// will need to complete three methods, and add any others as needed for your
// solution. 

// initialize()
// Find the start and goal points. Push or enqueue the start point. Set
// the boolean no_more_steps and goal_reached flags to false.
void maze_solver::initialize() {
	// TODO: write this method
	no_more_steps = false;
	goal_reached = false;

	int tmpPos = -1;
	int tmpPos2 = -1;

	// Find the start position and save it
	for (int i = 0; i < rows; i++) {
		string line = maze[i];

		tmpPos = line.find(START_CHR);
		if (tmpPos != std::string::npos) {
			startPt = Point(tmpPos, i);
			break;
		}
	}

	// Find the goal positon and save it
	for (int i = 0; i < rows; i++) {
		string line = maze[i];

		tmpPos2 = line.find(GOAL_CHR);
		if (tmpPos2 != std::string::npos) {
			goalPt = Point(tmpPos2, i);
			break;
		}
	}

	cout << "Found Start point at: " << startPt << endl;
	cout << "Found Goal point at: " << goalPt << endl;

	// Save the start pos to Stack OR Queue
	if (use_stack == true) {
		stk.push(startPt);
		cout << "Using Stack\n";
	}
	else {
		que.enqueue(startPt);
		cout << "Using Queue's\n";
	}
}

// write_maze()
// Output the (partially or totally solved) maze on the provided output stream.
void maze_solver::write_maze(ostream& out) {
	// TODO: write this method
	for (int i = 0; i < rows; i++) {
		out << maze[i] << endl;
	}
}

// step()
// Take one step towards solving the maze, setting no_more_steps and 
// goal_reached as appropriate.  This implements the essential maze search
// algorithm; 
//
// Notes:
// - Your initial point should have been pushed/enqueued in the initialize()
//   method.  You should set the no_more_steps variable to true when there
//   are no more points in the stack/queue.  The run() method will not call step() once
//   no_more_steps is true.
// - You should write an '@' over every location you have tested,
// - Make sure you follow the order given in the assignment instructions for
//   adding points to your data structure - up, right, down, left - or your
//   final maze solution won't match the required solution.  Check against the
//   sample solutions provided.

void maze_solver::step() {
	goal_reached = false;

	if (use_stack) {
		while (!stk.isEmpty()) {
			Point current_point = stk.pop();
			// cout << "current point poped = " << current_point << endl;

			Vector<Point> tests = getTestPoints(current_point);
			for (int i = 0; i < tests.size(); ++i) {
				Point test_point = tests[i];
				
				if (isPointInsideMaze(test_point)) {					
					char c = getMazeCharAtPoint(test_point);
					if (c == GOAL_CHR) {
						no_more_steps = true;
						goal_reached = true;
						return;
					}
					else if (c == UNEXPLORED) {
						maze[test_point.getY()][test_point.getX()] = VISITED;
						stk.push(test_point);
					}
				}
			} 

			cout << endl;
			write_maze(cout);
			cout << endl;
			pause();
		}

		if (stk.isEmpty()) {
			no_more_steps = true;
		}
	}
	else {
		// Use Queue
	}
}

char maze_solver::getMazeCharAtPoint(Point pt)
{
	return maze[pt.getY()][pt.getX()];
}

bool maze_solver::isPointInsideMaze(Point testPoint)
{
	if (testPoint.getX() < 0 || testPoint.getX() > columns) 
		return false;
	
	if (testPoint.getY() < 0 || testPoint.getY() > rows)
		return false;

	return true;
}

// TODO: add helper methods as needed
Vector<Point> maze_solver::getTestPoints(Point curPoint)
{
	Vector<Point> points;
	
	// Top Row points
	points.add(Point(curPoint.getX()-1, curPoint.getY()-1));
	points.add(Point(curPoint.getX(), curPoint.getY()-1));
	points.add(Point(curPoint.getX()+1, curPoint.getY()-1));

	// Right side points
	points.add(Point(curPoint.getX() + 1, curPoint.getY()));
	points.add(Point(curPoint.getX() + 1, curPoint.getY()+1));

	// Bottom side points
	points.add(Point(curPoint.getX(), curPoint.getY() + 1));
	points.add(Point(curPoint.getX() - 1, curPoint.getY()+1));

	// Leftside point
	points.add(Point(curPoint.getX()-1, curPoint.getY()));

	//for (int i = 0; i < points.size(); ++ i)
	//	cout << points[i] << 't';
	//cout << endl;

	return points;
}


/***************************************************************************
    You should not need to modify code below this point.  Touch at your own
    risk!
****************************************************************************/

//------------------------------------------------------------------------
// Name:  maze_solver::maze_solver()
//
// Description: Default class constructor
//
// Arguments: 
//	string - file to be loaded
//	bool - Use a stack if true
//	bool - pause output
//
// Modifies: initializes class data
// 
// Returns: none
//
//--------------------------------------------------------------------
// Here's the constructor code.  You should not need to modify this, but you
// can if you want.  Right now it takes care of reading in the maze for you.
// The maze is stored as a Vector<string>, but you can change that if you wish.
maze_solver::maze_solver(string infile, bool use_stak, bool pause) {
	use_stack = use_stak;
	do_pause = pause;

	// parse out maze name for later use in creating output file name
	int pos = infile.find(".");
	if (pos == string::npos) {
		maze_name = infile;
	} else {
		maze_name = infile.substr(0, pos);
	}

	// open input file and read in maze
	ifstream fin(infile);
	if (!fin) {
		cerr << "Error opening input file \"" << infile << "\"; exiting." << endl;
		cin.get() ;
		exit(1);
	}

	fin >> rows >> columns;

	string row;
	getline(fin, row);
	for (int i = 0; i < rows; i++) {
		getline(fin, row);
		maze.add(row);
	}
	
	fin.close();
}

//------------------------------------------------------------------------
// Name:  maze_solver::run()
//
// Description: Drives the solution forward.
// While more steps are possible, run repeatedly calls step, then write_maze
// (on cout), then pause.Once there are no more steps, it prints a success /
// failure message to the user and writes the final maze to a solution file.
//
// Arguments: none
// 
// Returns: none
//
//--------------------------------------------------------------------
void maze_solver::run() {
	cout << "Solving maze '" << maze_name << "'." << endl;
	cout << "Initial maze: " << endl << endl;
	write_maze(cout);
	cout << endl;
	pause();

	// main loop
	while (!no_more_steps) {
		step();
		cout << endl;
		write_maze(cout);
		cout << endl;
		pause();
	}

	// final output to user
	cout << "Finished: ";
	if (goal_reached) {
		cout << "goal reached!" << endl;
	} else {
		cout << "no solution possible!" << endl;
	}

	// save solution file
	string outfile;
	if (use_stack) outfile = maze_name + "-stack-solution.txt";
	else outfile = maze_name + "-queue-solution.txt";
	
	ofstream fout(outfile);
	if (!fout) {
		cerr << "Could not open file \"" << outfile << "\" for writing." << endl;
		cerr << "Solution file could not be saved!" << endl;
		cin.get();
	}
	else {
		write_maze(fout);
		fout.close();
	}
	cin.get();
}  // end run

//------------------------------------------------------------------------
// Name:  maze_solver::pause()
//
// Description: If do_pause is set, pauses the output
//
// Arguments: none
// 
// Returns: none
//
//--------------------------------------------------------------------
void maze_solver::pause() {
	if (!do_pause) return;
	string foo;
	cout << "Hit Enter to continue...";
	getline(cin, foo);
} // end pause