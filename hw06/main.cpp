//Programmer: Kaleb Spreckelmeyer
//Date: 5/6/2025
//File: main.cpp
//Assignment: HW7
//Purpose: This will contain a turn based Codemon game

#include <iostream>
#include <string>
#include "Contestant.h"
#include "Codemon.h"
#include "Item.h"
#include "Skill.h"
#include "Map.h"

//DESC: Main game loop containing the battle mechanics and turns. Will close and print a message upon someone's victory
//PRE: All variables should be properly initialized 
//POST: Someoen will be the winner and they will be printed a congragulatory message
void mainGameLoop(Map map, Contestant player, Contestant enemy, Codemon startingPlayerCodemon, Codemon startingEnemyCodemon);

//DESC: Contains the logic for one player turn
//PRE: All variables should be properly initialized 
//POST: Codemon will be updated, so they must be checked before advancing to the next round for faints
void playerTurn(Map& map, Contestant player, Contestant enemy, Codemon& activePlayerCodemon, Codemon& activeEnemyCodemon, std::string typeChart[], double typeAdvantageChart[][4]);

//DESC: Contains the logic for one enemy turn
//PRE: All variables should be properly initialized 
//POST: Codemon will be updated, so they must be checked before advancing to the next round for faints
void enemyTurn(Map& map, Contestant player, Contestant enemy, Codemon& activePlayerCodemon, Codemon& activeEnemyCodemon, std::string typeChart[], double typeAdvantageChart[][4]);

using namespace std;

