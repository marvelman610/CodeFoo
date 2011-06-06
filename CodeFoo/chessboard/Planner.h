#ifndef PLANNER_H
#define PLANNER_H

#include <iostream>
using namespace std;

struct Tile
{
	int row;
	int column;
};

class PlannerNode
{
private:
	Tile *tile;
	int numTiles;
	

public:
	char board[8][8];
	PlannerNode *parent;

	PlannerNode(Tile *t);
	PlannerNode(Tile *t, PlannerNode* p, int numertiles, char b[8][8]); 

	//sets variables to 0/null
	void initialize();

	//accessors
	int getRow() { return tile->row;}
	int getColumn() { return tile->column;}
	int getNumTiles() {return numTiles;}

	//mutators
	void setRow(int r) { tile->row = r;}
	void setColumn(int c) { tile->column = c;}

	void incrementNumTiles(int x);


};



#endif