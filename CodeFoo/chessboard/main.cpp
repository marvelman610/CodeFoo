#include "Planner.h"
#include <map>
#include <deque>
#include <vector>

void Display(PlannerNode* pNode );
void Planner();

PlannerNode* current;
std::map<Tile const*,PlannerNode*> created;
std::deque<PlannerNode*> open;
std::vector<PlannerNode const*> solution;
bool boardFull;
static int numMoves = 0;

int main(void)
{

	boardFull = false;

	Tile temp;
	temp.row = 0;
	temp.column = 0;

	//initialize start node
	PlannerNode* startNode = new PlannerNode(&temp);
	startNode->initialize();

	for(int row = 0; row < 8; row++)
	{
		
		for( int col = 0; col < 8; col++)
		{
			startNode->board[row][col] = 0;
		}
	}

	created[0] = startNode;
	
	open.push_front(created[0]);

	//run the search
	do
	{
		Planner();

	} while(!boardFull);



	return 0;

}

void Display(PlannerNode* pNode )
{
	//display chessboard
	cout<<" 1  2  3  4  5  6  7  8\n";
	for(int row = 0; row < 8; row++)
	{
		
		for( int col = 0; col < 8; col++)
		{
			cout<<'[';
			//print smiley face if knight crossed this box
			cout<<pNode->board[row][col]<<']';
		}
		cout<<endl;
	}
	cout<<" 1  2  3  4  5  6   7  8\n\n";

	cout<<pNode->getNumTiles()<<endl;

	cout<<solution.size();

}
void Planner()
{
	//////////////////////////////////////////
	//failing at breadth first search algorithm
	///////////////////////////////////////////
	static int offsets[8][2] = {
		//row   colum
		   {-2, -1}
		  , {-2, 1}

		  , {-1, 2}
		  , {1, 2}

		  ,{2, -1}
		  , {2, 1}

		  , {-1, -2}
		  , {1, -2}
		};

	

	while (!open.empty())
	{
		current = open.front();
		open.pop_front();

		
		if(current->getNumTiles() >= 64)
			boardFull=true;

		if(boardFull)
		{
			solution.push_back(current);
			const PlannerNode* temp = current->parent;
			while(true)
			{
				if( temp->parent != NULL)
				{
					solution.push_back(temp);
					temp = temp->parent;
					
				}
				else
					break;
				
			}
			solution.push_back(temp);
		}

		int x, y;
		for(int i = 0; i < 8; ++i)
		{
			x = current->getRow()+offsets[i][0];
			y = current->getColumn()+offsets[i][1];

			Tile* tile = new Tile();
			tile->row = x;
			tile->column = y;

			//set boxes on boards to display that they have been crossed over
			if(x >= 0 && y >= 0 && x < 8 && y < 8)
			{
				if(created[tile] == NULL)
				{
					switch(i)
					{
					case 0:
						current->board[x][y] = 1;
						current->board[current->getRow()-1][current->getColumn()] = 1;
						current->board[current->getRow()-2][current->getColumn()] = 1;
						break;
					case 1:
						current->board[x][y] = 1;
						current->board[current->getRow()-1][current->getColumn()] = 1;
						current->board[current->getRow()-2][current->getColumn()] = 1;
						break;
					case 2:
						current->board[x][y] = 1;
						current->board[current->getRow()][current->getColumn()+1] = 1;
						current->board[current->getRow()][current->getColumn()+2] = 1;
						break;							  
					case 3:								  
						current->board[x][y] = 1;		  
						current->board[current->getRow()][current->getColumn()+1] = 1;
						current->board[current->getRow()][current->getColumn()+2] = 1;
						break;
					case 4:
						current->board[x][y] = 1;
						current->board[current->getRow()+1][current->getColumn()] = 1;
						current->board[current->getRow()+2][current->getColumn()] = 1;
						break;								
					case 5:									
						current->board[x][y] = 1;			
						current->board[current->getRow()+1][current->getColumn()] = 1;
						current->board[current->getRow()+2][current->getColumn()] = 1;
						break;
					case 6:
						current->board[x][y] = 1;
						current->board[current->getRow()][current->getColumn()-1] = 1;
						current->board[current->getRow()][current->getColumn()-2] = 1;
						break;							  
					case 7:								  
						current->board[x][y] = 1;		  
						current->board[current->getRow()][current->getColumn()-1] = 1;
						current->board[current->getRow()][current->getColumn()-2] = 1;
						break;

					}
					current->incrementNumTiles(3);
					created[tile] = new PlannerNode(tile,current, current->getNumTiles(),current->board);
					open.push_back(created[tile]);
					
					system("cls");
					Display(current );
				}

			}
		

		}
			
	}

}