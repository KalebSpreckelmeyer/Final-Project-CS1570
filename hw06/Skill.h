#ifndef SKILL_H
#define SKILL_H

#include <string>
class Skill
{
private:
	std::string name;
	int damage;
public:
	//Default constructor that initializes the skill with default values
	Skill();
	//Parameterized constructor that accepts a name and damage value
	// and initializes the skill with these values
	Skill(std::string name, int damage);

	//Getters 
	std::string getName() const;
	int getDamage() const;

	//Setters
	void setDamage(int damage);
	void setName(std::string name);
};
#endif // !SKILL_H



