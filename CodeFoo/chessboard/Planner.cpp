#include "Planner.h"

PlannerNode::PlannerNode(Tile *t)
{ 
	tile = t;
}
PlannerNode::PlannerNode(Tile *t, PlannerNode* p, int numertiles, char b[8][8])
{ 
	tile = t;
	parent = p; 
	numTiles = numertiles; 
}

void PlannerNode::initialize()
{
	this->parent = NULL;
	this->numTiles = 0;
	this->setColumn(0);
	this->setRow(0);
}

void PlannerNode::incrementNumTiles(int x)
{
	numTiles += x;
}