int main() {
	////Create 3 contestants
	////Using default constructor
	//Contestant contestant1 = Contestant();
	////Using parameterized constructor
	//Contestant contestant2 = Contestant("Ash");
	////Using copy constructor
	//Contestant contestant3 = Contestant(contestant2);

	////Create array of contestants
	//Contestant contestants[3] = {
	//	Contestant(""),
	//	Contestant(""),
	//	Contestant("")
	//};
	//contestants[0] = contestant1;
	//contestants[1] = contestant2;
	//contestants[2] = contestant3;

	////Prepare contestants
	//for (int i = 0; i < 3; i++)
	//{
	//	contestants[i].prepare();
	//}

	////Print out contestant information
	//for (int i = 0; i < 3; i++)
	//{
	//	std::cout << contestants[i].getName() << std::endl;
	//	contestants[i].print();
	//	std::cout << "--------------------------------------------" << std::endl;
	//}

	////Test skill loopup
	//skillLookup(contestants, 3);

	//Seed random number generator
	srand(1025);

	//Load terrain map and set Contestant Positions
	Map map;

	//Load contestants
	Contestant player = Contestant("Player", true);
	Contestant enemy = Contestant("Enemy", false);

	//Load Codemons
	const int POOL_SIZE = 12;

	const string CODEMON_NAMES[POOL_SIZE] = {
		"Flareth", // Fire
		"Aquagon", // Water
		"Leafowl", // Grass 
		"Voltiguana", // Electric 
		"Infermouse", // Fire
		"Bubbletail", // Water
		"Shrubling", // Grass 
		"Zapkit", // Electric
		"Cindermole", // Fire
		"Torrentoise", // Water 
		"Thornabbit", // Grass
		"Shockpup" // Electric
	};

	const string CODEMON_TYPES[POOL_SIZE] = {
		"FIRE",
		"WATER",
		"GRASS",
		"ELECTRIC",
		"FIRE",
		"WATER",
		"GRASS",
		"ELECTRIC",
		"FIRE",
		"WATER",
		"GRASS",
		"ELECTRIC"
	};
	const int CODEMON_HP[POOL_SIZE] = {
		40, 42, 38, 35,
		34, 45, 37, 32,
		39, 48, 40, 36
	};

	const int CODEMON_LEVELS[POOL_SIZE] = {
		5, 4, 2, 6,
		7, 3, 1, 0,
		8, 9, 10, 11
	};

	const string CODEMON_SKILLS[POOL_SIZE] = {
		"Flame Burst", "Aqua Jet", "Razor Leaf", "Thunder Jolt",
		"Fire Claw", "Bubble Beam", "Vine Whip", "Static Bolt",
		"Ember Rage", "Water Pulse", "Spore Shot", "Spark Bite"
	};

	const int CODEMON_SKILL_DAMAGE[POOL_SIZE] = {
		12, 10, 11, 13,
		15, 14, 19, 17,
		16, 18, 20, 21
	};

	//Assign Codemons

	//Computer Assignment
	int choices[3] = { 0, 0, 0 };
	for (int i = 0; i < 3; i++)
	{
		bool validNumber = false;
		int randomNumber = 0;
		do
		{
			randomNumber = (rand() % 12);
			choices[i] = randomNumber;
			int numDuplicates = 0;
			for (int i = 0; i < 3; i++)
			{
				if (choices[i] == randomNumber)
				{
					numDuplicates++;
				}
			}
			if (numDuplicates == 1)
			{
				validNumber = true;
			}
		} while (!validNumber);
		Codemon temp = Codemon(CODEMON_NAMES[randomNumber], CODEMON_TYPES[randomNumber],
			CODEMON_LEVELS[randomNumber], CODEMON_HP[randomNumber]);
		Skill tempSkill = Skill(CODEMON_SKILLS[randomNumber], CODEMON_SKILL_DAMAGE[randomNumber]);
		temp.updateSkills(tempSkill);
		enemy.updatePocket(temp);
	}
	//Player assignment
	bool validChoice = false;
	int choice = 0;
	do
	{
		std::cout << "Would you like to create your own 3 codemons or have the computer pick for you? 0 - choose your own, 1 let the computer choose:";
		cin >> choice;
		cin.ignore();
		if (choice < 0 || choice > 1)
		{
			std::cout << "Invalid submission" << std::endl;
		}
		else
		{
			validChoice = true;
		}
	} while (!validChoice);
	
	if (choice == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			std::string name = "";
			std::string type = "";
			int level = 0;
			int health = 0;
			cout << "Enter the codemon's name: ";
			getline(cin, name);
			cout << "Enter the codemon's type: ";
			getline(cin, type);
			cout << "Enter the codemon's level: ";
			cin >> level;
			cout << "Enter the codemon's HP: ";
			cin >> health;
			cin.ignore();

			Codemon temp = Codemon(name, type, level, health);

			Skill skill;
			string skillName;
			int skillDamage;
			cout << "Enter the name of the codemon's skill: ";
			getline(cin, skillName);
			cout << "Enter the damage of the skill: ";
			cin >> skillDamage;
			skill.setDamage(skillDamage);
			skill.setName(skillName);

			temp.updateSkills(skill);

			player.updatePocket(temp);
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			bool validNumber = false;
			int randomNumber = 0;
			do
			{
				randomNumber = (rand() % 12);
				choices[i] = randomNumber;
				int numDuplicates = 0;
				for (int i = 0; i < 3; i++)
				{
					if (choices[i] == randomNumber)
					{
						numDuplicates++;
					}
				}
				if (numDuplicates == 1)
				{
					validNumber = true;
				}
			} while (!validNumber);
			Codemon temp = Codemon(CODEMON_NAMES[randomNumber], CODEMON_TYPES[randomNumber],
				CODEMON_LEVELS[randomNumber], CODEMON_HP[randomNumber]);
			Skill tempSkill = Skill(CODEMON_SKILLS[randomNumber], CODEMON_SKILL_DAMAGE[randomNumber]);
			temp.updateSkills(tempSkill);
			player.updatePocket(temp);
		}
	}

	//Select active codemons
	//Enemy
	int randomNum = (rand() % 3);
	Codemon enemyActiveCodemon = enemy.codemons[randomNum];
	
	//Player
	validChoice = false;
	int codemonChoice = 0;
	do
	{
		cout << "Select a codemon to deploy into battle: " << endl;
		for (int i = 0; i < player.getNumCodemons(); i++)
		{
			cout << i + 1 << ") " << player.codemons[i].getName() << endl;
		}
		cin >> codemonChoice;

		if (codemonChoice > 0 && codemonChoice <= player.getNumCodemons())
		{
			validChoice = true;
		}
	} while (!validChoice);
	
	Codemon playerActiveChoice = player.codemons[codemonChoice - 1];

	
	mainGameLoop(map, player, enemy, playerActiveChoice, enemyActiveCodemon);
}

