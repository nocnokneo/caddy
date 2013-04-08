// RoboAIDoc.cpp : implementation of the CRoboAIDoc class
//

#include "stdafx.h"
#include "RoboAI.h"

#include "RoboAIDoc.h"
#include "permutation.h"

// for file input
#include <iostream>
#include <fstream>
#include <iomanip>

// for absolute value
#include <math.h>

// for random numbers
#include <ctime>
#include <cstdlib>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRoboAIDoc ====== MFC DOC CLASS EXTENSION =====================

IMPLEMENT_DYNCREATE(CRoboAIDoc, CDocument)
BEGIN_MESSAGE_MAP(CRoboAIDoc, CDocument)
END_MESSAGE_MAP()

// CRoboAIDoc construction/destruction
CRoboAIDoc::CRoboAIDoc()
{
	debugStr =  "Welcome, press:\r\n";
	debugStr += "  spacebar to step through maze.\r\n";
	debugStr += "  1-5 to select a pre-selected test case.\r\n";
	debugStr += "  r to select a random test case.\r\n";
	debugStr += "  t to select the last random test case.\r\n";
	debugStr += "  a to run test driver with all cases.\r\n";
	debugStr += "  s to run test driver with some cases.\r\n";


	// Randomize with seed = time in seconds since the epoch
	std::srand((unsigned int)time(0));
	rand_test_case = 1;

	// init bot's data using pre-selected random goals
	projectedPathHead = NULL;
	initAllBotData(FIRST_RAND_GOALS);
}

CRoboAIDoc::~CRoboAIDoc()
{

}

BOOL CRoboAIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	return TRUE;
}

// CRoboAIDoc serialization
void CRoboAIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

// CRoboAIDoc diagnostics
#ifdef _DEBUG
void CRoboAIDoc::AssertValid() const
{
	CDocument::AssertValid();
}
void CRoboAIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

//
// CRoboAIDoc ====== TEST CODE ===================================
//
void CRoboAIDoc::randomlyReset(char* listFileName)
{
	struct Coord goal_coords[NUM_RANDOM_GOALS];
	int numberOfTests;

	// get number of test cases
	std::ifstream list(listFileName);
	if( !list.is_open() )
	{
		debugStr += "Error opening input file\r\n";
		return;
	}
	list >> numberOfTests;
	list.close();

	// get and reset with random ball placement
	rand_test_case = random(1,numberOfTests);
	getTestCoords(rand_test_case,"test_list.txt", goal_coords);
	initAllBotData(goal_coords);
}

/* Generates a random number between min and max.
 *  pre: numbers have been randomized
 *       min and max are positive integers
 * post: a random integer is returned
 */
int CRoboAIDoc::random(int min, int max)
{
	return min + rand()%(max);
}

void CRoboAIDoc::getTestCoords(int testNum, char* listFileName, struct Coord goal_coords[NUM_RANDOM_GOALS])
{
	int numberOfTests;
	int count;
	int bestDistance;
	std::ifstream list(listFileName);
	if( !list.is_open() )
	{
		debugStr += "Error opening ";
		debugStr += listFileName;
		debugStr += "\r\n";
		return;
	}

	list >> numberOfTests;
	if( testNum < 1 || testNum > numberOfTests )
	{
		debugStr += "Invalid test number\r\n";
		return;
	}

	CString temp;
	temp.Format("%d", testNum);
	debugStr += "Test Case: ";
	debugStr += temp;
	debugStr += "\r\n";

	count = 1;
	while(count <= testNum)
	{
		list >> bestDistance;
		list >> goal_coords[0].row;
		list >> goal_coords[0].col;
		list >> goal_coords[1].row;
		list >> goal_coords[1].col;
		list >> goal_coords[2].row;
		list >> goal_coords[2].col;
		count++;
	}
	list.close();
}

