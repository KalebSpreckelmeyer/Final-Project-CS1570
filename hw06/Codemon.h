#ifndef CODEMON_H
#define CODEMON_H
#include <string>
#include "Skill.h"
#include <iostream>

//class Contestant;

class Codemon
{
private:
	std::string name;
	std::string type;
	int level;
	int health;
	int maxHealth;
	Skill skills[6];

	//DESC: Evolves the codemon to the next level, increasing its level and the base 
	// damage of one randomly selected skill
	//PRE: The codemon should be properly initialized
	//POST: The codemon's level is increased by 1 and the base damage of one skill is increased
	void evolve();

public:
	//Default contructor that initializes the codemon with default values
	Codemon();

	//Parameterized constructor that accepts a name, type, level, and health
	// and initializes the codemon with these values
	Codemon(std::string name, std::string type, int level, int health);

	//DESC: Updates Codemon's skills with new skill so long as skill is not already present
	//PRE: The codemon and skill should be properly initialized
	//POST: The skill is added to the codemon's skills if it is not already present
	void updateSkills(Skill skill);

	//DESC: Prints out the codemon's name, type, level, health, and skills in a formatted manner
	//PRE: The codemon should be properly initialized
	//POST: The codemon's name, type, level, health, and skills are printed
	void print();

	//DESC: This function will search through each contestant provided and return 
	// a particular skill. This skill is determined by the name of the skill and the 
	// function will prompt the user to input said name before searching 
	//PRE: The contestant array should be properly initialized
	//POST: The function will search through each contestant and return the skill
	/*friend void skillLookup(Contestant contestants[], int numContestants);*/

	//DESC: Overload of the << operator to print out Codemon information 
	//PRE: Codemon should be properly initialized 
	//POST: Codemon Type, Level, and Current Hp / Max Hp will be returned 
	friend std::ostream& operator<<(std::ostream& os, const Codemon& codemon)
	{
		os << "Type: " << codemon.type << std::endl
			<< "Level: " << codemon.level << std::endl
			<< "HP: " << codemon.health << "/" << codemon.maxHealth << std::endl;
		return os;
	}

	//DESC: Overload of the - operator to return a new codemon object with the health of the
	// original - the int value passed
	//PRE: Codemon should pe properly initialized 
	//POST: New codemon object will be returned 
	Codemon operator - (int hp);

	//DESC: Overload of the -= operator to modify an existing codemon object's health points
	// and return the same codemon object with the new health value 
	//PRE: Codemon should be properly initialized 
	//POST: Modified codemon will be returned 
	Codemon& operator -=(int hp);

	//Getters
	std::string getName() const;
	std::string getType() const;
	int getLevel() const;
	int getHealth() const;
	int getMaxHealth() const;
	Skill* getSkills() const;

	//Setters
	void setName(std::string name);
};
#endif // !CODEMON_H
