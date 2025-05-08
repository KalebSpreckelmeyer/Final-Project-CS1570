#include "Skill.h"

Skill::Skill()
{
	this->name = "Unnamed";
	this->damage = 0;
}

Skill::Skill(std::string name, int damage)
{
	this->name = name;
	this->damage = damage;
}

std::string Skill::getName() const
{
	return this->name;
}

int Skill::getDamage() const
{
	return this->damage;
}

void Skill::setDamage(int damage)
{
	this->damage = damage;
}

void Skill::setName(std::string name)
{
	this->name = name;
}