// Tests all cases specified in list file and writes results in result file
// assumes NUM_RANDOM_GOALS = 3
void CRoboAIDoc::testAll(const char* listFileName, const char* resultFileName)
{
	int numberOfTests;
	int testNum;
	int bestDistance;
	int moveCount;
	
	bool atStopCoord;

	int timesAtStop = 0;
	int timesAllGoals = 0;
	int timesSuccede = 0;
	
	Coord goal_coords[NUM_RANDOM_GOALS];
	std::ofstream rslt(resultFileName);
	std::ifstream list(listFileName);
	
	if ( !list.is_open() )
	{
		debugStr += "Error opening input file\r\n";
		return;
	}
	
	debugStr += "Running tests in ";
	debugStr += listFileName;
	debugStr += "  ...\r\n";

	list >> numberOfTests;

	rslt << "Key:    TEST = test number" << std::endl
	     << "           F = finish run at stop coords" << std::endl
	     << "           G = number of goals reached" << std::endl
		 << "           B = best case distance was traveled " << std::endl
		 << "        DIST = distance traveled" << std::endl
		 << "        BEST = best case distance" << std::endl
		 << "  PLACEMENTS = where balls were placed" << std::endl << std::endl
		 << "(see end of file for summary)" << std::endl << std::endl
	     << " TEST  F  G  B  DIST  BEST  PLACEMENTS" << std::endl;

	testNum = 1;
	while(testNum <= numberOfTests)
	{
		// Progress bar? HERE.

		// Get test data
		list >> bestDistance;
		list >> goal_coords[0].row;
		list >> goal_coords[0].col;
		list >> goal_coords[1].row;
		list >> goal_coords[1].col;
		list >> goal_coords[2].row;
		list >> goal_coords[2].col;

		// write test number
		rslt << std::setw(5) << testNum;


		// Run test with goal coords from test list
		initAllBotData(goal_coords);
		moveCount = 0;
		goalsReached;
		while( makeNextMove() && moveCount < MAX_MOVES )
		{
			moveCount++;
		}

		// write and count if bot finishes at stop coords
		atStopCoord = botCoord.row == BOT_STOP_COORD.row && botCoord.col == BOT_STOP_COORD.col;
		if( atStopCoord )
		{
			rslt << "  Y";
			timesAtStop++;
		}
		else
			rslt << "  N";
		
		// write goals reached and count times all goals reached
		rslt << std::setw(3) << goalsReached;
		if( goalsReached == GOALS_IN_ARENA )
			timesAllGoals++;

		if( atStopCoord && goalsReached == GOALS_IN_ARENA )
			timesSuccede++;


		// write dummy values for future tests
		rslt << "  -";
		
		// write distance traveled
		rslt << std::setw(6) << distanceTrav;

		// echo input data in prettier format
		rslt << std::setw(6) << bestDistance << "  "
		     << "{("  << std::setw(2) << goal_coords[0].row
		     << ","   << std::setw(2) << goal_coords[0].col
		     << "),(" << std::setw(2) << goal_coords[1].row
			 << ","   << std::setw(2) << goal_coords[1].col
			 << "),(" << std::setw(2) << goal_coords[2].row
			 << ","   << std::setw(2) << goal_coords[2].col
			 << ")}"  << std::endl;

		/* extra info
		rslt << "    Reached " << goalsReached << ",   "
		     << std::setw(3) << moveCount << " moves" << std::endl;
		*/

		testNum++;
	}

	rslt << std::endl << "SUMMARY:" << std::endl
	     << std::setw(6) << timesAtStop << " finishes at stop" << std::endl
	     << std::setw(6) << timesAllGoals << " times reached all goals" << std::endl
		 << std::setw(6) << timesSuccede << " successes" << std::endl;


	list.close();
	rslt.close();

	debugStr += "See ";
	debugStr += resultFileName;
	debugStr += " for results.\r\n";
}

//
// CRoboAIDoc ====== INITIALIZATION ==============================
//
// Re-initilizes all of bot's data for constructor and reset by GUI
void CRoboAIDoc::initAllBotData(const struct Coord rand_goal_coords[NUM_RANDOM_GOALS])
{
	botCoord = BOT_START_COORD;
	botDirection = LEFT;
	goalsReached = 0;
	distanceTrav = 0;

	// record coordinates and number of goals already known
	goalsFound = NUM_FIXED_GOALS;
	for(int i = 0; i < NUM_FIXED_GOALS; i++)
	{
		foundGoalCoords[i] = FIXED_GOAL_COORDS[i];
	}

	// record random goals, if bot is to be told
	if( OMNISCIENT )
	{
		goalsFound = GOALS_IN_ARENA;
		for(int i = 0; i < NUM_RANDOM_GOALS; i++)
		{
			foundGoalCoords[i + NUM_FIXED_GOALS] = rand_goal_coords[i];
		}
	}

	initializeTrack(rand_goal_coords);
	check();
	updateProjectedPath();
}

