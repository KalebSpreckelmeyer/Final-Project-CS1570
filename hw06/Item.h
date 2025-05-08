#ifndef ITEM_H
#define ITEM_H

#include <string>
class Item
{
private:
	std::string name;
	std::string description;
	int duration;
public:
	//Default constructor that initializes the item with default values
	Item();
	//Parameterized constructor that accepts a name, description, and duration
	// and initializes the item with these values
	Item(std::string name, std::string description, int duration);

	//Getters
	int getDuration() const;
};
#endif // !ITEM_H



