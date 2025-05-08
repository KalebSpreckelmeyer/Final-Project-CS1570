#include "Codemon.h"
#include <iostream>
#include "Contestant.h"

void Codemon::evolve()
{
	int baseLuck = rand() % 71;
	int numSkills = sizeof(skills) / sizeof(skills[0]);

	int evolutionChance = baseLuck + (numSkills * 5);

	if (evolutionChance >= 60)
	{
		this->level++;
		//Randomly select skill to evolve
		int skillIndex = rand() % numSkills;
		//Randomly select damage increase
		int damageIncrease = rand() % 101;
		float damageIncreasePercent = damageIncrease / 100.0f;
		//Increase skill damage
		int newDamage = skills[skillIndex].getDamage() * (1 + damageIncreasePercent);
		skills[skillIndex].setDamage(newDamage);
		//Print out evolution message
		std::cout << this->name << " has evolved to level " << this->level << "!" << std::endl;
		std::cout << "Skill " << skills[skillIndex].getName() << " has increased damage to " << newDamage << "!" << std::endl;
		return;
	}
	else
	{
		return;
	}
}

Codemon::Codemon()
{
	this->name = "Unnamed";
	this->type = "None";
	this->level = 0;
	this->health = 0;
	this->maxHealth = health;
}

Codemon::Codemon(std::string name, std::string type, int level, int health)
{
	this->name = name;
	this->type = type;
	this->level = level;
	this->health = health;
	this->maxHealth = health;
}

void Codemon::updateSkills(Skill skill)
{
	//Check if skill is already present
	for (int i = 0; i < 6; i++)
	{
		if (skills[i].getName() == skill.getName())
		{
			std::cout << "Skill already present!" << std::endl;
			return;
		}
	}
	//Add skill to skills array
	for (int i = 0; i < 6; i++)
	{
		if (skills[i].getName() == "Unnamed")
		{
			skills[i] = skill;
			return;
		}
	}
}

void Codemon::print()
{
	std::cout << "Codemon Name: " << this->name << std::endl;
	std::cout << "Codemon Type: " << this->type << std::endl;
	std::cout << "Codemon Level: " << this->level << std::endl;
	std::cout << "Codemon Health: " << this->health << std::endl;
	std::cout << "Codemon Skills: " << std::endl;
	//sort skills in ascending order of base damage

	Skill sortedSkills[6];
	for (int i = 0; i < 6; i++)
	{
		Skill tempSkill = skills[i];
		for (int j = i + 1; j < 6; j++)
		{
			if (tempSkill.getDamage() > skills[j].getDamage())
			{
				tempSkill = skills[j];
				skills[j] = skills[i];
				skills[i] = tempSkill;
			}
		}
	}

	//Print out skills in ascending order of base damage
	for (int i = 0; i < 6; i++)
	{
		std::cout << "Skill Name: " << sortedSkills[i].getName() << std::endl;
		std::cout << "Skill Damage: " << sortedSkills[i].getDamage() << std::endl;
	}

}

std::string Codemon::getName() const
{
	return this->name;
}

std::string Codemon::getType() const
{
	return this->type;
}
int Codemon::getLevel() const
{
	return this->level;
}

int Codemon::getHealth() const
{
	return this->health;
}

int Codemon::getMaxHealth() const
{
	return this->maxHealth;
}

Skill* Codemon::getSkills() const {
	Skill* temp = new Skill[6];
	for (int i = 0; i < 6; i++)
	{
		temp[i] = skills[i];
	}
	return temp;
}

void Codemon::setName(std::string name)
{
	this->name = name;
}
//void skillLookup(Contestant contestants[], int numContestants)
//{
//	std::cout << "Enter skill name: ";
//	std::string skillName;
//	std::cin.ignore(10000, '\n');
//	std::getline(std::cin, skillName);
//	std::cout << "Skill: " << skillName << std::endl;
//	int index = 1;
//	for (int i = 0; i < numContestants; i++)
//	{
//		for (int j = 0; j < contestants[i].getNumCodemons(); j++)
//		{
//			for (int k = 0; k < 6; k++)
//			{
//				if (contestants[i].codemons[j].skills[k].getName() == skillName)
//				{
//					std::cout << "Acquired by: " << std::endl;
//					std::cout << index << ") " << contestants[i].codemons[j].getName() <<
//						" (" + contestants[i].name + ") - " << "Base damage: "
//						<< contestants[i].codemons[j].skills[k].getDamage() << std::endl;
//					index++;
//				}
//			}
//		}
//	}
//	if (index == 1)
//	{
//		std::cout << "Skill not found!" << std::endl;
//	}
//	else
//	{
//		std::cout << "Total number of codemons with this skill: " << index - 1 << std::endl;
//	}
//}

Codemon Codemon::operator-(int hp)
{
	Codemon temp = *this;
	temp.health -= hp;
	if (temp.health < 0) temp.health = 0;
	return temp;
}

Codemon& Codemon::operator-=(int hp)
{
	this->health -= hp;
	if (this->health < 0) this->health = 0;
	return *this;
}