// Sets the initial values of the trackAr array
void CRoboAIDoc::initializeTrack(const struct Coord rand_goal_coords[NUM_RANDOM_GOALS])
{
	int row = 0;
	int col = 0;

	//initialize border -> true means its a wall block
	// also initialize the rest of the struct to false
	for(row = 0; row < ROWS; row++)
	{
		for(col = 0; col < COLS; col++)
		{
			trackAr[row][col].containsGoal = false;
			trackAr[row][col].beenChecked = false;
			trackAr[row][col].isNode = false;
			
			if(row == 0 || row == ROWS - 1)
				trackAr[row][col].isWall = true;
			else if(col == 0 || col == COLS - 1)
				trackAr[row][col].isWall = true;
			else
				trackAr[row][col].isWall = false;
		}
	}

	// check cell bot is on
	trackAr[BOT_START_COORD.row][BOT_START_COORD.col].beenChecked = true;

	// place random and fixed goals
	for(int i = 0; i < NUM_RANDOM_GOALS; i++)
	{
		trackAr[rand_goal_coords[i].row][rand_goal_coords[i].col].containsGoal = true;
		if( OMNISCIENT )
			trackAr[rand_goal_coords[i].row][rand_goal_coords[i].col].beenChecked = true;
	}
	for(int i = 0; i < NUM_FIXED_GOALS; i++)
	{
		trackAr[FIXED_GOAL_COORDS[i].row][FIXED_GOAL_COORDS[i].col].containsGoal = true;
		trackAr[FIXED_GOAL_COORDS[i].row][FIXED_GOAL_COORDS[i].col].beenChecked = true;
	}

	createRemainingWalls();
	createNodes();
}

// Helps InitializeTrack by setting rest of the wall blocks, (assumes border is already set to wall)
void CRoboAIDoc::createRemainingWalls()
{
	// trackAr[row][col]
	trackAr[1][7].isWall = true;
	trackAr[1][8].isWall = true;
	trackAr[2][2].isWall = true;
	trackAr[2][4].isWall = true;
	trackAr[2][5].isWall = true;
	trackAr[2][8].isWall = true;
	trackAr[3][2].isWall = true;
	trackAr[3][3].isWall = true;
	trackAr[3][5].isWall = true;
	trackAr[3][6].isWall = true;
	trackAr[4][2].isWall = true;
	trackAr[4][3].isWall = true;
	trackAr[4][4].isWall = true;
	trackAr[4][6].isWall = true;
	trackAr[4][7].isWall = true;
	trackAr[6][2].isWall = true;
	trackAr[6][3].isWall = true;
	trackAr[6][5].isWall = true;
	trackAr[6][7].isWall = true;
	trackAr[7][2].isWall = true;
	trackAr[7][3].isWall = true;
	trackAr[7][5].isWall = true;
	trackAr[7][7].isWall = true;
	trackAr[8][7].isWall = true;
	trackAr[9][2].isWall = true;
	trackAr[9][4].isWall = true;
	trackAr[9][5].isWall = true;
	trackAr[10][2].isWall = true;
	trackAr[10][7].isWall = true;
	trackAr[11][2].isWall = true;
	trackAr[11][3].isWall = true;
	trackAr[11][4].isWall = true;
	trackAr[11][5].isWall = true;
	trackAr[11][6].isWall = true;
	trackAr[11][7].isWall = true;
	trackAr[12][7].isWall = true;
}

