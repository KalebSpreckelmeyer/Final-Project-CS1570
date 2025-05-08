#include "Contestant.h"
#include <iostream>
#include "Map.h"	

Contestant::Contestant()
{
	std::cout << "Enter contestant name: ";
	std::getline(std::cin, this->name);
	this->numCodemons = 0;
	this->numItems = 0;
	this->isPlayer = false;
}

Contestant::Contestant(std::string name, bool isPlayer)
{
	this->name = name;
	this->numCodemons = 0;
	this->numItems = 0;
	this->isPlayer = isPlayer;
}
//
//Contestant::Contestant(const Contestant& other)
//{
//	std::cout << "Enter contestant name: ";
//	std::getline(std::cin, this->name);
//	this->numCodemons = other.numCodemons;
//	this->numItems = other.numItems;
//	this->isPlayer = other.isPlayer;
//	for (int i = 0; i < numCodemons; i++)
//	{
//		this->codemons[i] = other.codemons[i];
//	}
//	for (int i = 0; i < numItems; i++)
//	{
//		this->items[i] = other.items[i];
//	}
//}

void Contestant::updatePocket(Codemon codemon)
{
	//Check if codemon is already present
	for (int i = 0; i < numCodemons; i++)
	{
		if (codemons[i].getName() == codemon.getName())
		{
			std::cout << "Codemon already present!" << std::endl;
			return;
		}
	}
	//Add codemon to pocket
	codemons[numCodemons] = codemon;
	numCodemons++;
}

void Contestant::updateBackpack(Item item)
{
	//Add item to backpack
	items[numItems] = item;
	numItems++;
}

void Contestant::prepare()
{
	//update pocket and backpack contents
	bool doneUpdatingPocket = false;
	do
	{
		if (numCodemons >= 10)
		{
			std::cout << "Pocket is full!" << std::endl;
			doneUpdatingPocket = true;
			break;
		}
		std::cout << "Update " << this->name << "'s pocket with codemon ? (y / n) : ";
		char choice;
		std::cin >> choice;
		if (choice == 'y' || choice == 'Y')
		{
			std::string name, type;
			int level, health;
			std::cout << "Enter codemon name: ";
			std::cin >> name;
			std::cout << "Enter codemon type: ";
			std::cin >> type;
			std::cout << "Enter codemon level: ";
			std::cin >> level;
			std::cout << "Enter codemon health: ";
			std::cin >> health;
			Codemon newCodemon(name, type, level, health);

			//Add skills to codemon
			for (int i = 0; i < 6; i++)
			{
				std::cout << "Update skill " << i + 1 << " for codemon? (y/n): ";
				char skillChoice;
				std::cin >> skillChoice;
				if (skillChoice == 'n' || skillChoice == 'N')
				{
					break;
				}
				std::string skillName;
				int skillDamage;
				std::cout << "Enter skill name: ";
				std::cin.ignore(10000, '\n');
				std::getline(std::cin, skillName);
				std::cout << "Enter skill damage: ";
				std::cin >> skillDamage;
				Skill newSkill(skillName, skillDamage);
				newCodemon.updateSkills(newSkill);
			}
			updatePocket(newCodemon);
		}
		else
		{
			doneUpdatingPocket = true;
		}
	} while (!doneUpdatingPocket);
	bool doneUpdatingBackpack = false;
	do
	{
		if (numItems >= 20)
		{
			std::cout << "Backpack is full!" << std::endl;
			doneUpdatingBackpack = true;
			break;
		}
		std::cout << "Update backpack with item? (y/n): ";
		char choice;
		std::cin >> choice;
		if (choice == 'y' || choice == 'Y')
		{
			std::string name, description;
			int duration;
			std::cout << "Enter item name: ";
			std::cin >> name;
			std::cout << "Enter item description: ";
			std::cin >> description;
			std::cout << "Enter item duration: ";
			std::cin >> duration;
			Item newItem(name, description, duration);
			updateBackpack(newItem);
		}
		else
		{
			doneUpdatingBackpack = true;
		}
	} while (!doneUpdatingBackpack);
}

