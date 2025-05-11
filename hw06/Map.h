#ifndef MAP_H
#define MAP_H
#include "Contestant.h"
class Map
{
public:
	char terrainMap[12][12];
	char itemMap[12][12];
	int playerX;
	int playerY;
	int enemyX;
	int enemyY;
	int allyCoords[2][2];

	//Default constructor, generates terrain map randomly (seeded in main)
	Map();
	//Destructor
	~Map();
	 
	//DESC: Prints a map as it is passed, adding the player or enemy's position on top of it
	// as the maps are stored without the player's tile so that the ground they're standing on
	// can be read
	//PRE: Contestant and map should be properly initialized 
	//POST: Map will be printed to the console
	void printMap(Contestant contestant) const;

	//DESC: Randomly selects a position on the map to place each contestant's starting point
	//PRE: Map should be initialized properly
	//POST: Map will be altered with starting points placed
	void setContestantPositions();

	//DESC: Generates the visible map, either for the player or the enemy dictated by the passsed
	// boolean
	//PRE: Map and boolean should be initialized
	//POST: New map object will be returned that shows only the visible tiles
	Map generateVisibleMap(Contestant contestant);
};
#endif // !MAP_H