// once the track walls have been placed, create nodes should be called to proccess the
// track and set the node data member.  The node data member is private, and must be
// set using the makeNode func.
void CRoboAIDoc::createNodes()
{
	// trackAr[row][col]    set nodes	
	//intersection nodes
	trackAr[1][1].isNode = true;
	trackAr[1][2].isNode = true;
	trackAr[1][6].isNode = true;
	trackAr[2][6].isNode = true;
	trackAr[2][7].isNode = true;
	trackAr[3][7].isNode = true;
	trackAr[3][8].isNode = true;
	trackAr[5][1].isNode = true;
	trackAr[5][3].isNode = true;
	trackAr[5][4].isNode = true;
	trackAr[5][6].isNode = true;
	trackAr[5][8].isNode = true;
	trackAr[8][1].isNode = true;
	trackAr[8][3].isNode = true;
	trackAr[8][4].isNode = true;
	trackAr[8][6].isNode = true;
	trackAr[9][6].isNode = true;
	trackAr[9][8].isNode = true;
	trackAr[10][3].isNode = true;
	trackAr[10][6].isNode = true;
	trackAr[12][1].isNode = true;
	trackAr[12][6].isNode = true;
	trackAr[12][8].isNode = true;

	//ball nodes
	trackAr[10][1].isNode = true;
	trackAr[10][1].mayContainGoal = true;
	trackAr[10][5].isNode = true;
	trackAr[10][5].mayContainGoal = true;
	trackAr[9][7].isNode = true;
	trackAr[9][7].mayContainGoal = true;
	trackAr[9][3].isNode = true;
	trackAr[9][3].mayContainGoal = true;
	trackAr[8][2].isNode = true;
	trackAr[8][2].mayContainGoal = true;
	trackAr[8][5].isNode = true;
	trackAr[8][5].mayContainGoal = true;
	trackAr[8][8].isNode = true;
	trackAr[8][8].mayContainGoal = true;
	trackAr[7][6].isNode = true;
	trackAr[7][6].mayContainGoal = true;
	trackAr[7][1].isNode = true;
	trackAr[7][1].mayContainGoal = true;
	trackAr[6][4].isNode = true;
	trackAr[6][4].mayContainGoal = true;
	trackAr[6][8].isNode = true;
	trackAr[6][8].mayContainGoal = true;
	trackAr[5][7].isNode = true;
	trackAr[5][7].mayContainGoal = true;
	trackAr[5][2].isNode = true;
	trackAr[5][2].mayContainGoal = true;
	trackAr[4][1].isNode = true;
	trackAr[4][1].mayContainGoal = true;
	trackAr[4][8].isNode = true;
	trackAr[4][8].mayContainGoal = true;
	trackAr[2][1].isNode = true;
	trackAr[2][1].mayContainGoal = true;
	trackAr[1][5].isNode = true;
	trackAr[1][5].mayContainGoal = true;

	//diagonal ball nodes
	trackAr[2][3].isNode = true;
	trackAr[2][3].mayContainGoal = true;
	trackAr[4][5].isNode = true;
	trackAr[4][5].mayContainGoal = true;
}

//
// CRoboAIDoc ====== BOT'S ACTIONS ===============================
//
// Moves bot's position in given direction, until a node is reached.
bool CRoboAIDoc::move(DIRECTION dir)
{
	bool moveSuccess = false;
	botDirection = dir;
	switch(dir)
	{
		case(LEFT):
			moveSuccess = move(0,-1);        // move left
			break;
		case(RIGHT):
			moveSuccess = move(0,1);         // move right
			break;
		case(DOWN):
			if( isDiagonal(botCoord) && botCoord.row != 5 )
				moveSuccess = move(1,1);     // move down-and-right
			else
				moveSuccess = move(1,0);     // move down
			break;
		
		case(UP):
			if( isDiagonal(botCoord) && botCoord.row != 1 )
				moveSuccess = move(-1,-1);   // move up-and-left
			else
				moveSuccess = move(-1,0);    // move up
			break;
	}
	return moveSuccess;
}
// overloaded helper to new move function
bool CRoboAIDoc::move(int dRow, int dCol)
{
	if(trackAr[botCoord.row+dRow][botCoord.col+dCol].isWall)
		return false;

	// move, while node is not reached
	do
	{
		distanceTrav++;
		botCoord.row += dRow;
		botCoord.col += dCol;
		if(trackAr[botCoord.row][botCoord.col].containsGoal)
		{
			trackAr[botCoord.row][botCoord.col].containsGoal = false;
			removeCoord(botCoord, foundGoalCoords, goalsFound-goalsReached);
			goalsReached++;
			
		}
	}while(!trackAr[botCoord.row][botCoord.col].isNode);
	
	check();

	return true;
}

