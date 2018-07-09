//========================================================
//
//  File Name:   maze_solver.h
//
//  Author: Christopher Painter-Wakefield 
//			Mark Baldwin
//
//  Course and Assignment:   CSCI262 Assignment 2 Maze Solver
//
//  Description:  Header for the maze_solver object
//
//=========================================================

#ifndef _MAZE_SOLVER_H
#define _MAZE_SOLVER_H

#include <iostream>

// The provided code uses a Vector<string> to store the maze.
// You can change this if you wish.
#include "vector.h"

// TODO: add additional includes here for the data structures you use
#include "stack.h"
#include "queue.h"

// Here is a Stanford library object that might make things a lot easier.   
#include "point.h"

using namespace std;

// TODO: make sure you read all of the assignment instructions before you
// begin.  You need to modify/create the following methods of this class:
//    initialize()
//    step() 
//    write_maze()
// You will also need to add instance variables for your stack and queue 
// objects.  You may also add other instance variables or methods as needed 
// to effectively complete the task.

//----------------------------------------------------------------------
//
// Object maze_solver
//
// Description: Class to hold and manipulate a maze
//
//
//----------------------------------------------------------------------
class maze_solver {
public:
	// constructor
	maze_solver(string infile, bool use_stak, bool pause=false);

	// public methods
	void initialize();
	void run();
	// TODO: your own public methods or variables here?

private:	
	void step();
	void write_maze(ostream& out);
	void pause();
	
	// instance variables
	string maze_name;
	bool use_stack;
	bool do_pause;

	int rows, columns;
	Vector<string> maze;

	bool no_more_steps;
	bool goal_reached;
	// TODO: your own private methods or variables here?
	Stack<Point> stk;
	Queue<Point> que;
	Point startPt, goalPt;

	static const char START_CHR = 'o';
	static const char GOAL_CHR = '*';
	static const char VISITED = '@';
	static const char WALL = '#';
	static const char UNEXPLORED = '.';

	Vector<Point> getTestPoints(Point curPoint);
	bool isPointInsideMaze(Point testPoint);
	char getMazeCharAtPoint(Point pt);
};

#endif