void Contestant::print()
{
	std::cout << "Contestant Name: " << this->name << std::endl;
	std::cout << "Number of Codemons: " << this->numCodemons << std::endl;
	std::cout << "Codemons: " << std::endl;
	Codemon sortedCodemons[6];
	for (int i = 0; i < 6; i++)
	{
		Codemon tempCodemon = codemons[i];
		for (int j = i + 1; j < 6; j++)
		{
			if (tempCodemon.getLevel() > codemons[j].getLevel())
			{
				tempCodemon = codemons[j];
				codemons[j] = codemons[i];
				codemons[i] = tempCodemon;
			}
		}
	}

	//Print out codemons in ascending order of level
	for (int i = 0; i < 6; i++)
	{
		sortedCodemons[i].print();
	}
	std::cout << "Items: " << std::endl;
	Item sortedItems[20];
	for (int i = 0; i < 20; i++)
	{
		Item tempItem = items[i];
		for (int j = i + 1; j < 20; j++)
		{
			if (tempItem.getDuration() > items[j].getDuration())
			{
				tempItem = items[j];
				items[j] = items[i];
				items[i] = tempItem;
			}
		}
	}
}

void Contestant::printVisibleMap(Contestant other, Map map, Codemon activeCodemon, Codemon otherActiveCodemon) const {
	Map visibleMap = map.generateVisibleMap(*this);
	if (isPlayer)
	{
		visibleMap.printMap(*this);
		std::cout << "===========" << std::endl;
		std::cout << "[@] Contestant " << this->name << "'s " << activeCodemon.getName()
			<< " is standing on ";
		char standingTile = map.terrainMap[map.playerX][map.playerY];
		switch (standingTile)
		{
		case 'F':
		{
			std::cout << "Forest" << std::endl;
			break;
		}
		case 'M':
		{
			std::cout << "Mountain" << std::endl;
			break;
		}
		case 'P':
		{
			std::cout << "Plains" << std::endl;
			break;
		}
		case 'W':
		{
			std::cout << "Water" << std::endl;
			break;
		}
		case 'S':
		{
			std::cout << "Swamp" << std::endl;
			break;
		}
		default:
		{
			std::cout << "ERROR: TILE NOT VALID IN PRINTVISBILEMAP" << std::endl;
			break;
		}
		}
		std::cout << activeCodemon << std::endl;

		if ((abs(map.enemyX - map.playerX) <= 1) && (abs(map.enemyY - map.playerY <= 1)))
		{
			std::cout << "[E] Contestant " << other.name << "'s " << otherActiveCodemon.getName()
				<< " is standing on ";
			char standingTile = map.terrainMap[map.enemyX][map.enemyY];
			switch (standingTile)
			{
			case 'F':
			{
				std::cout << "Forest" << std::endl;
				break;
			}
			case 'M':
			{
				std::cout << "Mountain" << std::endl;
				break;
			}
			case 'P':
			{
				std::cout << "Plains" << std::endl;
				break;
			}
			case 'W':
			{
				std::cout << "Water" << std::endl;
				break;
			}
			case 'S':
			{
				std::cout << "Swamp" << std::endl;
				break;
			}
			default:
			{
				std::cout << "ERROR: TILE NOT VALID IN PRINTVISBILEMAP" << std::endl;
				break;
			}
			}
			std::cout << otherActiveCodemon << std::endl;
		}
	}
}

std::string Contestant::getName() const {
	return this->name;
}

int Contestant::getNumCodemons() const {
	return this->numCodemons;
}

bool Contestant::getIsPlayer() const {
	return this->isPlayer;
}

//Codemon* Contestant::getCodemons() const {
//	Codemon* tempCodemons = new Codemon[numCodemons];
//	for (int i = 0; i < numCodemons; i++)
//	{
//		tempCodemons[i] = codemons[i];
//	}
//	return tempCodemons;
//}