// Checks all cells in view from bot's position.
void CRoboAIDoc::check()
{
	// look in all four directions
	look(0,-1);
	look(0,1);
	look(1,0);
	look(-1,0);

	// IF in either cell w/ diagonal, look in diagonal direction
	if( isDiagonal(botCoord) )
	{
		look(1,1);
		look(-1,-1);
	}
}

// Changes cells to checked status in given direction from bot's position.
void CRoboAIDoc::look(int dRow, int dCol)
{
	Coord coord = botCoord;

	while(!trackAr[coord.row][coord.col].isWall)
	{
		trackAr[coord.row][coord.col].beenChecked = true;
		trackAr[coord.row][coord.col].mayContainGoal = false;
		
		if(trackAr[coord.row][coord.col].containsGoal)
		{
			// IF new goal,
			if(!findCoord(coord, foundGoalCoords, goalsFound-goalsReached))
			{
				foundGoalCoords[goalsFound-goalsReached].row = coord.row;
				foundGoalCoords[goalsFound-goalsReached].col = coord.col;
				goalsFound++;

				updateProjectedPath();
			}
			if(!isFixedGoal(coord))
				break;		
		}

		coord.row += dRow;
		coord.col += dCol;
	}
}

bool CRoboAIDoc::isDiagonal(Coord coord)
{
	return (coord.row == 1 && coord.col == 2) ||
	       (coord.row == 2 && coord.col == 3) ||
		   (coord.row == 3 && coord.col == 4) ||
		   (coord.row == 4 && coord.col == 5) ||
		   (coord.row == 5 && coord.col == 6);
}

// general helper function that returns true when 'coord' is in 'coordArray'
bool CRoboAIDoc::findCoord(Coord  coord, const struct Coord coordArray[], int arraySize)
{
	bool found = false;
	int i = 0;
	while(i < arraySize && !found)
	{
		found = (coordArray[i].row == coord.row) && (coordArray[i].col == coord.col);
		i++;
	}
	return found;
}

bool CRoboAIDoc::removeCoord(Coord  coord, struct Coord coordArray[], int arraySize)
{
	bool found = false;
	int i = 0;
	while(i < arraySize)
	{
		found = (coordArray[i].row == coord.row) && (coordArray[i].col == coord.col);
		if (found)
		{
			for (; i < arraySize-1; i++)
			{
				coordArray[i] = coordArray[i+1];
			}
			break;
		}
		i++;
	}
	return found;
}
// specific helper function for GUI returns true when coord is a fixed goal
bool CRoboAIDoc::isFixedGoal(Coord  coord)
{
	return findCoord(coord, FIXED_GOAL_COORDS, NUM_FIXED_GOALS);
}

