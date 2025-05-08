#include "Map.h"
#include <cstdlib>
#include <iostream>
#include <ctime>

Map::Map()
{
	//Generate the map first, truly random
	srand(time(0));
	//Character array to reference when setting each tile of the map
	char charArray[5] = { 'F', 'M', 'P', 'W', 'S' };

	bool validMap = false;
	do
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				//Generate random number from 1 - 5 
				int randNum = (rand() % 5);
				terrainMap[i][j] = charArray[randNum];
			}
		}

		//Step through the map and check each tile for criteria, changing them if necessary
		int invalidChars = 0;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (i != 0)
				{
					if (terrainMap[i - 1][j] == terrainMap[i][j])
					{
						invalidChars++;
						break;
					}
				}
				if (i != 4)
				{
					if (terrainMap[i + 1][j] == terrainMap[i][j])
					{
						invalidChars++;
						break;
					}
				}
				if (j != 0)
				{
					if (terrainMap[i][j - 1] == terrainMap[i][j])
					{
						invalidChars++;
						break;
					}
				}
				if (j != 4)
				{
					if (terrainMap[i][j + 1] == terrainMap[i][j])
					{
						invalidChars++;
						break;
					}
				}
			}
		}
		if (invalidChars == 0) validMap = true;
	} while (!validMap);
	setContestantPositions();
}

Map::~Map() {
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			terrainMap[j][j] = ' ';
		}
	}
}
void Map::printMap(Contestant contestant) const {
	if (contestant.getIsPlayer())
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (j == playerX && i == playerY)
				{
					std::cout << '@';
				}
				else if (j == enemyX && i == enemyY)
				{
					std::cout << 'E';
				}
				else
				{
					std::cout << terrainMap[j][i];
				}
			}
			std::cout << std::endl;
		}
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (i == enemyX && j == enemyY)
				{
					std::cout << 'E';
				}
				else
				{
					std::cout << terrainMap[i][j];
				}
			}
			std::cout << std::endl;
		}
	}
}

void Map::setContestantPositions() {
	int randX = (rand() % 5);
	int randY = (rand() % 5);
	playerX = randX;
	playerY = randY;
	randX = (rand() % 5);
	randY = (rand() % 5);
	enemyX = randX;
	enemyY = randY;
}
Map Map::generateVisibleMap(Contestant contestant) {
	if (contestant.getIsPlayer())
	{
		//Create a new map object centered on the player, then build that map with only 
		// visible tiles filling in everything else with '#' 
		Map tempMap;
		tempMap.playerX = playerX;
		tempMap.playerY = playerY;
		tempMap.enemyX = enemyX;
		tempMap.enemyY = enemyY;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (abs(i - playerX) > 1)
				{
					tempMap.terrainMap[i][j] = '#';
				}
				else if (abs(j - playerY) > 1)
				{
					tempMap.terrainMap[i][j] = '#';
				}
				else
				{
					tempMap.terrainMap[i][j] = terrainMap[i][j];
				}
			}
		}
		return tempMap;
	}
	else
	{
		//Create a new map object centered on the player, then build that map with only 
		// visible tiles filling in everything else with '#' 
		Map tempMap;
		tempMap.playerX = playerX;
		tempMap.playerY = playerY;
		tempMap.enemyX = enemyX;
		tempMap.enemyY = enemyY;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (abs(i - enemyX) > 1)
				{
					tempMap.terrainMap[i][j] = '#';
				}
				else if (abs(j - enemyY) > 1)
				{
					tempMap.terrainMap[i][j] = '#';
				}
				else
				{
					tempMap.terrainMap[i][j] = terrainMap[i][j];
				}
			}
		}
		return tempMap;
	}
}