void mainGameLoop(Map map, Contestant player, Contestant enemy, Codemon startingPlayerCodemon, Codemon startingEnemyCodemon)
{
	//Used to check for the winner. If either of these have a size = the numCodemons, they have lost!
	int numPlayerFaintedCodemons = 0;
	int numEnemyFaintedCodemons = 0;
	
	//Used to hold the active codemon, change when the hp reaches 0
	Codemon activePlayerCodemon = startingPlayerCodemon;
	Codemon activeEnemyCodemon = startingEnemyCodemon;

	//Used to hold the living codemons from each contestant's pocket. Updated when each one faints
	//Codemon livingPlayerCodemons[3];
	//for (int i = 0; i < 3; i++)
	//{
	//	livingPlayerCodemons[i] = player.codemons[i];
	//}
	//Codemon livingEnemyCodemons[3];
	//for (int i = 0; i < 3; i++)
	//{
	//	livingEnemyCodemons[i] = enemy.codemons[i];
	//}

	//Type advantage chart
	double typeAdvantageChart[4][4];
	typeAdvantageChart[0][0] = 1.0;
	typeAdvantageChart[1][0] = 2.0;
	typeAdvantageChart[2][0] = 0.5;
	typeAdvantageChart[3][0] = 1.0;
	typeAdvantageChart[0][1] = 0.5;
	typeAdvantageChart[1][1] = 1.0;
	typeAdvantageChart[2][1] = 2.0;
	typeAdvantageChart[3][1] = 2.0;
	typeAdvantageChart[0][2] = 2.0;
	typeAdvantageChart[1][2] = 0.5;
	typeAdvantageChart[2][2] = 1.0;
	typeAdvantageChart[3][2] = 1.0;
	typeAdvantageChart[0][3] = 1.0;
	typeAdvantageChart[1][3] = 1.0;
	typeAdvantageChart[2][3] = 1.0;
	typeAdvantageChart[3][3] = 1.0;

	//TESTING: PRINT CHART
	/*for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << typeAdvantageChart[i][j] << " ";
		}
		cout << endl;
	}*/

	//Type chart
	string typeChart[4] = { "Fire", "Water", "Grass", "Electric" };

	bool someoneDefeated = false;
	do
	{
		//Check for fainted codemon, prompt the user to change if active codemon has fainted
		if (activePlayerCodemon.getHealth() <= 0)
		{
			cout << "Your " << activePlayerCodemon.getName() << " has fainted!" << endl;
			numPlayerFaintedCodemons++;
			for (int i = 0; i < player.getNumCodemons(); i++)
			{
				if (player.codemons[i].getName() == activePlayerCodemon.getName())
				{
					player.codemons[i].setName("FAINTED CODEMON");
				}
			}
			//check if they have any codemon left 
			if (numPlayerFaintedCodemons >= player.getNumCodemons())
			{
				someoneDefeated = true;
			}
			else
			{
				bool validChoice = false;
				int codemonChoice = 0;
				do
				{
					cout << "Select a codemon to deploy into battle: " << endl;
					for (int i = 0; i < player.getNumCodemons(); i++)
					{
						cout << i + 1 << ") " << player.codemons[i].getName() << endl;
					}
					cin >> codemonChoice;

					if (codemonChoice > 0 && codemonChoice <= player.getNumCodemons())
					{
						if (player.codemons[codemonChoice - 1].getName() == "FAINTED CODEMON")
						{
							cout << "You can't bring a fainted codemon into battle!" << endl;
						}
						else
						{
							validChoice = true;
						}
					}
				} while (!validChoice);

				activePlayerCodemon = player.codemons[codemonChoice - 1];
			}
		}
		if (activeEnemyCodemon.getHealth() <= 0)
		{
			cout << "The enemy's " << activeEnemyCodemon.getName() << " has fainted!" << endl;
			numEnemyFaintedCodemons++;
			for (int i = 0; i < enemy.getNumCodemons(); i++)
			{
				if (enemy.codemons[i].getName() == activeEnemyCodemon.getName())
				{
					enemy.codemons[i].setName("FAINTED CODEMON");
				}
			}
			//check if they have any codemon left 
			if (numEnemyFaintedCodemons >= enemy.getNumCodemons())
			{
				someoneDefeated = true;
				break;
			}
			else {
				bool validChoice = false;
				int randomNum = 0;
				int retries = 0;
				int maxRetries = 100; 

				do {
					int aliveCodemonCount = enemy.getNumCodemons() - numEnemyFaintedCodemons;

					if (aliveCodemonCount <= 0) {
						std::cout << "No alive enemy codemons remain!\n";
						break;
					}

					randomNum = rand() % aliveCodemonCount;

					if (randomNum < 0) continue;

					if (enemy.codemons[randomNum].getName() != "FAINTED CODEMON") {
						validChoice = true;
					}

					retries++;
				} while (!validChoice && retries < maxRetries);

				if (validChoice) {
					activeEnemyCodemon = enemy.codemons[randomNum];
				}
			}

		}
		if (someoneDefeated == false)
		{
			//determine who moves first
			int randomNum = (rand() % 2) + 1;
			//Player moves first
			if (randomNum == 1)
			{
				playerTurn(map, player, enemy, activePlayerCodemon, activeEnemyCodemon, typeChart, typeAdvantageChart);
				enemyTurn(map, player, enemy, activePlayerCodemon, activeEnemyCodemon, typeChart, typeAdvantageChart);
			}
			//Enemy moves first
			else
			{
				enemyTurn(map, player, enemy, activePlayerCodemon, activeEnemyCodemon, typeChart, typeAdvantageChart);
				playerTurn(map, player, enemy, activePlayerCodemon, activeEnemyCodemon, typeChart, typeAdvantageChart);
			}
		}
	} while (!someoneDefeated);

	//Print victory message
	if (player.getNumCodemons() > numPlayerFaintedCodemons)
	{
		cout << "The player wins!" << endl;
	}
	else
	{
		cout << "The computer wins!" << endl;
	}
}