//
// CRoboAIDoc ====== BOT'S NAVIGATION & SEARCHING ================
//
// Finds the path the bot should take
// PRE: numUnreachedGoals > 0
void CRoboAIDoc::updateProjectedPath()
{
	int startDist[GOALS_IN_ARENA];
	int goalDist[GOALS_IN_ARENA][GOALS_IN_ARENA];
	int stopDist[GOALS_IN_ARENA];

	Coord tempList[GOALS_IN_ARENA];
	
	int bestPerm[GOALS_IN_ARENA];
	int bestDist;

	PathList* nextPathHead;

	int i, j, tempDist;
	
	int* perm;            // base address of current perumtation
	int totalPerms;       // number of permutations, given numUnreachedGoals


	// Change of variables to bot's design.
	int numUnreachedGoals = goalsFound - goalsReached;
	struct Coord goalList[GOALS_IN_ARENA];
	for( i = 0; i < numUnreachedGoals; i++)
		goalList[i] = foundGoalCoords[i];

	if( numUnreachedGoals == 0 )
	{
		freeList(projectedPathHead);
		projectedPathHead = getPath( botCoord, BOT_STOP_COORD ).pathHead;
	}
	else
	{
		// find distances between goal nodes and start/stop nodes
		for( i = 0; i < numUnreachedGoals; i++)
		{
			startDist[i] = findDist(botCoord, goalList[i]);
			stopDist[i] = findDist(goalList[i], BOT_STOP_COORD);
		}

		// find distances between every goal node
		for( i = 0; i < numUnreachedGoals; i++)
		{
			for( j = 0; j <= i; j++)
			{
				if( i == j )
					goalDist[i][j] = 0;
				else
				{
					tempDist = findDist( goalList[i], goalList[j] );
					goalDist[i][j] = tempDist;
					goalDist[j][i] = tempDist;
				}
			}
		}

		// (PRE-CONDITION: numUnreachedGoals > 0)
		bestDist = 0x7FFF;   // (unsigned int8)
		perm = &perms[baseIndex[numUnreachedGoals]];
		totalPerms = numPerms[numUnreachedGoals];
		for(int p = 0; p < totalPerms; p++)
		{
			// Test Code: Print this permutation - {botCoord + perm. of goalList + BOT_STOP_COORD}
			/*
			CString tempS;
			tempS.Format("%d", botCoord.row);
			debugStr += "{(" + tempS + ",";
			tempS.Format("%d", botCoord.col);
			debugStr += tempS + ") ";
			for( i = 0; i < numUnreachedGoals; i++ )
			{
				tempS.Format("%d", goalList[perm[i]].row);
				debugStr += "(" + tempS + ",";
				tempS.Format("%d", goalList[perm[i]].col);
				debugStr += tempS + ") ";
			}
			tempS.Format("%d", BOT_STOP_COORD.row);
			debugStr += "(" + tempS + ",";
			tempS.Format("%d", BOT_STOP_COORD.col);
			debugStr += tempS + ")}: ";
			*/

			// Find distance of this permutation
			tempDist = startDist[perm[0]];
			for( i = 0; i < numUnreachedGoals-1; i++ )
				tempDist += goalDist[perm[i]][perm[i+1]];
			tempDist += stopDist[perm[i]];

			// save tempDist and perm, if this permutation is better
			if( tempDist < bestDist )
			{
				bestDist = tempDist;
				copyList(perm, bestPerm, numUnreachedGoals);
			}

			// advance perm base address to next permutation
			perm += numUnreachedGoals;

			// Test Code: Print distance
			/*
			tempS.Format("%d", tempDist);
			debugStr += tempS + "\r\n";
			*/
		}

		// Re-order goalList according to bestPerm.  (Useful for LCD debugging)
		copyList(goalList, tempList, numUnreachedGoals);
		for( i = 0; i < numUnreachedGoals; i++ )
			goalList[i] = tempList[bestPerm[i]];

		// Replace current projectedPath with newly found best path
		freeList(projectedPathHead);
		projectedPathHead = getPath( botCoord, goalList[0] ).pathHead;
		for( i = 0; i < numUnreachedGoals-1; i++ )
		{
			nextPathHead = freeNode(getPath(goalList[i],goalList[i+1]).pathHead);
			projectedPathHead = appendLast(projectedPathHead, nextPathHead);
		}
		nextPathHead = freeNode(getPath(goalList[i],BOT_STOP_COORD).pathHead);
		projectedPathHead = appendLast(projectedPathHead, nextPathHead);
	}
}

// Returns distance of shortest path from nodeA to nodeB
int CRoboAIDoc::findDist(Coord nodeA, Coord nodeB)
{
	PathWithCost tempPath;
	tempPath = getPath( nodeA, nodeB );
	freeList(tempPath.pathHead);
	return tempPath.pathCost;
}

// Copies first 'numElements' elements of srcList into destList
void CRoboAIDoc::copyList(Coord srcList[], Coord destList[], int numElements)
{
	for( int i = 0; i < numElements; i++ )
		destList[i] = srcList[i];
}
void CRoboAIDoc::copyList(int srcList[], int destList[], int numElements)
{
	for( int i = 0; i < numElements; i++ )
		destList[i] = srcList[i];
}

