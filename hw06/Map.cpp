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

	for (int i = 0; i < 12; ++i) {
		for (int j = 0; j < 12; ++j) {
			char newChar;
			bool valid;
			do {
				valid = true;
				newChar = charArray[rand() % 5];

				// Check above
				if (i > 0 && terrainMap[i - 1][j] == newChar)
					valid = false;
				// Check left
				if (j > 0 && terrainMap[i][j - 1] == newChar)
					valid = false;

			} while (!valid);

			terrainMap[i][j] = newChar;
		}
	}
	setContestantPositions();
}

Map::~Map() {
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			terrainMap[j][j] = ' ';
		}
	}
}
void Map::printMap(Contestant contestant) const {
	if (contestant.getIsPlayer())
	{
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				if (j == playerX && i == playerY)
				{
					std::cout << '@';
				}
				else if (j == enemyX && i == enemyY)
				{
					if (abs(enemyX - playerX) <= 1 && abs(enemyY - playerY) <= 1)
						std::cout << 'E';
					else
						std::cout << terrainMap[j][i];
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
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 12; j++)
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
	int randX = (rand() % 12);
	int randY = (rand() % 12);
	playerX = randX;
	playerY = randY;
	randX = (rand() % 12);
	randY = (rand() % 12);
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
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 12; j++)
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
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 12; j++)
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