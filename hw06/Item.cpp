#include "Item.h"

Item::Item()
{
	this->name = "Unnamed";
	this->description = "None";
	this->duration = 0;
}

Item::Item(std::string name, std::string description, int duration)
{
	this->name = name;
	this->description = description;
	this->duration = duration;
}

int Item::getDuration() const
{
	return this->duration;
}