// moves bot to next node in path it should take
bool CRoboAIDoc::makeNextMove()
{
	bool moveSuccess;
	Coord start;
	Coord next;
	Coord temp;
	
	// Don't move, if at nest
	if( botCoord.row == BOT_STOP_COORD.row && botCoord.col == BOT_STOP_COORD.col )
	{
		return false;
	}

	// Set course to (1,6), if ball may be placed at (1,5) when bot is on (2,7)
	if( botCoord.row == 2 && botCoord.col == 7 &&
	    !trackAr[1][5].beenChecked && goalsFound < GOALS_IN_ARENA )
	{
		temp.row = 1;
		temp.col = 6;
		freeList(projectedPathHead);
		projectedPathHead = getPath( botCoord, temp ).pathHead;
	}

	// Set course to (5,6), if ball may be placed at (7,6) when bot is on (5,8)
	if( botCoord.row == 5 && botCoord.col == 8 &&
	    !trackAr[7][6].beenChecked && goalsFound < GOALS_IN_ARENA )
	{
		temp.row = 5;
		temp.col = 6;
		freeList(projectedPathHead);
		projectedPathHead = getPath( botCoord, temp ).pathHead;
	}

	if( projectedPathHead == NULL || projectedPathHead->nextNode == NULL )
	{
		updateProjectedPath();
	}
	
	// Get/free current coord and get next coord
	start = projectedPathHead->coord;
	projectedPathHead = freeNode(projectedPathHead);
	next = projectedPathHead->coord;
	
	// Find and move in direction of next coord
	if(start.row == next.row)
	{
		if(start.col > next.col)
			moveSuccess = move(LEFT);
		else
			moveSuccess = move(RIGHT);
	}
	else if(start.col == start.col)
	{
		if(start.row > next.row)
			moveSuccess = move(UP);
		else
			moveSuccess = move(DOWN);
	}
	else if(start.row > next.row)
		moveSuccess = move(UP);
	else
		moveSuccess = move(DOWN);
	
	return moveSuccess;
}

// pathHead of path returned equals null if path is not found
PathWithCost CRoboAIDoc::getPath(Coord start, Coord goal)
{
	PathWithCost pathReturned = { MAX_PATH, NULL };
	PathList *head = NULL;       // head of path found
	PathList *sucList = NULL;
	PathList *visitList = NULL;
	Coord curCoords;
	PathArray searchMap[ROWS][COLS];
	int r, c, curCost;
	
	//initialize search Map
	for(r = 0; r < ROWS; r++)
	{
		for(c = 0; c < COLS; c++)
		{
			searchMap[r][c].parent.row = -1;
			searchMap[r][c].parent.col = -1;
			searchMap[r][c].pathCost = MAX_COST;
			searchMap[r][c].visited = false;
		}
	}

	curCoords.row = start.row;
	curCoords.col = start.col;
	searchMap[start.row][start.col].pathCost = 0;
	searchMap[start.row][start.col].visited = true;

	//isNodeFlag = trackArray[][]...

	curCost = 0;
	while((curCoords.row != goal.row || curCoords.col != goal.col))
	{
		// explore successors, if haven't visited yet
		sucList = getSucessors(curCoords);
		while(sucList != NULL )
		{
			r = sucList->coord.row;
			c = sucList->coord.col;
			if(searchMap[r][c].visited == false)
			{
				// if already found, compare path costs
				if(searchMap[r][c].pathCost == MAX_COST)
				{
					searchMap[r][c].parent = curCoords;
					searchMap[r][c].pathCost = curCost 
						        + getPathCost(curCoords, sucList->coord);
					visitList = addNodeByCost(visitList, sucList->coord, searchMap);
				}
				else
				{
					// compare path costs...
				}
			}

			sucList = freeNode(sucList);
		}

		// visit next node w/ lowest cost, if one exists
		if(visitList == NULL)
		{
			return pathReturned;  //  b/c path not found
		}
		else
		{
			// get info of and remove first node of visitList
			curCoords = visitList->coord;
			curCost = searchMap[curCoords.row][curCoords.col].pathCost;
			searchMap[curCoords.row][curCoords.col].visited = true;
			visitList = freeNode(visitList);
		}
	}
	
	// form path found with searchMap
	pathReturned.pathCost = curCost;
	head = addNodeFirst(head, curCoords);
	while(curCoords.row != start.row || curCoords.col != start.col)
	{
		curCoords = searchMap[curCoords.row][curCoords.col].parent;
		head = addNodeFirst(head, curCoords);
	}
	pathReturned.pathHead = head;

	// free rest of visitList
	freeList(visitList);

	return pathReturned;
}