void playerTurn(Map& map, Contestant player, Contestant enemy, Codemon& activePlayerCodemon, Codemon& activeEnemyCodemon, string typeChart[], double typeAdvantageChart[][4])
{
	//show the visible map for the player
	Map visibleMap = map.generateVisibleMap(player);
	player.printVisibleMap(enemy, map, activePlayerCodemon, activeEnemyCodemon);
	//check the visible map for the enemy, if found, give player option to attack them
	bool inRange = false;
	if (abs(map.enemyX - map.playerX) <= 1 && abs(map.enemyY - map.playerY) <= 1)
	{
		inRange = true;
	}
	if (inRange)
	{
		cout << "Attack enemy? (0 = yes, 1 = no): ";
		bool validInput = false;
		int choice = -1;
		do
		{
			cin >> choice;
			if (choice < 0 || choice > 1)
			{
				cout << "Invalid submission" << endl;
			}
			else
			{
				validInput = true;
			}
		} while (!validInput);

		if (choice == 0)
		{
			//attack
			//select a skill to use
			cout << "Select a skill to use: " << endl;
			Skill* tempSkills = activePlayerCodemon.getSkills();
			for (int i = 0; i < 6; i++)
			{
				cout << i + 1 << ") " << tempSkills->getName() << "; Damage:"
					<< tempSkills->getDamage() << endl;
			}
			bool validAttackChoice = false;
			int attackChoice = 0;
			do
			{
				cin >> attackChoice;
				if (attackChoice < 1 || attackChoice > 6)
				{
					validAttackChoice = false;
				}
				else
				{
					validAttackChoice = true;
				}
			} while (!validAttackChoice);

			//Calculate final damage using attack type matrix

			double initialDamage = tempSkills[attackChoice - 1].getDamage();
			delete[]tempSkills;

			int attackerType = 0;
			int defenderType = 0;

			for (int i = 0; i < 4; i++)
			{
				if (typeChart[i] == activePlayerCodemon.getType())
				{
					attackerType = i;
				}
				if (typeChart[i] == activeEnemyCodemon.getType())
				{
					defenderType = i;
				}
			}

			double multiplier = typeAdvantageChart[attackerType][defenderType];

			double effectiveDamage = initialDamage * multiplier;

			activeEnemyCodemon -= effectiveDamage;
		}
		else
		{
			//do nothing
		}
	}
	else
	{
		cout << "Where would you like to move? W A S D are cardinal directions, Q E Z C are diagonals: ";
		char moveChoice;
		bool validMoveChoice = false;
		do
		{
			cin >> moveChoice;
			//Clears the fail state cin seems to be getting into under certain circumstances
			if (cin.fail()) {
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
			if (moveChoice == 'w' || moveChoice == 'W')
			{
				if (map.playerY == 0)
				{
					cout << "You cannot move further up" << endl;
				}
				else
				{
					validMoveChoice = true;
					map.playerY -= 1;
				}
			}
			else if (moveChoice == 'a' || moveChoice == 'A')
			{
				if (map.playerX == 0)
				{
					cout << "You cannot move further left" << endl;
				}
				else
				{
					validMoveChoice = true;
					map.playerX -= 1;
				}
			}
			else if (moveChoice == 's' || moveChoice == 'S')
			{
				if (map.playerY == 4)
				{
					cout << "You cannot move further down" << endl;
				}
				else
				{
					validMoveChoice = true;
					map.playerY += 1;
				}
			}
			else if (moveChoice == 'd' || moveChoice == 'D')
			{
				if (map.playerX == 4)
				{
					cout << "You cannot move further right" << endl;
				}
				else
				{
					validMoveChoice = true;
					map.playerX += 1;
				}
			}
			else if (moveChoice == 'q' || moveChoice == 'Q')
			{
				if (map.playerX == 0 || map.playerY == 0)
				{
					cout << "You cannot move diagonally up left" << endl;
				}
				else
				{
					validMoveChoice = true;
					map.playerX -= 1;
					map.playerY -= 1;
				}
			}
			else if (moveChoice == 'e' || moveChoice == 'E')
			{
				if (map.playerX == 4 || map.playerY == 0)
				{
					cout << "You cannot move diagonally up right" << endl;
				}
				else
				{
					validMoveChoice = true;
					map.playerX -= 1;
					map.playerY += 1;
				}
			}
			else if (moveChoice == 'z' || moveChoice == 'Z')
			{
				if (map.playerX == 4 || map.playerY == 0)
				{
					cout << "You cannot move diagonally down left" << endl;
				}
				else
				{
					validMoveChoice = true;
					map.playerX += 1;
					map.playerY -= 1;
				}
			}
			else if (moveChoice == 'c' || moveChoice == 'C')
			{
				if (map.playerX == 4 || map.playerY == 4)
				{
					cout << "You cannot move diagonally down right" << endl;
				}
				else
				{
					validMoveChoice = true;
					map.playerX += 1;
					map.playerY += 1;
				}
			}
			else
			{
				cout << "Invalid submission" << endl;
			}
		} while (!validMoveChoice);
	}
}

void enemyTurn(Map& map, Contestant player, Contestant enemy, Codemon& activePlayerCodemon, Codemon& activeEnemyCodemon, string typeChart[], double typeAdvantageChart[][4])
{
	//generate the visible map for the enemy
	Map visibleMap = map.generateVisibleMap(enemy);
	//check the visible map for the enemy, if found, give player option to attack them
	bool inRange = false;
	if (abs(map.enemyX - map.playerX) <= 1 && abs(map.enemyY - map.playerY) <= 1)
	{
		inRange = true;
	}

	if (inRange)
	{
		//attack
		//select a skill to use
		Skill* tempSkills = activeEnemyCodemon.getSkills();
		bool validAttackChoice = false;
		int randomSkill = 0;
		do
		{
			randomSkill = (rand() % 6);
			if (tempSkills[randomSkill].getName() == "Unnamed")
			{
				continue;
			}
			else
			{
				validAttackChoice = true;
			}
		} while (!validAttackChoice);


		//Calculate final damage using attack type matrix

		double initialDamage = tempSkills[randomSkill].getDamage();
		delete[]tempSkills;

		int attackerType = 0;
		int defenderType = 0;

		for (int i = 0; i < 4; i++)
		{
			if (typeChart[i] == activeEnemyCodemon.getType())
			{
				attackerType = i;
			}
			if (typeChart[i] == activePlayerCodemon.getType())
			{
				defenderType = i;
			}
		}

		double multiplier = typeAdvantageChart[attackerType][defenderType];

		double effectiveDamage = initialDamage * multiplier;

		activePlayerCodemon -= effectiveDamage;
	}
	else
	{
		//move 

		//I ripped this out of the player's option and adjusted it in case it looks funny
		int moveChoice = 0;
		bool validMoveChoice = false;
		do
		{
			moveChoice = (rand() % 8) + 1;

			if (moveChoice == 1)
			{
				if (map.enemyY == 0)
				{
				}
				else
				{
					validMoveChoice = true;
					map.enemyY -= 1;
				}
			}
			else if (moveChoice == 2)
			{
				if (map.enemyX == 0)
				{
				}
				else
				{
					validMoveChoice = true;
					map.enemyX -= 1;
				}
			}
			else if (moveChoice == 3)
			{
				if (map.enemyY == 4)
				{
				}
				else
				{
					validMoveChoice = true;
					map.enemyY += 1;
				}
			}
			else if (moveChoice == 4)
			{
				if (map.enemyX == 4)
				{
				}
				else
				{
					validMoveChoice = true;
					map.enemyX += 1;
				}
			}
			else if (moveChoice == 5)
			{
				if (map.enemyX == 0 || map.enemyY == 0)
				{
				}
				else
				{
					validMoveChoice = true;
					map.enemyX -= 1;
					map.enemyY -= 1;
				}
			}
			else if (moveChoice == 6)
			{
				if (map.enemyX == 4 || map.enemyY == 0)
				{
				}
				else
				{
					validMoveChoice = true;
					map.enemyX -= 1;
					map.enemyY += 1;
				}
			}
			else if (moveChoice == 7)
			{
				if (map.enemyX == 4 || map.enemyY == 0)
				{
				}
				else
				{
					validMoveChoice = true;
					map.enemyX += 1;
					map.enemyY -= 1;
				}
			}
			else if (moveChoice == 8)
			{
				if (map.enemyX == 4 || map.enemyY == 4)
				{
				}
				else
				{
					validMoveChoice = true;
					map.enemyX += 1;
					map.enemyY += 1;
				}
			}
			else
			{
				cout << "ERROR: Invalid submission in computer turn move choice" << endl;
			}
		} while (!validMoveChoice);
	}

}