// assumes a and b are adjacent nodes
int CRoboAIDoc::getPathCost(Coord a, Coord b)
{
	if(a.row == b.row)
		return abs(a.col - b.col);
	else if(a.col == b.col)
		return abs(a.row - b.row);
	else
		return 2;
}

PathList* CRoboAIDoc::getSucessors(Coord parent)
{
	PathList *head = NULL;

	// look for a node in all four directions
	head = appendLast(head, findNode(parent,  0, -1));
	head = appendLast(head, findNode(parent,  0,  1));
	head = appendLast(head, findNode(parent,  1,  0));
	head = appendLast(head, findNode(parent, -1,  0));
	
	// IF in either cell w/ diagonal, look in diagonal direction for nodes
	if (isDiagonal(parent))
	{		
		head = appendLast(head, findNode(parent,1,1));
		head = appendLast(head, findNode(parent,-1,-1));
	}

	return head;
}

// helper function for getSuccessors
PathList* CRoboAIDoc::findNode(Coord parent, int dRow, int dCol)
{
	int r = parent.row + dRow;
	int c = parent.col + dCol;	

	PathList *node;
	node = (struct PathList *)malloc(sizeof(struct PathList));

	while(!trackAr[r][c].isNode)
	{
		if(trackAr[r][c].isWall)
			return NULL;
		r += dRow;
		c += dCol;
	}

	node->coord.row = r;
	node->coord.col = c;
	node->nextNode = NULL;
	return node;
}
//
// CRoboAIDoc ====== LINKED LIST HELPER FUNCTIONS ================
//
// Frees all nodes in list at head
void CRoboAIDoc::freeList(PathList * head)
{
	while(head != NULL)
	{
		head = freeNode(head);
	}
}
// Frees node at head and returns pointer to next node
PathList * CRoboAIDoc::freeNode(PathList * head)
{
	PathList *temp = NULL;
	temp = head;
	head = head->nextNode;
	free(temp);
	return head;
}

PathList* CRoboAIDoc::addNodeByCost(PathList* head, Coord newCoord, PathArray searchMap[ROWS][COLS])
{
	PathList *current = NULL;
	PathList *next = NULL;
	PathList *newNode = NULL;
	Coord headCoord;
	Coord nextCoord;

	newNode = (struct PathList *)malloc(sizeof(struct PathList));
	newNode->coord = newCoord;
	newNode->nextNode = NULL;

	//add to empty list
	if(head == NULL)
	{
		return newNode;
	}

	headCoord = head->coord;
	newCoord = newNode->coord;
	
	//add to front of list
	if (searchMap[headCoord.row][headCoord.col].pathCost > searchMap[newCoord.row][newCoord.col].pathCost)
	{
		next = head;
		head = newNode;
		head->nextNode = next;
	}
	
	//add after head
	else
	{
		current = head;
		next = head->nextNode;

		while(next != NULL)
		{
			nextCoord = next->coord;
			if (searchMap[nextCoord.row][nextCoord.col].pathCost >= searchMap[newCoord.row][newCoord.col].pathCost)
				break;
			
			current = current->nextNode;
			next = next->nextNode;
		}

		newNode->nextNode = next;
		current->nextNode = newNode;
	}

	return head;
}

PathList* CRoboAIDoc::appendLast(PathList* head, PathList* newNode)
{
	PathList *current = head;

	if(head == NULL)
	{
		head = newNode;
	}
	else if(newNode != NULL)
	{
		while(current->nextNode != NULL)
		{
			current = current->nextNode;
		}
		current->nextNode = newNode;
	}

	return head;
}

PathList* CRoboAIDoc::addNodeFirst(PathList* head, Coord newCoord)
{
	PathList *current = head;
	PathList *temp = NULL;
	PathList *newNode;
	
	newNode = (struct PathList *)malloc(sizeof(struct PathList));
	newNode->coord = newCoord;
	newNode->nextNode = NULL;

	if(head == NULL)
	{
		head = newNode;
	}
	else
	{
		temp = head;
		head = newNode;
		head->nextNode = temp;
	}
	return head;
}
